#include "./sp_gui_states.hpp"

#include "./card.hpp"
#include "./game_state.hpp"

#include <imgui.h>

#include <cstdint>
#include <memory>
#include <numeric>
#include <optional>
#include <variant>

template<typename RNG>
static TurnSelection turnSelectRandom(RNG& rng, const std::vector<Card>& cards, const std::vector<bool>& cards_used, const PlayerVolatiles& vol) {
	const bool last_round = std::accumulate(cards_used.cbegin(), cards_used.cend(), 0) == 3;
	size_t extra_pots = 0;
	if (last_round) {
		extra_pots = vol.pots;
	} else {
		extra_pots = rng()%(vol.pots + 1);
	}

	bool frenzy = (vol.pots - extra_pots) >= 3 ? rng()%10 == 0 : false;

	size_t card_idx = rng()%cards.size();
	while (cards_used.at(card_idx)) {
		card_idx = (card_idx+1)%cards.size();
	}

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
template <>
constexpr bool ability_has_min<Abilities::OppLife>(void) { return true; }
template <>
constexpr bool ability_has_min<Abilities::OppPotion>(void) { return true; }
template <>
constexpr bool ability_has_min<Abilities::Poison>(void) { return true; }

template <typename T>
constexpr bool ability_has_min(void)
	requires requires(T t) { t.inner; }
{
	return ability_has_min<decltype(T::inner)>();
}

template <typename>
constexpr bool ability_has_max(void) { return false; }
template <>
constexpr bool ability_has_max<Abilities::Heal>(void) { return true; }

template <typename T>
constexpr bool ability_has_max(void)
	requires requires(T t) { t.inner; }
{
	return ability_has_max<decltype(T::inner)>();
}


// TODO: fragile, runtime
bool ability_is_defeat(const auto& a) {
	return
		std::holds_alternative<Abilities::Defeat<Abilities::Life>>(a.a) ||
		std::holds_alternative<Abilities::Defeat<Abilities::Poison>>(a.a) ||
		std::holds_alternative<Abilities::Defeat<Abilities::Heal>>(a.a) ||
		std::holds_alternative<Abilities::Defeat<Abilities::OppLife>>(a.a) ||
		std::holds_alternative<Abilities::Defeat<Abilities::Potion>>(a.a) ||
		std::holds_alternative<Abilities::Defeat<Abilities::RecoverPotions>>(a.a) ||
		std::holds_alternative<Abilities::Defeat<Abilities::OppPotion>>(a.a) ||
		std::holds_alternative<Abilities::Defeat<Abilities::LifePerDamage>>(a.a)
	;
}

template<typename T>
constexpr const auto& get_ability_value(const T& a)
	requires requires(T t) { t.value; }
{
	return a.value;
}
template<typename T>
constexpr const auto& get_ability_value(const T& a)
	requires requires(T t) { t.inner; }
{
	return get_ability_value(a.inner);
}

template<typename T>
constexpr const auto& get_ability_min(const T& a)
	requires requires(T t) { t.min; }
{
	return a.min;
}
template<typename T>
constexpr const auto& get_ability_min(const T& a)
	requires requires(T t) { t.inner; }
{
	return get_ability_min(a.inner);
}

template<typename T>
constexpr const auto& get_ability_max(const T& a)
	requires requires(T t) { t.max; }
{
	return a.max;
}
template<typename T>
constexpr const auto& get_ability_max(const T& a)
	requires requires(T t) { t.inner; }
{
	return get_ability_max(a.inner);
}

template<typename T>
static bool apply_value_ability(int16_t& value, const Ability& a) {
	if (std::holds_alternative<T>(a.a)) {
		const auto& a_v = std::get<T>(a.a);
		const auto value_before = value;

		value += get_ability_value(a_v);

		if constexpr (ability_has_min<T>()) {
			if (get_ability_value(a_v) < 0) {
				value = std::min<int16_t>(value_before, std::max<int16_t>(value, get_ability_min(a_v)));
			} // TODO: max(min()) for > 0?
		} else if constexpr (ability_has_max<T>()) {
			static_assert(false);
		}
		return true;
	}
	return false;
}
template<typename T, typename... Args>
static void apply_value_abilities(int16_t& value, const Ability& a, const Ability& b) {
	apply_value_ability<T>(value, a);
	apply_value_ability<T>(value, b);
	if constexpr (sizeof...(Args) > 0) {
		apply_value_abilities<Args...>(value, a, b);
	}
}

#if 0
template<typename T>
static bool apply_value_ability(const int16_t& value_base, int16_t& value_diff, const Ability& a) {
	if (std::holds_alternative<T>(a.a)) {
		const auto& a_v = std::get<T>(a.a);

		value_diff += get_ability_value(a_v);

		if constexpr (ability_has_min<T>()) {
			if (get_ability_value(a_v) < 0) {
				auto value_after = std::min<int16_t>(value_base, std::max<int16_t>(value_base + value_diff, get_ability_min(a_v)));
				value_diff = value_after - value_base;
			} // TODO: max(min()) for > 0?
		} else if constexpr (ability_has_max<T>()) {
			static_assert(false);
		}
		return true;
	}
	return false;
}

template<typename T, typename... Args>
static void apply_value_abilities(const int16_t& value_base, int16_t& value_diff, const Ability& a, const Ability& b) {
	apply_value_ability<T>(value_base, value_diff, a);
	apply_value_ability<T>(value_base, value_diff, b);
	if constexpr (sizeof...(Args) > 0) {
		apply_value_abilities<Args...>(value_base, value_diff, a, b);
	}
}
#endif

static inline void cardHoverDetails(const Card& card) {
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

		// copy abilities (before frenzy)
		size_t opp_ridx = (i+1)%2;
		if (std::holds_alternative<Abilities::CopyPower>(round->turns.at(i).card().ability.a)) {
			round->card_temps.at(i).power = round->turns.at(opp_ridx).card().power;
		}
		if (std::holds_alternative<Abilities::CopyPower>(round->turns.at(i).card().faction_bonus.a)) {
			round->card_temps.at(i).power = round->turns.at(opp_ridx).card().power;
		}

		if (std::holds_alternative<Abilities::CopyDamage>(round->turns.at(i).card().ability.a)) {
			round->card_temps.at(i).damage = round->turns.at(opp_ridx).card().damage;
		}
		if (std::holds_alternative<Abilities::CopyDamage>(round->turns.at(i).card().faction_bonus.a)) {
			round->card_temps.at(i).damage = round->turns.at(opp_ridx).card().damage;
		}

		// apply frenzy dmg bonus
		if (round->turns.at(i).frenzy) {
			round->card_temps.at(i).damage += 2;
		}

		// init temp vols, so we can edit them in respects to min/max
		round->volatile_temps.at(i).hp = gs.vols.at(round->players.at(i)).hp;
		round->volatile_temps.at(i).pots = gs.vols.at(round->players.at(i)).pots - (round->turns.at(i).pots + round->turns.at(i).frenzy*3);
	}

	for (size_t i = 0; i < round->card_temps.size(); i++) { // apply power and dmg
		apply_value_abilities<Abilities::Power>(
			round->card_temps.at(i).power,
			round->turns.at(i).card().ability,
			round->turns.at(i).card().faction_bonus
		);
		apply_value_abilities<Abilities::Damage>(
			round->card_temps.at(i).damage,
			round->turns.at(i).card().ability,
			round->turns.at(i).card().faction_bonus
		);
	}

	for (size_t i = 0; i < round->card_temps.size(); i++) { // apply opp power and dmg
		size_t opp_ridx = (i+1)%2;
		apply_value_abilities<Abilities::OppPower>(
			round->card_temps.at(opp_ridx).power,
			round->turns.at(i).card().ability,
			round->turns.at(i).card().faction_bonus
		);
		apply_value_abilities<Abilities::OppDamage>(
			round->card_temps.at(opp_ridx).damage,
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
		apply_value_abilities<Abilities::Attack>(
			round->card_temps.at(i).attack,
			round->turns.at(i).card().ability,
			round->turns.at(i).card().faction_bonus
		);
	}

	for (size_t i = 0; i < round->card_temps.size(); i++) { // apply opp attack
		apply_value_abilities<Abilities::OppAttack>(
			round->card_temps.at((i+1)%round->card_temps.size()).attack,
			round->turns.at(i).card().ability,
			round->turns.at(i).card().faction_bonus
		);
	}

	auto [win_ridx, reason] = round->decide_winning_card();
	const size_t loose_ridx = (win_ridx+1)%2;

	// the primary dmg -> hp effect
	round->volatile_temps.at(loose_ridx).hp -= round->card_temps.at(win_ridx).damage;

	{ // win
		size_t opp_ridx = (win_ridx+1)%2;
		apply_value_abilities<Abilities::Life>(
			round->volatile_temps.at(win_ridx).hp,
			round->turns.at(win_ridx).card().ability,
			round->turns.at(win_ridx).card().faction_bonus
		);
		//std::holds_alternative<Abilities::Poison>(a.a) ||
		//std::holds_alternative<Abilities::Heal>(a.a) ||
		apply_value_abilities<Abilities::OppLife>(
			round->volatile_temps.at(opp_ridx).hp,
			round->turns.at(win_ridx).card().ability,
			round->turns.at(win_ridx).card().faction_bonus
		);
		apply_value_abilities<Abilities::Potion>(
			round->volatile_temps.at(win_ridx).pots,
			round->turns.at(win_ridx).card().ability,
			round->turns.at(win_ridx).card().faction_bonus
		);

		if (std::holds_alternative<Abilities::RecoverPotions>(round->turns.at(win_ridx).card().ability.a)) {
			round->volatile_temps.at(win_ridx).pots += (round->turns.at(win_ridx).pots+2) / 2;
		}
		if (std::holds_alternative<Abilities::RecoverPotions>(round->turns.at(win_ridx).card().faction_bonus.a)) {
			round->volatile_temps.at(win_ridx).pots += (round->turns.at(win_ridx).pots+2) / 2;
		}

		apply_value_abilities<Abilities::OppPotion>(
			round->volatile_temps.at(opp_ridx).pots,
			round->turns.at(win_ridx).card().ability,
			round->turns.at(win_ridx).card().faction_bonus
		);

		if (std::holds_alternative<Abilities::LifePerDamage>(round->turns.at(win_ridx).card().ability.a)) {
			const auto& a_v = std::get<Abilities::LifePerDamage>(round->turns.at(win_ridx).card().ability.a);
			round->volatile_temps.at(win_ridx).hp += get_ability_value(a_v) * round->card_temps.at(win_ridx).damage;
		}
		if (std::holds_alternative<Abilities::LifePerDamage>(round->turns.at(win_ridx).card().faction_bonus.a)) {
			const auto& a_v = std::get<Abilities::LifePerDamage>(round->turns.at(win_ridx).card().faction_bonus.a);
			round->volatile_temps.at(win_ridx).hp += get_ability_value(a_v) * round->card_temps.at(win_ridx).damage;
		}
	}

	{ // loose (defeat)
		size_t opp_ridx = (loose_ridx+1)%2;
		apply_value_abilities<Abilities::Defeat<Abilities::Life>>(
			round->volatile_temps.at(loose_ridx).hp,
			round->turns.at(loose_ridx).card().ability,
			round->turns.at(loose_ridx).card().faction_bonus
		);
		//std::holds_alternative<Abilities::Defeat<Abilities::Poison>>(a.a) ||
		//std::holds_alternative<Abilities::Defeat<Abilities::Heal>>(a.a) ||
		apply_value_abilities<Abilities::Defeat<Abilities::OppLife>>(
			round->volatile_temps.at(opp_ridx).hp,
			round->turns.at(loose_ridx).card().ability,
			round->turns.at(loose_ridx).card().faction_bonus
		);
		apply_value_abilities<Abilities::Defeat<Abilities::Potion>>(
			round->volatile_temps.at(loose_ridx).pots,
			round->turns.at(loose_ridx).card().ability,
			round->turns.at(loose_ridx).card().faction_bonus
		);

		if (std::holds_alternative<Abilities::Defeat<Abilities::RecoverPotions>>(round->turns.at(loose_ridx).card().ability.a)) {
			round->volatile_temps.at(loose_ridx).pots += (round->turns.at(loose_ridx).pots+2) / 2;
		}
		if (std::holds_alternative<Abilities::Defeat<Abilities::RecoverPotions>>(round->turns.at(win_ridx).card().faction_bonus.a)) {
			round->volatile_temps.at(loose_ridx).pots += (round->turns.at(loose_ridx).pots+2) / 2;
		}

		apply_value_abilities<Abilities::Defeat<Abilities::OppPotion>>(
			round->volatile_temps.at(opp_ridx).pots,
			round->turns.at(loose_ridx).card().ability,
			round->turns.at(loose_ridx).card().faction_bonus
		);
		//std::holds_alternative<Abilities::Defeat<Abilities::LifePerDamage>>(a.a) // ??
	}

	// sanitize pots
	round->volatile_temps.at(0).pots = std::max<int16_t>(round->volatile_temps.at(0).pots, 0);
	round->volatile_temps.at(1).pots = std::max<int16_t>(round->volatile_temps.at(1).pots, 0);

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

	ImGui::SeparatorText("resulting in");
	ImGui::Text("bot  hp: %d (%+d)", round->volatile_temps.at(bot_idx).hp, round->volatile_temps.at(bot_idx).hp - gs.vols.at(1).hp);
	ImGui::Text("your hp: %d (%+d)", round->volatile_temps.at(human_idx).hp, round->volatile_temps.at(human_idx).hp - gs.vols.at(0).hp);
	ImGui::Text("bot  pots: %d (%+d)", round->volatile_temps.at(bot_idx).pots, round->volatile_temps.at(bot_idx).pots - gs.vols.at(1).pots);
	ImGui::Text("your pots: %d (%+d)", round->volatile_temps.at(human_idx).pots, round->volatile_temps.at(human_idx).pots - gs.vols.at(0).pots);

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
