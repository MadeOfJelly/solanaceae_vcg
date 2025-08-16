#include "./assassins.hpp"

std::vector<Card> Cards::assassins(void) {
	return {
		{"Frontman",2,5,3,{"- 2 Opp Damage Min 3"},{"- 2 Opp Power Min 1"},"The Front looks nice and accomodating and usually handles the business of the Assassins with new clients."},
		{"Dissolver",3,7,1,{"- 2 Opp Life Min 0"},{"- 2 Opp Power Min 1"},"The Dissolver is somewhat an alchemist, though he only knows his way around acids. Three of his fingers and many of his teeth are already missing, just like all of his victims."},
		{"Fake Colleague",2,4,3,{"- 2 Opp Power Min 1"},{"- 2 Opp Power Min 1"},"The Fake Colleague infiltrates work gatherings and jobs to get into every house and every corner of the city."},
		{"Infiltrator",3,6,3,{"- 2 Opp Power Min 5"},{"- 2 Opp Power Min 1"},"The Infiltrator can get into any building at any time to the day. A grappling hook, rope and some lockpicks are all he needs."},
		{"Mr. Plan Z",5,8,5,{"- 3 Opp Damage Min 3"},{"- 2 Opp Power Min 1"},"Mr. Plan Z always has a plan, always knows where to go and always knows what to say. He is a force of nature, a brute and a charmer."},
		{"Blackmailer",4,7,3,{"- 3 Opp Potion Min 2"},{"- 2 Opp Power Min 1"},"The Blackmailer is not so much an Assassins as he knows to psychologically kill his victims by extorting money through body parts of missing family members or regular visits at their homes."},
		{"Butcher",4,5,5,{"- 3 Opp Power Min 4"},{"- 2 Opp Power Min 1"},"The Butcher fronts as a simple worker, but he likes it bloody and covers as much of the killing scene as he can in blood."},
		{"Mass Murderer",4,6,4,{"+ 1 Life per Damage"},{"- 2 Opp Power Min 1"},"The Mass Murderer relishes the thoughs of his former kills and is ready to kill again. "},
		{"Number A",4,6,5,{"Courage: + 3 Damage"},{"- 2 Opp Power Min 1"},"Number A is figure shrouded in black that is sent first when someone needs to be killed fast."},
		{"Madlad",3,4,5,{"Courage: + 3 Power"},{"- 2 Opp Power Min 1"},"The Madlab takes jobs no other Assassin may be sane enough to do and he doesn't shy away from killing people in broad daylight or right next to the guards."},
		{"Suicide Bomber",3,5,3,{"Defeat: - 2 Opp Life Min 0"},{"- 2 Opp Power Min 1"},"The Suicide Bomber only has one job, which is to blow shit up. Equipped with an explosive vest if things go wrong, he can blow everyone else up with him. However, so far his bombs sufficed."},
		{"Poisoner",3,6,1,{"Poison 2 Min 0"},{"- 2 Opp Power Min 1"},"The Poisoner only knows how to create poisons, though he is good at that. These poisons can be used on all kinds of sharp weapons or arrows."},
		{"Brother Rage",5,7,4,{"Revenge: - 4 Opp Life Min 0"},{"- 2 Opp Power Min 1"},"When Brother Rage is on a job, everything goes to shits. Houses collapse, trade routes disappear, entire meetings end in bloodbaths."},
		{"Sister Jealousy",5,7,6,{"Revenge: + 3 Damage"},{"- 2 Opp Power Min 1"},"Sister Jealousy cares for her jobs and only takes high value ones. When she is out and about you hope that you have less than her, as her jewelry is just for her and no one should have more than her."},
		{"Number B",4,5,6,{"Revenge: + 3 Power"},{"- 2 Opp Power Min 1"},"Number B is figure shrouded in grey that is sent second when someone needs to be killed fast."},
		{"Detective",2,5,2,{"Stop Opp Ability"},{"- 2 Opp Power Min 1"},"The Detective knows which clues to look for to find his next victim or find those that killed someone. He likes to smoke his pipe."},
		{"Overwhelmer",4,7,4,{"Stop Opp Ability"},{"- 2 Opp Power Min 1"},"The Overwhelmer is able to do so much at once, people's brains overload when he is out killing. Tables get thrown around and a multitude of knives are in the air when he is around."},
		{"Master Tactician",5,8,5,{"Stop Opp Bonus"},{"- 2 Opp Power Min 1"},"The Master Tactition uses battle plans, floor plans, city plans, staffing plans and any other plans he can get his hands on to plan the perfect kill."},
		{"Separator",3,7,2,{"Stop Opp Bonus"},{"- 2 Opp Power Min 1"},"The Separator likes to cut up his victims into small pieces and mail them to their family members."},
		{"Cutthroat",3,8,2,{"Stop: - 8 Opp Attack Min 3"},{"- 2 Opp Power Min 1"},"The Cutthroat comes at you when its most unexpected and rams a knife into your throat, leaving you to bleed out while he is already gone."},
		{"Coordinator",3,4,5,{"Team: - 3 Opp Attack Min 12"},{"- 2 Opp Power Min 1"},"The Coordinator knows which Assassin is where, plans escape routes and generally makes sure that the Assassins themselves don't cross paths if they are doing solo jobs."},
		{"Tracker",2,6,2,{"Team: + 2 Attack"},{"- 2 Opp Power Min 1"},"The Tracker uses his trusty dogs to find anyone in the city."},
	};
}
