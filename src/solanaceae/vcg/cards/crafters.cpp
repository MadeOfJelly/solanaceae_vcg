#include "./crafters.hpp"

std::vector<Card> Cards::crafters(void) {
	return {
		{"Toymaker",2,5,3,{"- 3 Opp Damage Min 2"},{"Defeat: Recover 1 of 2 Potion"},"Loved by the kids, the Toymaker is a specialist for small craftsmenship. His smile is calm and inviting, just like his white shirt with straps. However, don't forget that carving equipment for wooden toys can still be used on flesh."},
		{"Cobbler",3,5,5,{"- 3 Opp Power Min 5"},{"Defeat: Recover 1 of 2 Potion"},"As an important personality in the city, the Cobbler is always asked for. Everyone wants to walk the walk and talk the talk, but only with his shoes that is possible. Though as good they can be, they can be bad and the cobbling tools might also get used in a different way."},
		{"Leatherworker",4,7,5,{"- 5 Opp Damage Min 4"},{"Defeat: Recover 1 of 2 Potion"},"The Leatherworker can be found tanning leather or crafting clothing from leather in his shop."},
		{"Blacksmith",5,8,6,{"+ 12 Attack"},{"Defeat: Recover 1 of 2 Potion"},"The Blacksmith is a blacksmith and known for making things out of metal. Weapons are a speciality of his."},
		{"Baker",3,7,3,{"+ 3 Life"},{"Defeat: Recover 1 of 2 Potion"},"The Baker is known around the city, as many people interact with him daily. Always a bit dusty from the flower, but boasting large forearms, he knows how to knead."},
		{"Head Alchemist",5,7,7,{"+ 3 Potion"},{"Defeat: Recover 1 of 2 Potion"},"The Head Alchemist is a master of potions and brews. His shop is littered with potion bottles of all colors."},
		{"Enchanter",5,6,8,{"+ 3 Power"},{"Defeat: Recover 1 of 2 Potion"},"The Enchanter is highly sought after, as he magically enchants both common household items and combat equipment as well."},
		{"Apprentice",2,4,4,{"Courage: + 4 Power"},{"Defeat: Recover 1 of 2 Potion"},"The Apprentice is still learning, but his clothes are already dirty from learning from the masters. He is young and inexperienced."},
		{"Storage Keeper",2,6,2,{"Defeat: - 2 Opp Life Min 2"},{"Defeat: Recover 1 of 2 Potion"},"Always seen around the warehouse, the Storage Keeper boasts a large key chain. He knows his warehouse by heart and where which key fits."},
		{"Recycler",3,6,5,{"Defeat: Recover 1 of 2 Potion"},{"Defeat: Recover 1 of 2 Potion"},"The Recycler is always tinkering with things and able to extract gems from jewelery and special parts from toys, while also being able to work on potions."},
		{"Glasblower",2,6,2,{"Poison 2 Min 2"},{"Defeat: Recover 1 of 2 Potion"},"Be careful around the Glasblower and don't get distracted by his colorful outfit. Glass hurts both when it is molten and when it is shattered."},
		{"Carpenter",4,6,6,{"Revenge: - 14 Opp Attack Min 4"},{"Defeat: Recover 1 of 2 Potion"},"Working all around the city, you don't want to get on the bad side of the Carpenter. If he doesn't like you you can bet on your house and bed collapsing in the next few days."},
		{"Armorer",5,8,7,{"Revenge: - 3 Opp Damage Min 2"},{"Defeat: Recover 1 of 2 Potion"},"The Armorer creates armor from leather and metal. Chain shirts, plate armor, light undergarnments, whatever you desire, he can make it."},
		{"Potter",3,7,3,{"Revenge: + 4 Damage"},{"Defeat: Recover 1 of 2 Potion"},"Living a simple life, the Potter is just as great at throwing pots than he is at making them. Clay also makes an excellent armor as long as it has the right consistency."},
		{"Scrivener",3,6,4,{"Stop Opp Ability"},{"Defeat: Recover 1 of 2 Potion"},"Things need to be written and things need to be copied, which is the Scrivener's job. This puts him into contact with a lot of paper, but also a lot of information."},
		{"Stonemason",4,8,4,{"Stop Opp Ability"},{"Defeat: Recover 1 of 2 Potion"},"The Stonemason is strong and can be found all around town, bur always next to large stones."},
		{"Goldsmith",3,5,5,{"Stop Opp Bonus"},{"Defeat: Recover 1 of 2 Potion"},"The Goldsmith knows his way around gold and silver and has most likely seen more of it than most nobles. What many don't realize is that a gold bar is quite heavy, especially if it is thrown after you."},
		{"Builder",4,6,6,{"Team: + 1 Power"},{"Defeat: Recover 1 of 2 Potion"},"The Builder is hardworking and participated in building most of the buildings in the city."},
		{"Tailor",3,4,7,{"Team: + 3 Attack"},{"Defeat: Recover 1 of 2 Potion"},"Everyone wants nice clothing, which is just what the Tailor can bring you. He might not be wearing noble clothing, but his clothing is expertly made and perfectly tailored for his body."},
	};
}
