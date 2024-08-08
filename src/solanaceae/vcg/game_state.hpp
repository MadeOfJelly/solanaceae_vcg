#pragma once

#include "./card.hpp"

#include <vector>
#include <array>

struct TurnSelection {
	const std::vector<Card>& deck;

	size_t card_idx {0};

	// extra pots
	size_t pots {0};
	bool frenzy {false};

	TurnSelection(const std::vector<Card>& _deck) : deck(_deck) {}
	TurnSelection(
		const std::vector<Card>& _deck,
		size_t _card_idx,
		size_t _pots,
		bool _frenzy
	) : deck(_deck), card_idx(_card_idx), pots(_pots), frenzy(_frenzy) {}

	const Card& card(void) const { return deck.at(card_idx); }

	bool haveFactionBonus(void) const;

	std::string toString(void) const;
	void printSelection(void) const;
};

// just card numbers for intermediary results
struct CardTemp {
	int16_t power {0};
	int16_t damage {0};

	int16_t attack {0};
};

struct Round {
	std::vector<TurnSelection> turns;
	std::array<CardTemp, 2> card_temps;

	std::array<size_t, 2> players;

	enum class WinReason {
		ATTACK,
		LEVEL,
		DEFAULT,
	};
	struct win {
		size_t idx{0};
		WinReason reason{WinReason::DEFAULT};
	};
	win decide_winning_card (void) const;
};

// holds the current game state
struct GameState {
	size_t starting_player {0};

	// only should contain 4 cards, so already be chosen
	std::array<std::vector<Card>, 2> cards;
	std::array<std::vector<bool>, 2> cards_used;

	struct PlayerVolatiles {
		int16_t pots {12};
		int16_t hp {12};
	};
	std::array<PlayerVolatiles, 2> vols;

	std::vector<Round> rounds;

	GameState(
		const std::vector<Card>& player1_cards,
		const std::vector<Card>& player2_cards
	);

	// call this after construction !
	// uses rng as a fallback
	template<typename RNG>
	void determineStartingPlayer(RNG& rng) {
		size_t p1_total_levels{0};
		for (const auto& card : cards.at(0)) {
			p1_total_levels += card.level;
		}
		size_t p2_total_levels{0};
		for (const auto& card : cards.at(1)) {
			p2_total_levels += card.level;
		}

		if (p1_total_levels > p2_total_levels) {
			starting_player = 0;
		} else if (p2_total_levels > p1_total_levels) {
			starting_player = 1;
		} else {
			starting_player = rng()%2;
		}
	}

	size_t nextRoundStartingPlayer(void);

	// adds round
	// marks cards as used
	// updates player volatiles // TODO: take battle results
	bool update(
		const Round& round
	);


	std::string toString(void) const;
};

