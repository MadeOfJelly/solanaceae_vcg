#include "./random.hpp"

std::vector<Card> Cards::random(void) {
	return {
		{"Living Gargoyle",		4,5,8,{"- 1 Opp Damage Min 3"},	{"+ 2 Power"},"A gargoyle made of stone that is alive."},
		{"Basilisk",			3,7,4,{"- 1 Opp Power Min 4"},	{"+ 2 Power"},"A basilisk."},
		{"Mountain Troll",		5,7,8,{"- 2 Opp Damage Min 5"},	{"+ 2 Power"},"An ape-like creature covered in heavy fur with stone-like skin."},
		{"Beast of the Fields",	5,8,6,{"- 8 Opp Attack Min 10"},{"+ 2 Power"},"An ape-like creature with a wolf's head and a bone-blade arm. Extremely dangerous and deadly."},
		{"Rabies Bison",		2,6,3,{"+ 1 Damage"},			{"+ 2 Power"},"A bison with rabies. It is volatile and angry."},
		{"Red Dragon",			5,8,6,{"+ 2 Damage"},			{"+ 2 Power"},"A red dragon that spews mountains of fire at its victims."},
		{"Burrower",			3,6,4,{"+ 2 Power"},			{"+ 2 Power"},"A mole like creature with blade-like claws and a sturdy armor like an armadillo."},
		{"Monster8",			3,8,3,{"+ 4 Attack"},			{"+ 2 Power"},"A snake like creature with small legs that moves very fast."},

		// aberrations selection
		//{"Bone Monger",3,5,5,{"- 2 Opp Damage Min 1"},{"Stop Opp Bonus"},"A humanoid fleshy creature with the bones of its victims attached to its body. Teeth spike from all parts of its body."},
		//{"Cloaker",3,5,5,{"- 2 Opp Power Min 4"},{"Stop Opp Bonus"},"An invisible flying creature that is rarely seen, though it sparkles in light. It looks similar to a devilfish."},
		//{"Ripper",2,6,1,{"- 3 Opp Damage Min 2"},{"Stop Opp Bonus"},"A humanoid creature that strips its body of its flesh to attack anything suitable for consumption. Its own flesh is stripped of similar to what it does to its victims"},
		//{"Eye Wolf",3,5,3,{"- 4 Opp Power Min 4"},{"Stop Opp Bonus"},"A wolf-like creature with green eyes covering its entire body."},
		//{"Devourer",3,6,3,{"+ 1 Life per Damage"},{"Stop Opp Bonus"},"A mass of fleshy mouths with different kind of teeth all over its body."},
		//{"Splitter",3,7,3,{"+ 2 Power"},{"Stop Opp Bonus"},"A large mouth sits on a blueish hairy humanoid body with 2 arms that splits into 4 arms."},
		//{"Gobbler",2,6,1,{"+ 3 Life"},{"Stop Opp Bonus"},"A small baby-like creature with an insanely large mouth."},
		//{"Slitherer",3,7,3,{"+ 8 Attack"},{"Stop Opp Bonus"},"A snake-like creature that splits up into a mass of snakes."},
		//{"Shellshocker",4,5,7,{"Courage: - 3 Opp Power Min 4"},{"Stop Opp Bonus"},"A huge, grey crab-like creature with lightning arcing between parts of its bodies."},
		//{"Doppelganger",4,7,7,{"Damage = Opp Damage"},{"Stop Opp Bonus"},"A greyish blue humanoid creature that can change its body at will into other creatures, creating a perfect copy in the process."},
		//{"Tendril Bearer",5,7,6,{"Defeat: - 3 Opp Life Min 2"},{"Stop Opp Bonus"},"A hulking, hairy mass of a beast with fleshy tendrils and tentacles coming out of many parts of its body."},
		//{"Brain Dragon",5,7,7,{"Stop Opp Ability"},{"Stop Opp Bonus"},"A dragon with a gigantic brain mounted on its back that slithers to the wings and its head."},
		//{"Evil Eye",4,6,6,{"Stop Opp Ability"},{"Stop Opp Bonus"},"A flying eye with immense pressure it opposes on creatures around it."},

		// clerics selection
		//{"Mass Servant",2,5,3,{"- 2 Opp Damage Min 1"},{"Stop Opp Ability"},"The Mass Serant is dressed in simple robes and always there to accomodate the priests and Clerics."},
		//{"Hollow Cleric",4,7,3,{"- 4 Opp Life Min 2"},{"Stop Opp Ability"},"The Hollow Cleric is ready to fill the emptyness in your heart. His robes are of a dark blue color and reflect the sunlight."},
		//{"Prophet",4,8,2,{"- 4 Opp Potion Min 2"},{"Stop Opp Ability"},"The Prophet is one of a kind, foretold by the scriptures. He is as charismatic as he is strong and he wears the finest Cleric clothes."},
		//{"Peace Cleric",4,7,3,{"- 5 Opp Damage Min 2"},{"Stop Opp Ability"},"The Piece Cleric is keeping peace among all. He wears simple brown robes and is very old."},
		//{"Tempest Cleric",3,8,2,{"- 8 Opp Attack Min 3"},{"Stop Opp Ability"},"The Tempest Cleric's robes are of grey color and very light, almost floaty."},
		//{"Water Cleric",4,5,6,{"+ 12 Attack"},{"Stop Opp Ability"},"The Water Cleric wears bright blue robes and is mostly found blessing barrels and fountains of water."},
		//{"Life Cleric",5,6,2,{"+ 3 Life per Damage"},{"Stop Opp Ability"},"The Life Cleric wears golden robes and heals everyone, poor or rings."},
		//{"Nature Cleric",3,7,2,{"+ 3 Potion"},{"Stop Opp Ability"},"The Nature Cleric has green robes and knows how to tend plants."},
		//{"War Cleric",4,7,5,{"Courage: + 3 Power"},{"Stop Opp Ability"},"The War Cleric wears heavy metal armor underneath his robes and carries a battleaxe and shield."},
		//{"Oracle",4,5,5,{"Defeat: - 3 Opp Life Min 0"},{"Stop Opp Ability"},"The Oracle wears ragged clothing and is mostly found in its room with different smells and scents."},
		{"Nightmare Cleric",3,4,6,{"Revenge: + 3 Power"},{"Stop Opp Ability"},"The Nightmare Cleric helps people with their nightmares and is wrapped in bright white robes with dark dots."},
		{"Vengeance Cleric",5,7,5,{"Revenge: + 5 Damage"},{"Stop Opp Ability"},"The Vengeance Cleric has a small piece of paper with him at all times. His robes are of red color."},
		//{"Pastor",3,6,4,{"Stop Opp Bonus"},{"Stop Opp Ability"},"The Pastor prays to the gods and has information from the many people that talk to him."},
		//{"Stability Cleric",4,7,5,{"Stop Opp Bonus"},{"Stop Opp Ability"},"The Stability Cleric keeps things as they are and is mostly carrying around scriptures and books. His robes are of silver color."},
		{"Inquisitor",3,7,1,{"Stop: + 6 Damage"},{"Stop Opp Ability"},"The Inquisitor is there to charge those that do wrong. He wears heavy brown robes and metal armor underneath."},
	};
}
