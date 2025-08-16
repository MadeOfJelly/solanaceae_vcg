#include "./nobles.hpp"

std::vector<Card> Cards::nobles(void) {
	return {
		{"Book Keeper",3,4,4,{"- 12 Opp Attack Min 12"},{"- 12 Opp Attack Min 12"},"Book Keepers are necessary evils that know the ins and outs of the Nobles finances. A few extra coins in their pockets rarely affect the Nobles, but make life so much better."},
		{"Godfather",5,7,6,{"- 3 Opp Damage Min 3"},{"- 12 Opp Attack Min 12"},"The Godfather is old and frail, but commands a lot. He pulls the strings in the back of the Noble families."},
		{"Vintner",2,4,3,{"- 3 Opp Damage Min 3"},{"- 12 Opp Attack Min 12"},"The Vintner spends his days in the vineyard, tending to the grapes and testing the freshly produced wine."},
		{"Gardener",4,7,3,{"- 3 Opp Life Min 2"},{"- 12 Opp Attack Min 12"},"The Gardener is often found between the hedges. Problems only occur if you don't find him, as he could lurk behind every corner."},
		{"Carriage Driver",2,5,3,{"- 4 Opp Attack Min 2"},{"- 12 Opp Attack Min 12"},"The Carriage Driver keeps quiet, but he overhears quite a lot of secrets while riding the carriage."},
		{"Pact Keeper",5,7,4,{"- 4 Opp Life Min 1"},{"- 12 Opp Attack Min 12"},"The Pact Keeper is there to reinforce any written pacts between Nobles and is elected by the Nobles themselves to keep order. If someone doesn't value a contract, they are legally forced to feel his wrath."},
		{"Bodyguard",5,8,3,{"+ 1 Life per Damage"},{"- 12 Opp Attack Min 12"},"The Bodyguard is a former soldier and highly trained. He will give his life for the Nobles in combat and is therefore well payed. Heavy armor and weaponry are to be seen everywhere he goes."},
		{"Rebel Child",3,6,6,{"Backlash: - 2 Life Min 0"},{"- 12 Opp Attack Min 12"},"The Rebel Child is a teenager that doesn't quite yet appreacte the Nobles' life. It is angry and lashes out at everyone."},
		{"Spoiled Brat",2,5,5,{"Backlash: - 4 Potion Min 0"},{"- 12 Opp Attack Min 12"},"The Spoiled Brat is the young child of a noble, always throwing tantrums, but often getting what it wants."},
		{"Private Doctor",4,6,4,{"Heal 2 Max 13"},{"- 12 Opp Attack Min 12"},"Nobles need Private Doctors, without a Private Doctor you are not a real Noble. They have often stayed with families for generations and are highly valued."},
		{"Butler",3,5,5,{"Poison 1 Min 3"},{"- 12 Opp Attack Min 12"},"The Butler oversees the entire mansion and is always there for the Nobles, may it be during dinner or on their death bed."},
		{"Distant Relative",3,6,3,{"Revenge: + 3 Potion"},{"- 12 Opp Attack Min 12"},"The Distant Relative is a secret weapon of the Nobles. Having outside connections people do or don't know about is always a good thing, although their resources might take a while to get to them."},
		{"Second in Line",4,5,6,{"Revenge: + 3 Power"},{"- 12 Opp Attack Min 12"},"The Second in Line is so close to the throne and yet so far. They will not get their will, but have to be accomodated for, which results in a lot of resentment for the rest of the family."},
		{"Courtesan",3,7,2,{"Steal 1 Potion Min 3"},{"- 12 Opp Attack Min 12"},"Nobles have money and Courtesans, who are always dressed in the best clothes, sometimes revealing a bit too much of their bodies."},
		{"Housekeeper",2,5,3,{"Steal 1 Potion Min 6"},{"- 12 Opp Attack Min 12"},"The Housekeeper knows where everything belongs, but sometimes things just might go missing in such a big mansion, especially when guests misplace their goods"},
		{"Council Member",4,7,4,{"Stop Opp Ability"},{"- 12 Opp Attack Min 12"},"The Council Member is a Noble that has went deep into politics. He knows the laws and is not afraid to bend them to the will of his Noble family."},
		{"Stable Keeper",3,7,2,{"Stop Opp Bonus"},{"- 12 Opp Attack Min 12"},"The Stable Keeper knows his way around horses and is mostly found around the stables. He is strongly built, but that's about it."},
		{"Sponsor",3,6,3,{"Stop: + 3 Life"},{"- 12 Opp Attack Min 12"},"Sponsors are often from out of town, but still supply large amounts of money to the Nobles. Not that they need the money, but they may be swayed to vote in terms of the unknown Sponsor."},
		{"Insider",4,5,6,{"Stop: + 3 Power"},{"- 12 Opp Attack Min 12"},"The Insider is partially a Noble, but only partially. He has knowledge about many noble families, but they rarely have accurate information about him, which always puts a smile on his face."},
	};
}
