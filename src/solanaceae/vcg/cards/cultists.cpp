#include "./cultists.hpp"

std::vector<Card> Cards::cultists(void) {
	return {
		{"Fanatic",3,7,3,{"- 2 Opp Life Min 2"},{"- 2 Opp Life Min 2"},"The Fanatic is down to do everything the higher Cultists are telling him. No matter how insane the job, he will do his best to accomplish it."},
		{"Slaughterer",4,8,3,{"+ 1 Life per Damage"},{"- 2 Opp Life Min 2"},"The Slaughterer is there to let the blood flow. With his murderous axe he chops down the victims of the Cultists, whether in the ritual chamber or on the streets."},
		{"Guru",5,7,7,{"+ 2 Life"},{"- 2 Opp Life Min 2"},"The Guru is mostly found in the back of the chamber. Old and bald, he oversees the rituals and provides evil counseling for the Cultists."},
		{"Zealot",3,6,4,{"+ 2 Power"},{"- 2 Opp Life Min 2"},"The Zealot dreams of the future the Cultists offer and bathes in the future glory that they will achieve."},
		{"Rampaging Demon",5,8,8,{"Backlash: - 2 Life Min 2"},{"- 2 Opp Life Min 2"},"The Rampaging Demon is a large, dark and evil creature bound by chains and only unleashed when necessary. Its power is beyond anything the Cultists have ever seen, though the price to summon it was high."},
		{"Bloodletter",2,7,4,{"Backlash: - 3 Life Min 0"},{"- 2 Opp Life Min 2"},"The Bloodletter bleeds out all kinds of creatures with his ritual knife. He needs blood, or else his life is incomplete."},
		{"Contracted Devil",4,8,7,{"Backlash: - 3 Life Min 0"},{"- 2 Opp Life Min 2"},"The Contracted Devil is a creature with red skin and a skinless tail. Two black horns protrude from its forehead. It is ready to do the master's bidding, but only for a price paid in blood."},
		{"Regular Bleeder",3,7,5,{"Backlash: - 3 Potion Min 0"},{"- 2 Opp Life Min 2"},"The Regular Bleeder is usually chained up within the ritual chamber. He is regularly used from small amounts of blood, but still kept alive to provide more blood further down the line."},
		{"Child Sacrifice",2,5,2,{"Defeat: - 3 Opp Life Min 2"},{"- 2 Opp Life Min 2"},"The Child Sacrifice was ripped from its mothers arms and now lies on the cold stone altar, ready to be ended."},
		{"Sacrificial Lamb",2,5,3,{"Defeat: + 2 Life"},{"- 2 Opp Life Min 2"},"The white Sacrifical Lamb stands amidst the pentagram and will sonn be sacrificed in a blood ritual"},
		{"Curse Spreader",3,5,5,{"Defeat: Heal 1 Max 15"},{"- 2 Opp Life Min 2"},"The Curse Spreader possesses evil powers granted by the masters from beyond and can curse anyone he comes across."},
		{"Well Keeper",5,7,5,{"Poison 2 Min 0"},{"- 2 Opp Life Min 2"},"The Well Keeper watches the blood well in the sanctum of the Cultist chambers. Additionally, he knows how to integrate the blood well with the city wide water system."},
		{"Frenzied Follower",3,7,3,{"Revenge: + 3 Damage"},{"- 2 Opp Life Min 2"},"The Frenzied Follower joined the Cultists because he was angry and is always the first to jump ahead with a dagger to the enemies' throats"},
		{"Goat Provider",3,6,4,{"Steal 1 Life Min 1"},{"- 2 Opp Life Min 2"},"The Goat Provider may be thought of as a farmer, though he manages to provide goats at any given moment. Some call him the most powerful of the cultists, as most rituals can be completed when he is around."},
		{"Masochist",4,7,3,{"Steal 2 Life Min 1"},{"- 2 Opp Life Min 2"},"The Masochist often hurts himself to further rituals and really glows up when in battle with opposing factions. He loves to bleed."},
		{"Flesh Gatherer",2,6,1,{"Steal 2 Life Min 4"},{"- 2 Opp Life Min 2"},"The Flesh Gatherer rifles through the remains on the battlefields to find corpse parts that can be used in the next ritual."},
		{"Heretic",4,6,6,{"Stop: + 3 Potion"},{"- 2 Opp Life Min 2"},"The Heretic was once a Cleric but is now godforsaken. He strives to free the world of the gods that have wronged him."},
		{"Cult Leader",5,8,4,{"Team: - 1 Opp Life Min 0"},{"- 2 Opp Life Min 2"},"The Cult Leader has overseen the Cultists for decades and decides which ritual is done and who is sacrificed to appease the lords from beyond."},
		{"Ritualist",4,6,5,{"Team: + 1 Power"},{"- 2 Opp Life Min 2"},"The Ritualist keeps watch of the rituals in the ritual chamber and knows exactly who to target with them to achieve the most damage. Additionally, he knows the foul books by heart and can cite most rituals and pentagrams without checking the books."},
	};
}
