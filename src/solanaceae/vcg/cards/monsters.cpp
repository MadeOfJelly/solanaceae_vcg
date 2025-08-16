#include "./monsters.hpp"

std::vector<Card> Cards::monsters(void) {
	return {
		{"Living Gargoyle",4,5,8,{"- 1 Opp Damage Min 4"},{"+ 2 Power"},"A living gargoyle out of stone with four arms and leathery wings, perched on a medieval house."},
		{"Basilisk",3,7,4,{"- 1 Opp Power Min 5"},{"+ 2 Power"},"The Basilisk is a hard skinned monster with greyish skin that turns any living creature that looks at it too long into stone. Its blue eyes pierce the night, while is teeth are not only sharp but can easily devour stone."},
		{"Mountain Troll",5,7,8,{"- 2 Opp Damage Min 5"},{"+ 2 Power"},"A gargantuan ape-like creature covered in heavy fur with stone-like skin."},
		{"Beast of the Fields",5,8,6,{"- 8 Opp Attack Min 3"},{"+ 2 Power"},"An ape-like creature with a wolf's head and a bone-blade arm. Extremely dangerous and deadly."},
		{"Blood Fly",2,5,4,{"+ 1 Life"},{"+ 2 Power"},"Blood flies have different colors based on the fauna that surrounds them. They possess a large stinger at the back of their tail that they use to paralyze and then kill their targets. Their four wings allow them to fly in nearly any direction out of any position, though they seem to have problems flying higher than a few feet off the ground."},
		{"Red Dragon",5,8,6,{"+ 2 Damage"},{"+ 2 Power"},"A red dragon that spews mountains of fire at its victims."},
		{"Burrower",3,6,4,{"+ 2 Power"},{"+ 2 Power"},"A mole like creature with blade-like claws and a sturdy armor like an armadillo."},
		{"Giant Centipede",2,4,4,{"+ 8 Attack"},{"+ 2 Power"},"A giant centipede."},
		{"Slicing Mantis",4,6,6,{"Courage: + 3 Power"},{"+ 2 Power"},"A mantis like monster with wings. Extremely dangerous and hungry."},
		{"Storm Shark",3,8,3,{"Defeat: - 1 Opp Life Min 4"},{"+ 2 Power"},"A snake like creature with small legs that moves very fast. Lightning arcs across its greyish blue body."},
		{"Troll",3,6,3,{"Heal 2 Max 13"},{"+ 2 Power"},"A large troll that regenerates from wounds. It has brackish skin and is otherwise humanoid, though quite ugly."},
		{"Hell Hornet",3,6,3,{"Poison 1 Min 0"},{"+ 2 Power"},"A giant red-black hornet with a burning venom in its stinger."},
		{"Sea Serpent",5,7,7,{"Poison 1 Min 1"},{"+ 2 Power"},"A gargantuan serpent that not only poisons but also devours its victims entirely if they are small enough."},
		{"Rabies Bison",2,5,2,{"Power = Opp Power"},{"+ 2 Power"},"A bison with rabies. It is volatile and angry."},
		{"Mutated Gorilla",4,7,6,{"Revenge: + 1 Power"},{"+ 2 Power"},"Usually found in jungle-like biomes, this gorilla like monster possesses 4 massive arms to are able to break any creature."},
		{"Flooded Spirit",3,6,5,{"Revenge: Stop Opp Bonus"},{"+ 2 Power"},"A creature made of mud that can cover large distances quickly and resembles a flowing humanoid."},
		{"Werewolf",3,5,5,{"Steal 1 Life Min 1"},{"+ 2 Power"},"A fucking werewolf."},
		{"Poison Lizard",3,6,4,{"Stop Opp Ability"},{"+ 2 Power"},"A poisonous lizard, which is emitting a disgusting stench."},
		{"Hydra",4,8,4,{"Stop: - 3 Opp Life Min 2"},{"+ 2 Power"},"A five-headed hydra."},
		{"Sandworm",4,6,7,{"Stop: + 1 Power"},{"+ 2 Power"},"A gargantuan sandworm that expulses sand at high speeds from its body and grinds down its victims with endless teeth."},
		{"Snapper",3,7,2,{"Team: + 1 Damage"},{"+ 2 Power"},"A small, t-rex like creature that hunts in packs."},
	};
}
