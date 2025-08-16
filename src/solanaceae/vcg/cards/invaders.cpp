#include "./invaders.hpp"

std::vector<Card> Cards::invaders(void) {
	return {
		{"Scout",2,6,2,{"- 2 Opp Damage Min 1"},{"- 8 Opp Attack Min 3"},"The Scout is hidden in the bushes and takes watch."},
		{"Demolitionist",4,7,4,{"- 3 Opp Life Min 2"},{"- 8 Opp Attack Min 3"},"The Demolitionist knows how to make bombs and blow up buildings or palisades. His skin is burned, but he is still smiling."},
		{"Commander",5,7,6,{"- 4 Opp Damage Min 2"},{"- 8 Opp Attack Min 3"},"The Commander leads the troups into battle and is usually on a horse."},
		{"Strategist",4,6,6,{"- 8 Opp Attack Min 3"},{"- 8 Opp Attack Min 3"},"The Strategist knows when to enter a village and how. He creates small battlemaps while still leading the charge in his heavy plate armor."},
		{"Ration Keeper",3,6,3,{"+ 3 Life"},{"- 8 Opp Attack Min 3"},"The Ration Keeper gives out food and water and is almost a small king among the Invaders."},
		{"Polisher",3,6,4,{"+ 8 Attack"},{"- 8 Opp Attack Min 3"},"The Polisher makes sure that the equipment of the Invaders is clean and in good shape."},
		{"Cannonist",5,6,8,{"Courage: - 12 Opp Attack Min 12"},{"- 8 Opp Attack Min 3"},"The Cannonist knows how to angle a cannon to hit the target."},
		{"Warlord",5,8,6,{"Courage: - 3 Opp Power Min 4"},{"- 8 Opp Attack Min 3"},"The Warlord has come to conquer and he will conquer. No one will stand in his way, when he comes with his traditional armor."},
		{"Field Medic",2,5,3,{"Heal 2 Max 10"},{"- 8 Opp Attack Min 3"},"The Field Medic knows how to treat wounds that appear on the battlefield, but he doesn't know how to fight himself."},
		{"Traveling Cook",3,7,3,{"Poison 2 Min 3"},{"- 8 Opp Attack Min 3"},"The Traveling Cook knows his way around poisons and is able to cook hearty meals that make your heart stop."},
		{"Pillager",2,5,3,{"Steal 1 Life Min 1"},{"- 8 Opp Attack Min 3"},"The Pillager burns down anything he finds after he has taken all the valuables."},
		{"Polymath",4,6,6,{"Stop Opp Ability"},{"- 8 Opp Attack Min 3"},"The Polymath calculates the flight path of catapults and cannons and also knows about local fauna and flora. He is old and has grey hair."},
		{"Wallclimber",3,7,3,{"Stop Opp Ability"},{"- 8 Opp Attack Min 3"},"The Wallclimber knows how to climb any wall and is able to get over them easily."},
		{"Archer",2,6,2,{"Stop Opp Bonus"},{"- 8 Opp Attack Min 3"},"The Archer is skilled with his bow and attacks from a distance."},
		{"Foreign King",5,7,7,{"Stop Opp Bonus"},{"- 8 Opp Attack Min 3"},"The Foreign King wants to increase the size of his country and has therefore determined that your city will be included in his empire. For this he can chill in his throne room and his throne and wear his crown."},
		{"Foreign Soldier",3,6,4,{"Stop Opp Bonus"},{"- 8 Opp Attack Min 3"},"The Foreign Soldier comes from another country and employs unknown fighting techniques and weaponry like scimitars."},
		{"Flanker",4,5,7,{"Stop: - 3 Opp Power Min 3"},{"- 8 Opp Attack Min 3"},"The Flanker comes from behind usually and is able to bring chaos to enemy troups."},
		{"Brandisher",3,5,4,{"Team: - 1 Opp Power Min 4"},{"- 8 Opp Attack Min 3"},"The Brandisher knows how to swing around a multitude of weapons all at once, but he needs to be provided with them."},
		{"Sharpener",4,6,6,{"Team: + 3 Attack"},{"- 8 Opp Attack Min 3"},"The Sharpener loves to sharpen swords, axes and arrow heads to maximize their impact."},
	};
}
