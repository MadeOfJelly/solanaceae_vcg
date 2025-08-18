#include "./clerics.hpp"

std::vector<Card> Cards::clerics(void) {
	return {
		{"Mass Servant",2,5,3,{"- 2 Opp Damage Min 1"},{"Stop Opp Ability"},"The Mass Serant is dressed in simple robes and always there to accomodate the priests and Clerics."},
		{"Hollow Cleric",4,7,3,{"- 4 Opp Life Min 2"},{"Stop Opp Ability"},"The Hollow Cleric is ready to fill the emptyness in your heart. His robes are of a dark blue color and reflect the sunlight."},
		{"Prophet",4,8,2,{"- 4 Opp Potion Min 2"},{"Stop Opp Ability"},"The Prophet is one of a kind, foretold by the scriptures. He is as charismatic as he is strong and he wears the finest Cleric clothes."},
		{"Peace Cleric",4,7,3,{"- 5 Opp Damage Min 2"},{"Stop Opp Ability"},"The Piece Cleric is keeping peace among all. He wears simple brown robes and is very old."},
		{"Tempest Cleric",3,8,2,{"- 8 Opp Attack Min 3"},{"Stop Opp Ability"},"The Tempest Cleric's robes are of grey color and very light, almost floaty."},
		{"Water Cleric",4,5,6,{"+ 12 Attack"},{"Stop Opp Ability"},"The Water Cleric wears bright blue robes and is mostly found blessing barrels and fountains of water."},
		{"Life Cleric",5,6,2,{"+ 3 Life per Damage"},{"Stop Opp Ability"},"The Life Cleric wears golden robes and heals everyone, poor or rings."},
		{"Nature Cleric",3,7,2,{"+ 3 Potion"},{"Stop Opp Ability"},"The Nature Cleric has green robes and knows how to tend plants."},
		{"War Cleric",4,7,5,{"Courage: Heal 2 Max 15"},{"Stop Opp Ability"},"The War Cleric wears heavy metal armor underneath his robes and carries a battleaxe and shield."},
		{"Oracle",4,5,5,{"Defeat: - 3 Opp Life Min 0"},{"Stop Opp Ability"},"The Oracle wears ragged clothing and is mostly found in its room with different smells and scents."},
		{"Acolyte",3,7,3,{"Heal 1 Max 15"},{"Stop Opp Ability"},"The Acolyte is there to help in the masses and help the Clerics with things."},
		{"Preacher",2,6,2,{"Heal 2 Max 10"},{"Stop Opp Ability"},"The Preacher stands out on the marketplace and ushers citizens to the temples of the Clerics."},
		{"Death Cleric",5,8,1,{"Poison 3 Min 0"},{"Stop Opp Ability"},"The Death Cleric wears dark green robes and carries an orb with him."},
		{"Nightmare Cleric",3,4,6,{"Revenge: + 3 Power"},{"Stop Opp Ability"},"The Nightmare Cleric helps people with their nightmares and is wrapped in bright white robes with dark dots."},
		{"Vengeance Cleric",5,7,5,{"Revenge: + 5 Damage"},{"Stop Opp Ability"},"The Vengeance Cleric has a small piece of paper with him at all times. His robes are of red color."},
		{"Pastor",3,6,4,{"Stop Opp Bonus"},{"Stop Opp Ability"},"The Pastor prays to the gods and has information from the many people that talk to him."},
		{"Stability Cleric",4,7,5,{"Stop Opp Bonus"},{"Stop Opp Ability"},"The Stability Cleric keeps things as they are and is mostly carrying around scriptures and books. His robes are of silver color."},
		{"Inquisitor",3,7,1,{"Stop: + 6 Damage"},{"Stop Opp Ability"},"The Inquisitor is there to charge those that do wrong. He wears heavy brown robes and metal armor underneath."},
		{"Mass Preparer",2,6,1,{"Team: + 1 Life"},{"Stop Opp Ability"},"The Mass Preparer is most often found in the backrooms of temples, helping to set up the masses."},
		{"Union Cleric",3,6,3,{"Team: + 1 Power"},{"Stop Opp Ability"},"The Union Cleric is there to help all Clerics together. He wears no robes at all, but a uniform. Although he still carries a priest's staff with him."},
	};
}
