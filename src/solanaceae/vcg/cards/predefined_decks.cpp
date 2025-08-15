#include "./predefined_decks.hpp"


std::vector<Card> Cards::monster_deck1(void) {
	return {
		{"Living Gargoyle",4,5,8,{"- 1 Opp Damage Min 4"},{"+ 2 Power"},"A living gargoyle out of stone with four arms and leathery wings, perched on a medieval house."},
		{"Beast of the Fields",5,8,6,{"- 8 Opp Attack Min 3"},{"+ 2 Power"},"An ape-like creature with a wolf's head and a bone-blade arm. Extremely dangerous and deadly."},
		{"Giant Centipede",2,4,4,{"+ 8 Attack"},{"+ 2 Power"},"A giant centipede."},
		{"Slicing Mantis",4,6,6,{"Courage: + 3 Power"},{"+ 2 Power"},"A mantis like monster with wings. Extremely dangerous and hungry."},
		{"Troll",3,6,3,{"Heal 2 Max 13"},{"+ 2 Power"},"A large troll that regenerates from wounds. It has brackish skin and is otherwise humanoid, though quite ugly."},
		{"Hell Hornet",3,6,3,{"Poison 1 Min 0"},{"+ 2 Power"},"A giant red-black hornet with a burning venom in its stinger."},
		{"Werewolf",3,5,5,{"Steal 1 Life Min 1"},{"+ 2 Power"},"A fucking werewolf."},
		{"Poison Lizard",3,6,4,{"Stop Opp Ability"},{"+ 2 Power"},"A poisonous lizard, which is emitting a disgusting stench."},
	};
}

std::vector<Card> Cards::monster_cleric_deck1(void) {
	return {
		{"Living Gargoyle",4,5,8,{"- 1 Opp Damage Min 4"},{"+ 2 Power"},"A living gargoyle out of stone with four arms and leathery wings, perched on a medieval house."},
		{"Slicing Mantis",4,6,6,{"Courage: + 3 Power"},{"+ 2 Power"},"A mantis like monster with wings. Extremely dangerous and hungry."},
		{"Werewolf",3,5,5,{"Steal 1 Life Min 1"},{"+ 2 Power"},"A fucking werewolf."},
		{"Snapper",3,7,2,{"Team: + 1 Damage"},{"+ 2 Power"},"A small, t-rex like creature that hunts in packs."},

		{"Life Cleric",5,6,2,{"+ 3 Life per Damage"},{"Stop Opp Ability"},"The Life Cleric wears golden robes and heals everyone, poor or rings."},
		{"Nature Cleric",3,7,2,{"+ 3 Potion"},{"Stop Opp Ability"},"The Nature Cleric has green robes and knows how to tend plants."},
		{"Inquisitor",3,7,1,{"Stop: + 6 Damage"},{"Stop Opp Ability"},"The Inquisitor is there to charge those that do wrong. He wears heavy brown robes and metal armor underneath."},
		{"Mass Preparer",2,6,1,{"Team: + 1 Life"},{"Stop Opp Ability"},"The Mass Preparer is most often found in the backrooms of temples, helping to set up the masses."},
	};
}

std::vector<Card> Cards::aberration_parasites_deck1(void) {
	return {
		{"Slitherer",3,7,3,{"+ 8 Attack"},{"Stop Opp Bonus"},"A snake-like creature that splits up into a mass of snakes."},
		{"Razer",2,6,5,{"Backlash: - 3 Life Min 0"},{"Stop Opp Bonus"},"A small grey creature with blade-like arms and a sleek head."},
		{"Shellshocker",4,5,7,{"Courage: - 3 Opp Power Min 4"},{"Stop Opp Bonus"},"A huge, grey crab-like creature with lightning arcing between parts of its bodies."},
		{"Doppelganger",4,7,7,{"Damage = Opp Damage"},{"Stop Opp Bonus"},"A greyish blue humanoid creature that can change its body at will into other creatures, creating a perfect copy in the process."},

		{"River Stench",5,8,5,{"- 12 Opp Attack Min 12"},{"Poison 2 Min 3"},"As one of the deadliest Parasites, the River Stench is hard to be avoided. Humans need water, but if the River Stench has taken over a water source, all of the water down stream is basically undrinkable, unless you want to die in the next three days."},
		{"Spore King",5,7,6,{"Defeat: Heal 3 Max 9"},{"Poison 2 Min 3"},"The Spore King is a gargantuan mass of colorful spores that moves around the land and overtakes every organic matter it can find. It does not matter whether its a living creature or plant life, everything gets integrated."},
		{"Plaguebearer",4,7,5,{"Stop Opp Ability"},{"Poison 2 Min 3"},"A Plaguebearer is a sloth-like creature that carries an immense stench with it. Creatures that smell this stench have a high chance of getting decomposed from the gases that the Plaguebearer emits, turning themselves into small ovens of this stench. Plaguebearers love this smell and love to eat those that smell like that."},
		{"Pandemic Oven",3,7,3,{"Stop Opp Bonus"},{"Poison 2 Min 3"},"Feeling like the flu at first, the Pandemic Oven heats up infected creatures, making them seek out water to cool themselves down. Inside of the water, the Pandemic Oven then release its small children through the skin of its victim, which then search for other hosts to heat up."},
	};
}

