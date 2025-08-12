#include "./game_state.hpp"

#include <iostream>
#include <string>

bool TurnSelection::haveFactionBonus(void) const {
	const auto& current_card = card();
	for (size_t i = 0; i < deck.size(); i++) {
		if (i == card_idx) {
			continue; // skip self
		}

		if (current_card.faction_bonus == deck.at(i).faction_bonus) {
			return true;
		}
	}
	return false;
}

std::string TurnSelection::toString(void) const {
	std::string str;
	str += "{" + card().toStringNLPD() + "},pots:" + std::to_string(pots);
	if (frenzy) {
		str += ",frenzy";
	}
	return str;
}

void TurnSelection::printSelection(void) const {
	std::cout << " " << toString() << "\n";
	//std::cout << " '" << card().name << "' P:" << card().power << " L:" << card().level << " D:" << card().damage << "\n";
	//std::cout << "  " << pots << " pots\n";
	//if (frenzy) {
	//    std::cout << "  and frenzy\n";
	//}
}

Round::win Round::decide_winning_card (void) const {
	const TurnSelection& turn1 = turns.at(0);
	const CardTemp& turn1_card_temp = card_temps.at(0);
	const TurnSelection& turn2 = turns.at(1);
	const CardTemp& turn2_card_temp = card_temps.at(1);

	if (turn1_card_temp.attack > turn2_card_temp.attack) {
		//std::cout << "t1 won by attack\n";
		return {0, WinReason::ATTACK};
	} else if (turn1_card_temp.attack < turn2_card_temp.attack) {
		//std::cout << "t2 won by attack\n";
		return {1, WinReason::ATTACK};
	} else { // equal
		if (turn1.card().level < turn2.card().level) {
			//std::cout << "t1 won by level\n";
			return {0, WinReason::LEVEL};
		} else if (turn1.card().level > turn2.card().level) {
			//std::cout << "t2 won by level\n";
			return {1, WinReason::LEVEL};
		} else { // equal
			//std::cout << "t1 won by default\n";
			return {0, WinReason::DEFAULT};
		}
	}
}

GameState::GameState(
	const std::vector<Card>& player1_cards,
	const std::vector<Card>& player2_cards
) : cards{player1_cards, player2_cards} {
	cards_used.at(0).resize(player1_cards.size(), false);
	cards_used.at(1).resize(player2_cards.size(), false);
}

size_t GameState::nextRoundStartingPlayer(void) {
	return (starting_player + rounds.size()) % 2;
}

bool GameState::update(
	const Round& round
) {
	const size_t player0 = round.players.at(0);
	const size_t player1 = round.players.at(1);
	// TODO: check for correctness
	// used volatiles
	// player order
	if ( // used cards
		cards_used.at(player0).at(round.turns.at(0).card_idx) == true ||
		cards_used.at(player1).at(round.turns.at(1).card_idx) == true
	) {
		std::cerr << "err card for new round already used\n";
		return false;
	}

	rounds.push_back(round);

	cards_used.at(player0).at(round.turns.at(0).card_idx) = true;
	cards_used.at(player1).at(round.turns.at(1).card_idx) = true;

	vols.at(player0).pots -= round.turns.at(0).pots + (round.turns.at(0).frenzy ? 3 : 0);
	vols.at(player1).pots -= round.turns.at(1).pots + (round.turns.at(1).frenzy ? 3 : 0);

	auto [won_ridx, _] = round.decide_winning_card();
	const size_t player_won = round.players.at(won_ridx);
	const size_t player_lost = (player_won+1)%2;
	vols.at(player_lost).hp -= round.card_temps.at(won_ridx).damage;

	vols.at(player0).hp += round.volatile_changes.at(0).hp;
	vols.at(player0).pots += round.volatile_changes.at(0).pots;
	vols.at(player1).hp += round.volatile_changes.at(1).hp;
	vols.at(player1).pots += round.volatile_changes.at(1).pots;

	return true;
}

std::string GameState::toString(void) const {
	std::string str;
	//size_t starting_player {0};
	str += "SP:" + std::to_string(starting_player);

	//// only should contain 4 cards, so already be chosen
	//std::array<std::vector<Card>, 2> cards;
	str += ",PC:[";
	for (size_t player = 0; player < 2; player++) {
		str += "[";
		for (const auto& card : cards.at(player)) {
			str += "{" + card.toStringNLPD() + "},";
		}
		str += "],";
	}
	str += "],";
	//std::array<std::vector<bool>, 2> cards_used;

	//struct PlayerVolatiles {
	//    int16_t pots {12};
	//    int16_t hp {12};
	//};
	//std::array<PlayerVolatiles, 2> vols;

	//std::vector<Round> rounds;

	return str;
}

