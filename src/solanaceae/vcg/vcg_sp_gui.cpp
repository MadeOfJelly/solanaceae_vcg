#include "./vcg_sp_gui.hpp"

#include "./card.hpp"
#include "./game_state.hpp"

#include "./sp_gui_states.hpp"

#include "./cards/easy_cards.hpp"

#include <imgui.h>

#include <memory>
#include <random>
#include <optional>

// TODO: refactor
template<typename RNG>
static std::vector<Card> drawCards(RNG& rng, const std::vector<Card>& full_deck) {
	// TODO: avoid extra copy
	std::vector<Card> subset = full_deck;
	while (subset.size() > 4) {
		size_t to_remove_idx = rng()%subset.size();
		subset.erase(subset.cbegin() + to_remove_idx);
	}
	return subset;
}

template<typename RNG>
static TurnSelection turnSelectRandom(RNG& rng, const std::vector<Card>& cards, const std::vector<bool>& cards_used, const GameState::PlayerVolatiles& vol) {
	size_t extra_pots = rng()%(vol.pots + 1);
	//vol.pots -= extra_pots;

	bool frenzy = (vol.pots - extra_pots) >= 3 ? rng()%10 == 0 : false;
	//if (frenzy) { vol.pots -= 3; }

	size_t card_idx = rng()%cards.size();
	while (cards_used.at(card_idx)) {
		card_idx = (card_idx+1)%cards.size();
	}
	//cards_used.at(card_idx) = true;

	return {
		cards,
		card_idx,
		extra_pots,
		frenzy,
	};
}

template <typename>
constexpr bool ability_has_min(void) { return false; }

template <>
constexpr bool ability_has_min<Abilities::OppDamage>(void) { return true; }
template <>
constexpr bool ability_has_min<Abilities::OppPower>(void) { return true; }
template <>
constexpr bool ability_has_min<Abilities::OppAttack>(void) { return true; }

template<typename T>
static bool apply_ability(int16_t& value, const Ability& a) {
	if (std::holds_alternative<T>(a.a)) {
		const auto& a_v = std::get<T>(a.a);
		const auto value_before = value;

		value += a_v.value;

		// if has min and avv is < 0
		if constexpr (ability_has_min<T>()) {
			if (a_v.value < 0) {
				value = std::min<int16_t>(value_before, std::max<int16_t>(value, a_v.to_at_least));
			} // TODO: max(min()) for > 0?
		}
		return true;
	}
	return false;
}

template<typename T, typename... Args>
static void apply_abilities(int16_t& value, const Ability& a, const Ability& b) {
	apply_ability<T>(value, a);
	apply_ability<T>(value, b);
	if constexpr (sizeof...(Args) > 0) {
		apply_abilities<Args...>(value, a, b);
	}
}

void cardHoverDetails(const Card& card) {
	if (ImGui::BeginItemTooltip()) {
		ImGui::Text("Name: %s", card.name.c_str());
		ImGui::Text("Level: %hu", card.level);
		ImGui::Text("Power: %hu", card.power);
		ImGui::Text("Damage: %hu", card.damage);
		ImGui::Separator();
		ImGui::Text("Ability: %s", card.ability.string.c_str());
		ImGui::Text("Faction: %s", card.faction_bonus.string.c_str());
		ImGui::Separator();
		ImGui::TextWrapped("%s", card.description.c_str());
		ImGui::EndTooltip();
	}
}

std::unique_ptr<PhaseI> PhaseCardSelection::render_impl(GameState& gs, std::optional<Round>& round, float) {
	if (!round) {
		// construct current round
		round = Round{};
		round->players.at(0) = gs.nextRoundStartingPlayer();
		round->players.at(1) = (round->players.at(0)+1)%2;
	}

	if (round->turns.size() == 2) {
		return std::make_unique<PhaseRevealSelections>();
	} else {
		if (round->players.at(round->turns.size()) == 0) {
			return std::make_unique<PhaseCardSelectionHuman>(gs);
		} else {
			return std::make_unique<PhaseCardSelectionBot>();
		}
	}
	return nullptr;
}

PhaseCardSelectionHuman::PhaseCardSelectionHuman(const GameState& gs) : _turn(gs.cards.at(0)) {
}

std::unique_ptr<PhaseI> PhaseCardSelectionHuman::render_impl(GameState& gs, std::optional<Round>& round, float) {
	assert(round);

	ImGui::Indent();
	for (size_t i = 0; i < _turn.deck.size(); i++) {
		const auto label = _turn.deck.at(i).toStringNLPD();
		// TODO: annoying, remove deck from turn?
		const bool used = gs.cards_used.at(0).at(i);
		if (used) {
			ImGui::Selectable(label.c_str(), false, ImGuiSelectableFlags_Disabled);
		} else {
			if (ImGui::Selectable(label.c_str(), i == _turn.card_idx)) {
				_turn.card_idx = i;
			}
		}
		cardHoverDetails(gs.cards.at(0).at(i));
	}
	ImGui::Unindent();

	ImGui::TextUnformatted("> select a card, pots and frenzy");

	ImGui::Text("have pots: %d", gs.vols.at(0).pots);
	{
		const size_t min_v {0};
		const size_t max_v {static_cast<size_t>(std::max(0, gs.vols.at(0).pots - _turn.frenzy*3))};
		ImGui::SliderScalar("extra pots", ImGuiDataType_U64, &_turn.pots, &min_v, &max_v);
	}

	if (ImGui::Checkbox("frenzy (+2 dmg for 3 pots)", &_turn.frenzy)) {
		if (int64_t(_turn.pots + _turn.frenzy*3) > int64_t(gs.vols.at(0).pots)) {
			_turn.frenzy = false;
		}
	}

	ImGui::Text("attack: %zu (without abilities)", _turn.card().power * (1+_turn.pots));
	ImGui::TextDisabled("^ the most useless metric ever");

	if (ImGui::Button("confirm")) {
		round->turns.emplace_back(_turn);
		return std::make_unique<PhaseCardSelection>();
	}

	return nullptr;
}

std::unique_ptr<PhaseI> PhaseCardSelectionBot::render_impl(GameState& gs, std::optional<Round>& round, float) {
	assert(round);
	ImGui::TextUnformatted("smart-ai 9000 is thinking...");
	if (_timer >= _fake_time) {
		// "smart-ai™ 9000"
		round->turns.emplace_back(turnSelectRandom(_rng, gs.cards.at(1), gs.cards_used.at(1), gs.vols.at(1)));
		return std::make_unique<PhaseCardSelection>();
	}
	return nullptr;
}

std::unique_ptr<PhaseI> PhaseRevealSelections::render_impl(GameState& gs, std::optional<Round>& round, float) {
	assert(round);

	size_t human_idx = round->players.at(0) == 0 ? 0 : 1;
	size_t bot_idx = (human_idx+1)%2;

	ImGui::Text("bot chose %zu pots%s.", round->turns.at(bot_idx).pots, round->turns.at(bot_idx).frenzy ? ", and frenzy" : "");
	ImGui::Text("you chose %zu pots%s.", round->turns.at(human_idx).pots, round->turns.at(human_idx).frenzy ? ", and frenzy" : "");
	if (ImGui::Button("continue to battle")) {
		return std::make_unique<PhaseBattle>();
	}

	return nullptr;
}

std::unique_ptr<PhaseI> PhaseBattle::render_impl(GameState& gs, std::optional<Round>& round, float) {
	assert(round);

	// calculate all the values for the selected cards (temp cards)

	for (size_t i = 0; i < round->card_temps.size(); i++) { // fill in base
		round->card_temps.at(i).power = round->turns.at(i).card().power;
		round->card_temps.at(i).damage = round->turns.at(i).card().damage;
		//std::cout << "  p" << round.players.at(i)+1 << " base power:" << round.card_temps.at(i).power << " damage:" << round.card_temps.at(i).damage << "\n";
	}

	// apply frenzy dmg bonus
	for (size_t i = 0; i < round->card_temps.size(); i++) {
		if (round->turns.at(i).frenzy) {
			round->card_temps.at(i).damage += 2;
		}
	}

	// TODO: move targetting to somewhere else
	for (size_t i = 0; i < round->card_temps.size(); i++) { // apply power and dmg
		apply_abilities<Abilities::Power>(
			round->card_temps.at(i).power,
			round->turns.at(i).card().ability,
			round->turns.at(i).card().faction_bonus
		);
		apply_abilities<Abilities::Damage>(
			round->card_temps.at(i).damage,
			round->turns.at(i).card().ability,
			round->turns.at(i).card().faction_bonus
		);
	}

	for (size_t i = 0; i < round->card_temps.size(); i++) { // apply opp power and dmg
		apply_abilities<Abilities::OppPower>(
			round->card_temps.at((i+1)%round->card_temps.size()).power,
			round->turns.at(i).card().ability,
			round->turns.at(i).card().faction_bonus
		);
		apply_abilities<Abilities::OppDamage>(
			round->card_temps.at((i+1)%round->card_temps.size()).damage,
			round->turns.at(i).card().ability,
			round->turns.at(i).card().faction_bonus
		);
	}

	// calc attack
	for (size_t i = 0; i < round->card_temps.size(); i++) {
		round->card_temps.at(i).attack = round->card_temps.at(i).power * (round->turns.at(i).pots + 1);
		//std::cout << "  p" << round.players.at(i)+1 << " base attack:" << round.card_temps.at(i).attack << "\n";
	}

	for (size_t i = 0; i < round->card_temps.size(); i++) { // apply attack
		apply_abilities<Abilities::Attack>(
			round->card_temps.at(i).attack,
			round->turns.at(i).card().ability,
			round->turns.at(i).card().faction_bonus
		);
	}

	for (size_t i = 0; i < round->card_temps.size(); i++) { // apply opp attack
		apply_abilities<Abilities::OppAttack>(
			round->card_temps.at((i+1)%round->card_temps.size()).attack,
			round->turns.at(i).card().ability,
			round->turns.at(i).card().faction_bonus
		);
	}

	return std::make_unique<PhaseBattleEnd>();
}

std::unique_ptr<PhaseI> PhaseBattleEnd::render_impl(GameState& gs, std::optional<Round>& round, float) {
	assert(round);

	size_t human_idx = round->players.at(0) == 0 ? 0 : 1;
	size_t bot_idx = (human_idx+1)%2;
	ImGui::Text("bot chose %zu pots%s.", round->turns.at(bot_idx).pots, round->turns.at(bot_idx).frenzy ? ", and frenzy" : "");
	ImGui::Text("you chose %zu pots%s.", round->turns.at(human_idx).pots, round->turns.at(human_idx).frenzy ? ", and frenzy" : "");

	// show values
	ImGui::Text("bot  attack: %hd", round->card_temps.at(bot_idx).attack);
	ImGui::Text("your attack: %hd", round->card_temps.at(human_idx).attack);

	// show winner
	auto [win_ridx, reason] = round->decide_winning_card();
	const auto winning_player = round->players.at(win_ridx);
	if (winning_player == 0) {
		ImGui::TextUnformatted("player wins round!");
	} else {
		ImGui::TextUnformatted("bot wins round.");
	}
	switch (reason) {
		case Round::WinReason::ATTACK:
			ImGui::TextUnformatted("by attack");
			break;
		case Round::WinReason::LEVEL:
			ImGui::TextUnformatted("by level");
			break;
		case Round::WinReason::DEFAULT:
			ImGui::TextUnformatted("by default");
			break;
	}

	if (ImGui::Button("continue")) {
		// apply dmg here? or ad end of battle?

		gs.update(*round);
		round = std::nullopt;

		if (gs.rounds.size() == 4 || gs.vols.at(0).hp <= 0 || gs.vols.at(1).hp <= 0) {
			return std::make_unique<PhaseEndScreen>();
		} else {
			return std::make_unique<PhaseCardSelection>();
		}
	}

	return nullptr;
}

std::unique_ptr<PhaseI> PhaseEndScreen::render_impl(GameState& gs, std::optional<Round>& round, float) {
	assert(!round);

	if (gs.vols.at(0).hp > gs.vols.at(1).hp) {
		ImGui::TextUnformatted("You won!");
	} else if (gs.vols.at(0).hp < gs.vols.at(1).hp) {
		ImGui::TextUnformatted("Bot won.");
	} else {
		ImGui::TextUnformatted("Draw!");
	}

	return nullptr;
}

struct CurrentGame {
	GameState game_state;
	std::optional<Round> round;
	std::unique_ptr<PhaseI> phase;

	CurrentGame(GameState&& _game_state) : game_state(_game_state) {}
};

VCGSPGUI::VCGSPGUI(void) {
	//_game = std::make_unique<CurrentGame>();
}

VCGSPGUI::~VCGSPGUI(void) {
}

float VCGSPGUI::render(float delta) {
	if (ImGui::Begin("VCG sp")) {
		if (ImGui::Button("new game")) {
			const auto cards = Cards::easy_cards();

			std::default_random_engine rng{std::random_device{}()};

			_game = std::make_unique<CurrentGame>(
				GameState(
					drawCards(rng, cards),
					drawCards(rng, cards)
				)
			);
			_game->game_state.determineStartingPlayer(rng);

			_game->phase = std::make_unique<PhaseCardSelection>();
		}

		if (_game) {
			ImGui::Separator();
			auto& gs = _game->game_state;

			// player is player 0
			// bot is player 1
			ImGui::Text("starting player: %zu (%s)", gs.starting_player, gs.starting_player == 0 ? "human" : "bot");

			if (ImGui::CollapsingHeader("details")) {
				const auto str = gs.toString();
				ImGui::TextWrapped("%s", str.c_str());
			}

			const size_t human_rindex = _game->round->players.at(0) == 0 ? 0 : 1;
			const size_t bot_rindex = _game->round->players.at(0) == 0 ? 1 : 0;
			const bool can_show_human_selection = _game->round->turns.size() == 2 || (_game->round->turns.size() == 1 && human_rindex == 0);
			const bool can_show_bot_selection = _game->round->turns.size() == 2 || (_game->round->turns.size() == 1 && bot_rindex == 0);

			ImGui::Text("Bot Pots:%d HP:%d cards:", gs.vols.at(1).pots, gs.vols.at(1).hp);
			ImGui::Indent();
			ImGui::PushID(1); // bot
			for (size_t i = 0; i < gs.cards.at(1).size(); i++) {
				const auto label = gs.cards.at(1).at(i).toStringNLPD();
				const bool used = gs.cards_used.at(1).at(i);
				if (used) {
					ImGui::TextDisabled("%s", label.c_str());
				} else if (can_show_bot_selection && i == _game->round->turns.at(bot_rindex).card_idx) {
					ImGui::Selectable(label.c_str(), true, ImGuiSelectableFlags_Disabled);
				} else {
					ImGui::TextUnformatted(label.c_str());
				}
				cardHoverDetails(gs.cards.at(1).at(i));
			}
			ImGui::PopID();
			ImGui::Unindent();

			// bot flavor text here?
			//_game->phase->

			ImGui::Text("Your Pots:%d HP:%d cards:", gs.vols.at(0).pots, gs.vols.at(0).hp);
			if (_game->phase->showPlayerCards()) {
				// TODO: toggle render, or inject selectable?
				ImGui::Indent();
				for (size_t i = 0; i < gs.cards.at(0).size(); i++) {
					const auto label = gs.cards.at(0).at(i).toStringNLPD();
					const bool used = gs.cards_used.at(0).at(i);
					if (used) {
						ImGui::TextDisabled("%s", label.c_str());
					} else if (can_show_human_selection && i == _game->round->turns.at(human_rindex).card_idx) {
						ImGui::Selectable(label.c_str(), true, ImGuiSelectableFlags_Disabled);
					} else {
						ImGui::TextUnformatted(label.c_str());
					}
					cardHoverDetails(gs.cards.at(0).at(i));
				}
				ImGui::Unindent();
			}

			// phases?
			// a round gets constructed from both players selections

			// get current phase ?
			// if card selection
			// 	- if bot -> do ai
			// 	- if player -> show handcards and make clickable
			// 	both end selection and either end general card selection or next player selects cards
			// if card selection over -> reveal and show battle
			// if battle -> end battle
			// if end battle
			//  - if end game cond -> end screen
			//  - else card selection


			auto new_phase = _game->phase->render(gs, _game->round, delta);
			if (new_phase) {
				_game->phase = std::move(new_phase);
			}
		}
	}
	ImGui::End();

	return 2.f;
}


