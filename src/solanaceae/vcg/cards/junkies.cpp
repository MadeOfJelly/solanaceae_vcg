#include "./junkies.hpp"

std::vector<Card> Cards::junkies(void) {
	return {
		{"Moonshiner",5,6,7,{"- 12 Opp Attack Min 12"},{"- 2 Opp Damage Min 1"},"The Moonshiner has the drinks that everyone wants, but nobody wants to deal with their aftermath. He is long blind, but the moonshine still makes him strong."},
		{"Drunkard",3,7,3,{"- 2 Opp Damage Min 1"},{"- 2 Opp Damage Min 1"},"The Drunkard is drunk 24/7 and always has a tankard in his hands."},
		{"Shroomer",4,7,5,{"- 2 Opp Power Min 6"},{"- 2 Opp Damage Min 1"},"The Shroomer only takes and eats the finest mushrooms. Red caps, blue caps, green caps, every mushroom gets ingested if it is nice enough."},
		{"Bouncer",4,8,4,{"- 3 Opp Damage Min 3"},{"- 2 Opp Damage Min 1"},"The Bouncer stands in front of the buildings where the Junkies do their stuff. Although he doesn't take any drugs, he gets high on the money that they pay him."},
		{"Opiod User",5,7,6,{"- 4 Opp Damage Min 2"},{"- 2 Opp Damage Min 1"},"The Opiod User feels no pain anymore. He has taken so much, pain does not exist for him."},
		{"Powder Master",5,8,5,{"+ 12 Attack"},{"- 2 Opp Damage Min 1"},"The Powder Master looks like he has chalk all over his face."},
		{"Glue Sniffer",2,6,2,{"+ 2 Potion"},{"- 2 Opp Damage Min 1"},"The Glue sniffer spends his day sniffing glue. That's all he does."},
		{"Piller",4,6,5,{"+ 3 Potion"},{"- 2 Opp Damage Min 1"},"The Piller has the best shit in his pocket. Small, compressed and of different colors, his pills provide spectacular experiences."},
		{"Injecter",3,8,2,{"+ 8 Attack"},{"- 2 Opp Damage Min 1"},"The Injecter carefully curates what he injects into his body and has had good results when doing so."},
		{"Dope Fiend",2,5,5,{"Backlash: - 2 Life Min 2"},{"- 2 Opp Damage Min 1"},"The Dope Fiend injects weird substances into his blood stream in order to feel better, though mostly he feels worse."},
		{"Gambler",2,5,3,{"Courage: - 3 Opp Power Min 2"},{"- 2 Opp Damage Min 1"},"The Gambler is usually found playing card or dice games for all the money he has. He is usually broke by the end of the day."},
		{"Ultraspritzer",5,7,7,{"Heal 2 Max 10"},{"- 2 Opp Damage Min 1"},"The Ultraspritzer only drinks the finest, dark red, bubbly drinks that refresh the mind and the soul."},
		{"Chainsmoker",3,7,3,{"Steal 1 Life Min 1"},{"- 2 Opp Damage Min 1"},"The Chainsmoker is always smoking something, even if it doesn't make sense. His lungs must be pitch black."},
		{"Frog Licker",2,6,2,{"Stop Opp Ability"},{"- 2 Opp Damage Min 1"},"The Frog Licker goes out of his way to search the swamps for fresh frogs to lick."},
		{"Herbalist",4,6,6,{"Stop Opp Ability"},{"- 2 Opp Damage Min 1"},"The Herbalist provides many of the Junkies with their raw materials. Whether the herbs are smoked, cooked and injected, or simply eaten, he knows how to grow and tend to them."},
		{"Spiker",3,6,4,{"Stop Opp Bonus"},{"- 2 Opp Damage Min 1"},"The Spiker spikes his own drinks to get high and get away from his usual life."},
		{"Trip Guide",4,7,5,{"Stop Opp Bonus"},{"- 2 Opp Damage Min 1"},"The Trip Guide is there for everyone when they are having a bad day. He is nice and accomodating."},
		{"Dealer",3,6,3,{"Team: + 1 Potion"},{"- 2 Opp Damage Min 1"},"The Dealer provides many of the drugs the Junkies are taking. His pockets are full of goods."},
		{"Overdoser",3,6,4,{"Team: + 3 Attack"},{"- 2 Opp Damage Min 1"},"The Overdoser is living on the edge, taking too much of many drugs at the same time, but his heart must be in the hands of god as it is still pumping."},
	};
}
