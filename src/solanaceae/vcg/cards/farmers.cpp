#include "./farmers.hpp"

std::vector<Card> Cards::farmers(void) {
	return {
		{"Silo Keeper",3,5,4,{"- 12 Opp Attack Min 12"},{"+ 2 Life"},"The Silo Keeper spends most of his days in the silo, counting the grains."},
		{"Transporter",3,6,4,{"- 3 Opp Damage Min 3"},{"+ 2 Life"},"The Transporter transports the goods of the Farmers in his wagon. This is mostly produce, but sometimes also animals."},
		{"Woodcutter",5,7,6,{"- 5 Opp Damage Min 4"},{"+ 2 Life"},"The Woodercutter swings his axe to fell trees and people. This is done to block roads and also to block the roads."},
		{"Fruit Vendor",2,6,2,{"- 8 Opp Attack Min 3"},{"+ 2 Life"},"The Fruit Vendor sells apples and pears."},
		{"Crop Master",3,8,2,{"+ 2 Life"},{"+ 2 Life"},"The Crop Master knows how and when to plant any crop. Wheat and Barley are like brothers to him."},
		{"Eldest Son",4,7,5,{"Courage: + 3 Damage"},{"+ 2 Life"},"The Eldest Son will overtake the business and is schooled in everything he needs to know."},
		{"Bison Breeder",3,4,6,{"Courage: + 3 Power"},{"+ 2 Life"},"The Bison Breeder is strong and tends to the hulking bisons he breeds."},
		{"Barn Builder",4,6,4,{"Defeat: + 4 Life"},{"+ 2 Life"},"The Barn Builder can put a barn on your pot of land in less than a day. It is sturdy and can withstand the weather."},
		{"Village Cook",4,6,5,{"Poison 2 Min 1"},{"+ 2 Life"},"The Village Cook is the best cook around and makes superb stews."},
		{"Expropriated Parent",4,4,8,{"Revenge: + 3 Power"},{"+ 2 Life"},"The Expropriated Parent had all of his land taken away by the king, gathered their things together and is now out for revenge."},
		{"Land Owner",5,7,7,{"Steal 1 Potion Min 1"},{"+ 2 Life"},"The Land Owner is there for the Farmers to get money out of the people trying to buy up land or even trying to steal it from the Farmers."},
		{"Druid",5,6,8,{"Stop Opp Ability"},{"+ 2 Life"},"The Druid is often consulted when things regarding nature happen. He lives in his small tent that borders the forest."},
		{"Shepherd",2,7,1,{"Stop Opp Ability"},{"+ 2 Life"},"The Shepherd tends to his sheep on the pasture. He has a sheeping dog and a wooden stick."},
		{"Pitchforker",3,6,4,{"Stop Opp Bonus"},{"+ 2 Life"},"The Pitchforker is angry and uses his pitchfork not only to move hay, but also impale people coming onto his farm."},
		{"Trapper",4,8,4,{"Stop Opp Bonus"},{"+ 2 Life"},"The Trapper keeps the animals of the Farmers save by laying traps all around the fields and forests."},
		{"Data Forger",3,5,5,{"Stop: + 12 Attack"},{"+ 2 Life"},"The Data Forger knows how to manipulate the books to make more money for the Farmers."},
		{"Oppressed Offspring",2,5,3,{"Stop: + 3 Power"},{"+ 2 Life"},"The Oppressed Offspring does not want to work the fields, but rather travel the world. It will do anything to push past these fields."},
		{"Village Elder",5,5,8,{"Team: + 1 Power"},{"+ 2 Life"},"The Village Elder is old, but knows his way around the law and has support from many people in the city."},
		{"Grandma",3,5,5,{"Team: + 3 Attack"},{"+ 2 Life"},"The Grandma likes to cook cakes and hearty meals, providing health and ample bellies to the Farmers."},
	};
}
