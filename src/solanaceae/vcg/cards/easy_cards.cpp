#include "./easy_cards.hpp"

std::vector<Card> Cards::easy_cards(void) {
	return {
		{"Living Gargoyle",		4,5,8,{"- 1 Opp Damage Min 3"},	{"+ 2 Power"},"A gargoyle made of stone that is alive."},
		{"Basilisk",			3,7,4,{"- 1 Opp Power Min 4"},	{"+ 2 Power"},"A basilisk."},
		{"Mountain Troll",		5,7,8,{"- 2 Opp Damage Min 5"},	{"+ 2 Power"},"An ape-like creature covered in heavy fur with stone-like skin."},
		{"Beast of the Fields",	5,8,6,{"- 8 Opp Attack Min 10"},{"+ 2 Power"},"An ape-like creature with a wolf's head and a bone-blade arm. Extremely dangerous and deadly."},
		{"Rabies Bison",		2,6,3,{"+ 1 Damage"},			{"+ 2 Power"},"A bison with rabies. It is volatile and angry."},
		{"Red Dragon",			5,8,6,{"+ 2 Damage"},			{"+ 2 Power"},"A red dragon that spews mountains of fire at its victims."},
		{"Burrower",			3,6,4,{"+ 2 Power"},			{"+ 2 Power"},"A mole like creature with blade-like claws and a sturdy armor like an armadillo."},
		{"Monster8",			3,8,3,{"+ 4 Attack"},			{"+ 2 Power"},"A snake like creature with small legs that moves very fast."},
	};
}
