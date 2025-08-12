#include "./card.hpp"
#include "./game_state.hpp"
#include "./cards/easy_cards.hpp"

#include <cstdint>
#include <iostream>
#include <random>
#include <variant>
#include <array>

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
				value = std::min<int16_t>(value_before, std::max<int16_t>(value, a_v.min));
			} // TODO: max(min()) for > 0?
		}
		return true;
	}
	return false;
}

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
static TurnSelection turnSelectRandom(RNG& rng, const std::vector<Card>& cards, std::vector<bool>& cards_used, PlayerVolatiles& vol) {
	size_t extra_pots = rng()%(vol.pots + 1);
	vol.pots -= extra_pots;

	bool frenzy = vol.pots >= 3 ? rng()%10 == 0 : false;
	if (frenzy) { vol.pots -= 3; }

	size_t card_idx = rng()%cards.size();
	while (cards_used.at(card_idx)) {
		card_idx = (card_idx+1)%cards.size();
	}
	cards_used.at(card_idx) = true;

	return {
		cards,
		card_idx,
		1 + extra_pots,
		frenzy,
	};
}

static size_t decide_winning_card(
	const TurnSelection& turn1, const CardTemp& turn1_card_temp,
	const TurnSelection& turn2, const CardTemp& turn2_card_temp
) {
	if (turn1_card_temp.attack > turn2_card_temp.attack) {
		std::cout << "t1 won by attack\n";
		return 0;
	} else if (turn1_card_temp.attack < turn2_card_temp.attack) {
		std::cout << "t2 won by attack\n";
		return 1;
	} else { // equal
		if (turn1.card().level < turn2.card().level) {
			std::cout << "t1 won by level\n";
			return 0;
		} else if (turn1.card().level > turn2.card().level) {
			std::cout << "t2 won by level\n";
			return 1;
		} else { // equal
			std::cout << "t1 won by default\n";
			return 0;
		}
	}
}

int main(void) {
	const auto cards = Cards::easy_cards();

	//for (const auto& card : cards) {
	//    std::cout << "C:" << card.name << "\n";
	//    std::cout << "  P:" << card.power << "\n";
	//    std::cout << "  D:" << card.damage << "\n";
	//    std::cout << "  A:";
	//    if (std::holds_alternative<Abilities::Damage>(card.ability.a)) {
	//        std::cout << "Damage " << std::get<Abilities::Damage>(card.ability.a).value << "\n";
	//    } else if (std::holds_alternative<Abilities::OppDamage>(card.ability.a)) {
	//        std::cout << "OppDamage " << std::get<Abilities::OppDamage>(card.ability.a).value << " Min " << std::get<Abilities::OppDamage>(card.ability.a).to_at_least << "\n";
	//    } else {
	//        std::cout << "unk\n";
	//    }
	//}

	std::default_random_engine rng{std::random_device{}()};

	// deck should only be 4 cards, or the TurnSelection should only contain 4 cards

	auto game = GameState(
		drawCards(rng, cards),
		drawCards(rng, cards)
	);
	game.determineStartingPlayer(rng);

	{ // print games setup
		std::cout << "Game setup:\n";

		std::cout << "  player1 draw:\n";
		size_t p1_total_levels {0};
		for (const auto& card : game.cards.at(0)) {
			std::cout
				<< "    " << card.name << "\n"
				<< "      L:" << card.level << " P:" << card.power << " D:" << card.damage << "\n"
				<< "      A:" << card.ability.string << "\n"
				<< "      F:" << card.faction_bonus.string << "\n";
			p1_total_levels += card.level;
		}
		std::cout << "    total levels: " << p1_total_levels << "\n";

		std::cout << "  player2 draw:\n";
		size_t p2_total_levels {0};
		for (const auto& card : game.cards.at(1)) {
			std::cout
				<< "    " << card.name << "\n"
				<< "      L:" << card.level << " P:" << card.power << " D:" << card.damage << "\n"
				<< "      A:" << card.ability.string << "\n"
				<< "      F:" << card.faction_bonus.string << "\n";
			p2_total_levels += card.level;
		}
		std::cout << "    total levels: " << p2_total_levels << "\n";

		std::cout << "  starting player is p" << game.starting_player+1 << "\n";
	}

	while (game.rounds.size() < 4) {
		const size_t round_idx = game.rounds.size();
		auto& round = game.rounds.emplace_back();
		round.players.at(0) = (game.starting_player+round_idx)%2;
		round.players.at(1) = (game.starting_player+round_idx+1)%2;
		std::cout << "### Round " << game.rounds.size() << " ###\n";

		for (size_t i = 0; i < round.players.size(); i++) {
			std::cout << "Turn " << i+1 << "\n";
			round.turns.emplace_back(turnSelectRandom(rng, game.cards.at(round.players.at(i)), game.cards_used.at(round.players.at(i)), game.vols.at(round.players.at(i))));
			std::cout << "  p" << round.players.at(i)+1 << " chose";
			round.turns.back().printSelection();
		}
		//std::cout << "Turn1\n";
		//// turn 1 - starting_player chooses card open and pots+frenzy hidden
		//round.turns.emplace_back(turnSelectRandom(rng, game.cards.at(round.t1_player), game.vols.at(round.t1_player)));
		//std::cout << "  p" << round.t1_player+1 << " chose";
		//round.turns.back().printSelection();

		//std::cout << "Turn2\n";
		//// turn 2 - other_player chooses card to counter and pots+frenzy
		//round.turns.emplace_back(turnSelectRandom(rng, game.cards.at(round.t2_player), game.vols.at(round.t2_player)));
		//std::cout << "  p" << round.t2_player+1 << " chose";
		//round.turns.back().printSelection();

		std::cout << "Battle\n";

		// battle
		for (size_t i = 0; i < round.card_temps.size(); i++) { // fill in base
			round.card_temps.at(i).power = round.turns.at(i).card().power;
			round.card_temps.at(i).damage = round.turns.at(i).card().damage;
			std::cout << "  p" << round.players.at(i)+1 << " base power:" << round.card_temps.at(i).power << " damage:" << round.card_temps.at(i).damage << "\n";
		}

		// apply frenzy dmg bonus
		for (size_t i = 0; i < round.card_temps.size(); i++) {
			if (round.turns.at(i).frenzy) {
				round.card_temps.at(i).damage += 2;
			}
		}

		for (size_t i = 0; i < round.card_temps.size(); i++) { // apply power and dmg
			apply_ability<Abilities::Power>(round.card_temps.at(i).power, round.turns.at(i).card().ability);
			apply_ability<Abilities::Power>(round.card_temps.at(i).power, round.turns.at(i).card().faction_bonus);
			apply_ability<Abilities::Damage>(round.card_temps.at(i).damage, round.turns.at(i).card().ability);
			apply_ability<Abilities::Damage>(round.card_temps.at(i).damage, round.turns.at(i).card().faction_bonus);
		}

		for (size_t i = 0; i < round.card_temps.size(); i++) { // apply opp power and dmg
			apply_ability<Abilities::OppPower>(round.card_temps.at((i+1)%round.card_temps.size()).power, round.turns.at(i).card().ability);
			apply_ability<Abilities::OppPower>(round.card_temps.at((i+1)%round.card_temps.size()).power, round.turns.at(i).card().faction_bonus);
			apply_ability<Abilities::OppDamage>(round.card_temps.at((i+1)%round.card_temps.size()).damage, round.turns.at(i).card().ability);
			apply_ability<Abilities::OppDamage>(round.card_temps.at((i+1)%round.card_temps.size()).damage, round.turns.at(i).card().faction_bonus);
		}

		for (size_t i = 0; i < round.card_temps.size(); i++) { // fill in base
			std::cout << "  p" << round.players.at(i)+1 << " mod power:" << round.card_temps.at(i).power << " damage:" << round.card_temps.at(i).damage << "\n";
		}

		// calc attack
		for (size_t i = 0; i < round.card_temps.size(); i++) {
			round.card_temps.at(i).attack = round.card_temps.at(i).power * round.turns.at(i).pots;
			std::cout << "  p" << round.players.at(i)+1 << " base attack:" << round.card_temps.at(i).attack << "\n";
		}

		for (size_t i = 0; i < round.card_temps.size(); i++) { // apply attack
			apply_ability<Abilities::Attack>(round.card_temps.at(i).attack, round.turns.at(i).card().ability);
			apply_ability<Abilities::Attack>(round.card_temps.at(i).attack, round.turns.at(i).card().faction_bonus);
		}

		for (size_t i = 0; i < round.card_temps.size(); i++) { // apply opp attack
			apply_ability<Abilities::OppAttack>(round.card_temps.at((i+1)%round.card_temps.size()).attack, round.turns.at(i).card().ability);
			apply_ability<Abilities::OppAttack>(round.card_temps.at((i+1)%round.card_temps.size()).attack, round.turns.at(i).card().faction_bonus);
		}

		for (size_t i = 0; i < round.card_temps.size(); i++) { // fill in base
			std::cout << "  p" << round.players.at(i)+1 << " mod attack:" << round.card_temps.at(i).attack << "\n";
		}

		// decide which card wins
		const size_t winning_card = decide_winning_card(round.turns.at(0), round.card_temps.at(0), round.turns.at(1), round.card_temps.at(1));
		const size_t round_winning_player = round.players.at(winning_card);
		std::cout << "p" << round_winning_player+1 << " deals " << round.card_temps.at(winning_card).damage << " damage\n";

		game.vols.at((round_winning_player+1)%2).hp -= round.card_temps.at(winning_card).damage;

		for (size_t i = 0; i < game.vols.size(); i++) {
			std::cout << "p" << i+1 << " pots:" << game.vols.at(i).pots << " hp:" << game.vols.at(i).hp << "\n";
		}

		if (game.vols.at(0).hp <= 0) {
			std::cout << "p1 died, p2 won\n";
			break;
		} else if (game.vols.at(1).hp <= 0) {
			std::cout << "p2 died, p1 won\n";
			break;
		}
	}

	if (game.vols.at(0).hp > 0 && game.vols.at(1).hp > 0) {
		if (game.vols.at(0).hp > game.vols.at(1).hp) {
			std::cout << "p2 has less hp, p1 won\n";
		} else if (game.vols.at(1).hp > game.vols.at(0).hp) {
			std::cout << "p1 has less hp, p0 won\n";
		} else {
			std::cout << "draw\n";
		}
	}

	return 0;
}

