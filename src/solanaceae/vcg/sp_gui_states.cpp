#include "./sp_gui_states.hpp"

#include "./card.hpp"
#include "./game_state.hpp"
#include "./battle.hpp"

#include <imgui.h>

#include <cstdint>
#include <memory>
#include <numeric>
#include <optional>

#include <iostream>

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

	if (round->turns.at(bot_idx).haveFactionBonus()) {
		ImGui::TextUnformatted("bot has faction bonus.");
	}
	if (round->turns.at(human_idx).haveFactionBonus()) {
		ImGui::TextUnformatted("you have faction bonus.");
	}

	ImGui::Text("bot chose 1+%zu pots%s.", round->turns.at(bot_idx).pots, round->turns.at(bot_idx).frenzy ? ", and frenzy" : "");
	ImGui::Text("you chose 1+%zu pots%s.", round->turns.at(human_idx).pots, round->turns.at(human_idx).frenzy ? ", and frenzy" : "");
	if (ImGui::Button("continue to battle")) {
		return std::make_unique<PhaseBattle>();
	}

	return nullptr;
}

std::unique_ptr<PhaseI> PhaseBattle::render_impl(GameState& gs, std::optional<Round>& round_opt, float) {
	assert(round_opt);
	auto& round = round_opt.value();

	battle(gs, round);

	return std::make_unique<PhaseBattleEnd>();
}

std::unique_ptr<PhaseI> PhaseBattleEnd::render_impl(GameState& gs, std::optional<Round>& round, float) {
	assert(round);

	size_t human_idx = round->players.at(0) == 0 ? 0 : 1;
	size_t bot_idx = (human_idx+1)%2;

	if (round->turns.at(bot_idx).haveFactionBonus()) {
		ImGui::TextUnformatted("bot has faction bonus.");
	}
	if (round->turns.at(human_idx).haveFactionBonus()) {
		ImGui::TextUnformatted("you have faction bonus.");
	}

	ImGui::Text("bot chose 1+%zu pots%s.", round->turns.at(bot_idx).pots, round->turns.at(bot_idx).frenzy ? ", and frenzy" : "");
	ImGui::Text("you chose 1+%zu pots%s.", round->turns.at(human_idx).pots, round->turns.at(human_idx).frenzy ? ", and frenzy" : "");

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
	ImGui::SameLine();
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

	if (!round->poisons.at(bot_idx).empty()) {
		ImGui::Text("bot suffered poison:");
		ImGui::Indent();
		for (const auto& poison : round->poisons.at(bot_idx)) {
			ImGui::Text("%d, min %d", poison.value, poison.min);
		}
		ImGui::Unindent();
	}
	if (!round->poisons.at(human_idx).empty()) {
		ImGui::Text("you suffered poison:");
		ImGui::Indent();
		for (const auto& poison : round->poisons.at(human_idx)) {
			ImGui::Text("%d, min %d", poison.value, poison.min);
		}
		ImGui::Unindent();
	}

	if (!round->heals.at(bot_idx).empty()) {
		ImGui::Text("bot received heal:");
		ImGui::Indent();
		for (const auto& heal : round->heals.at(bot_idx)) {
			ImGui::Text("%d, max %d", heal.value, heal.max);
		}
		ImGui::Unindent();
	}
	if (!round->heals.at(human_idx).empty()) {
		ImGui::Text("you received heal:");
		ImGui::Indent();
		for (const auto& heal : round->heals.at(human_idx)) {
			ImGui::Text("%d, max %d", heal.value, heal.max);
		}
		ImGui::Unindent();
	}

	if (ImGui::Button("continue")) {
		// apply dmg here? or ad end of battle?

		gs.update(*round);
		round = std::nullopt;

		std::cout << "--- round ---\n";

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
