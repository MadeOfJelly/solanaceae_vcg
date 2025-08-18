#include "./battle.hpp"
#include "./card.hpp"
#include "./game_state.hpp"

#include <random>
#include <iostream>

// fixed seed
static std::default_random_engine rng{1337*13};

#define A(x) if(!(x)) { std::cerr << "ASSERT(" __FILE__ ":" << __LINE__ << ") failed: '" #x "'\n"; return false; }

bool simple_full_battle1(void) {
	// simple spread easy_cards across the two players
	GameState gs{
		{
			{"Living Gargoyle",		4,5,8,{"- 1 Opp Damage Min 3"},	{"+ 2 Power"},"A gargoyle made of stone that is alive."},
			{"Basilisk",			3,7,4,{"- 1 Opp Power Min 4"},	{"+ 2 Power"},"A basilisk."},
			{"Mountain Troll",		5,7,8,{"- 2 Opp Damage Min 5"},	{"+ 2 Power"},"An ape-like creature covered in heavy fur with stone-like skin."},
			{"Beast of the Fields",	5,8,6,{"- 8 Opp Attack Min 10"},{"+ 2 Power"},"An ape-like creature with a wolf's head and a bone-blade arm. Extremely dangerous and deadly."},
		},
		{
			{"Rabies Bison",		2,6,3,{"+ 1 Damage"},			{"+ 2 Power"},"A bison with rabies. It is volatile and angry."},
			{"Red Dragon",			5,8,6,{"+ 2 Damage"},			{"+ 2 Power"},"A red dragon that spews mountains of fire at its victims."},
			{"Burrower",			3,6,4,{"+ 2 Power"},			{"+ 2 Power"},"A mole like creature with blade-like claws and a sturdy armor like an armadillo."},
			{"Monster8",			3,8,3,{"+ 4 Attack"},			{"+ 2 Power"},"A snake like creature with small legs that moves very fast."},
		}
	};

	gs.determineStartingPlayer(rng);

	A(gs.starting_player == 0);

	{ // round 1
		// construct current round
		Round round{};
		round.players.at(0) = gs.nextRoundStartingPlayer();
		round.players.at(1) = (round.players.at(0)+1)%2;

		round.turns.emplace_back(TurnSelection{
			gs.cards.at(round.players.at(0)),
			3, // beast
			2,
			false
		});
		// 8+2 * 3 -> 30 atk

		round.turns.emplace_back(TurnSelection{
			gs.cards.at(round.players.at(1)),
			2, // burrower
			1,
			false
		});
		// 6+2+2 * 2 -> 20 - 8 -> 12

		battle(gs, round);

		A(round.decide_winning_card().idx == 0);

		A(round.card_temps.at(0).attack == 30);
		A(round.card_temps.at(1).attack == 12);

		A(round.heals.at(0).empty());
		A(round.heals.at(1).empty());
		A(round.poisons.at(0).empty());
		A(round.poisons.at(1).empty());

		A(gs.update(round));

		A(gs.vols.at(0).hp == 12);
		A(gs.vols.at(1).hp == 6);
	}

	{ // round invalid
		// same cards, to trigger gs.update() validation
		// construct current round
		Round round{};
		round.players.at(0) = gs.nextRoundStartingPlayer();
		round.players.at(1) = (round.players.at(0)+1)%2;

		// order is now switched (bc next turn)
		round.turns.emplace_back(TurnSelection{
			gs.cards.at(round.players.at(0)),
			2, // burrower
			1,
			false
		});

		round.turns.emplace_back(TurnSelection{
			gs.cards.at(round.players.at(1)),
			3, // beast
			2,
			false
		});

		// skipping battle

		A(!gs.update(round));
	}


	return true;
}

int main(void) {
	if (!simple_full_battle1()) {
		std::cerr << "simple_full_battle1 failed\n";
		return 1;
	}

	std::cout << "all battle tests succeeded\n";
	return 0;
}
