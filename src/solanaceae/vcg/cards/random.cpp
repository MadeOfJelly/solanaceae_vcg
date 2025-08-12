#include "./random.hpp"

std::vector<Card> Cards::random(void) {
	return {
		//{"Living Gargoyle",		4,5,8,{"- 1 Opp Damage Min 3"},	{"+ 2 Power"},"A gargoyle made of stone that is alive."},
		//{"Basilisk",			3,7,4,{"- 1 Opp Power Min 4"},	{"+ 2 Power"},"A basilisk."},
		//{"Mountain Troll",		5,7,8,{"- 2 Opp Damage Min 5"},	{"+ 2 Power"},"An ape-like creature covered in heavy fur with stone-like skin."},
		//{"Beast of the Fields",	5,8,6,{"- 8 Opp Attack Min 10"},{"+ 2 Power"},"An ape-like creature with a wolf's head and a bone-blade arm. Extremely dangerous and deadly."},
		//{"Rabies Bison",		2,6,3,{"+ 1 Damage"},			{"+ 2 Power"},"A bison with rabies. It is volatile and angry."},
		//{"Red Dragon",			5,8,6,{"+ 2 Damage"},			{"+ 2 Power"},"A red dragon that spews mountains of fire at its victims."},
		//{"Burrower",			3,6,4,{"+ 2 Power"},			{"+ 2 Power"},"A mole like creature with blade-like claws and a sturdy armor like an armadillo."},
		//{"Monster8",			3,8,3,{"+ 4 Attack"},			{"+ 2 Power"},"A snake like creature with small legs that moves very fast."},

		// selectin of assassins that are currently supported
		//{"Frontman",2,5,3,{"- 2 Opp Damage Min 3"},{"- 2 Opp Power Min 1"},"The Front looks nice and accomodating and usually handles the business of the Assassins with new clients."},
		//{"Fake Colleague",2,4,3,{"- 2 Opp Power Min 1"},{"- 2 Opp Power Min 1"},"The Fake Colleague infiltrates work gatherings and jobs to get into every house and every corner of the city."},
		//{"Tracker",2,6,2,{"+ 4 Attack"},{"- 2 Opp Power Min 1"},"The Tracker uses his trusty dogs to find anyone in the city."},
		//{"Dissolver",3,7,1,{"- 2 Opp Life Min 0"},{"- 2 Opp Power Min 1"},"The Dissolver is somewhat an alchemist, though he only knows his way around acids. Three of his fingers and many of his teeth are already missing, just like all of his victims."},
		//{"Infiltrator",3,6,3,{"- 2 Opp Power Min 5"},{"- 2 Opp Power Min 1"},"The Infiltrator can get into any building at any time to the day. A grappling hook, rope and some lockpicks are all he needs."},
		//{"Cutthroat",3,8,2,{"- 4 Opp Attack Min 1"},{"- 2 Opp Power Min 1"},"The Cutthroat comes at you when its most unexpected and rams a knife into your throat, leaving you to bleed out while he is already gone."},
		////{"Suicide Bomber",3,6,4,{"Defeat: Poison 2 Min 5"},{"- 2 Opp Power Min 1"},"The Suicide Bomber only has one job, which is to blow shit up. Equipped with an explosive vest if things go wrong, he can blow everyone else up with him. However, so far his bombs sufficed."},
		//{"Blackmailer",4,7,3,{"- 3 Opp Potion Min 2"},{"- 2 Opp Power Min 1"},"The Blackmailer is not so much an Assassins as he knows to psychologically kill his victims by extorting money through body parts of missing family members or regular visits at their homes."},

		// mage selection
		{"Potion Keeper",2,6,1,{"+ 3 Potion"},{"+ 2 Damage"},"The Potion Keeper keeps the shelves stocked with Potions. He knows where to find which one."},
		{"Magical Enchanter",3,8,2,{"- 2 Opp Damage Min 1"},{"+ 2 Damage"},"The Magical Enchanter is seen with weird glassware used to enchant weapons, armors and regular items to give them magical effects."},
		{"Transmutation Mage",3,7,3,{"- 2 Opp Power Min 5"},{"+ 2 Damage"},"The Transmutation Mage can change matter from one to another. Stone into wood, wood into water, nothing is beyond limits."},
		{"Enchantment Mage",3,6,3,{"- 3 Opp Potion Min 3"},{"+ 2 Damage"},"The Enchantment Mage specializes in magic that enhances creatures. Whether that is increasing their physical power or mental capacities is up to him."},
		{"Illusion Mage",3,4,4,{"- 4 Opp Power Min 3"},{"+ 2 Damage"},"The Illusion Mage is able to produce illusions of anything. Even dragons aren't safe of being brought to life in images by him."},
		{"Conjuration Mage",3,7,3,{"+ 2 Power"},{"+ 2 Damage"},"The Conjuration Mage can summon magical creatures like fire elementals from thin air."},
		{"Necromancer",3,7,2,{"Defeat: + 3 Life"},{"+ 2 Damage"},"The Necromancer is hated, but can turn the tide of a battle by making the dead rise and fight again."},
		{"Spellblade",4,7,4,{"- 3 Opp Power Min 5"},{"+ 2 Damage"},"The Spellblade combines magic and swordfighting to achieve a dangerous combo of magical and physical warfare."},
		{"Evocation Mage",4,6,6,{"+ 2 Damage"},{"+ 2 Damage"},"The Evocation Mage is responsible for fireballs and big explosions. His spells devastate entire neighbourhoods."},
		{"Abjuration Mage",5,7,5,{"- 5 Opp Damage Min 2"},{"+ 2 Damage"},"The Abjuration mage is able to block any attack with magical force fields."},
		{"Destruction Mage",5,8,4,{"- 5 Opp Potion Min 5"},{"+ 2 Damage"},"The Destruction Mage evaporates matter, no matter if it is organic or not. When he points his finger at someone, they turn to dust."},
	};
}
