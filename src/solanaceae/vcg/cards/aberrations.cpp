#include "./aberrations.hpp"

std::vector<Card> Cards::aberrations(void) {
	return {
		{"Bone Monger",3,5,5,{"- 2 Opp Damage Min 1"},{"Stop Opp Bonus"},"A humanoid fleshy creature with the bones of its victims attached to its body. Teeth spike from all parts of its body."},
		{"Cloaker",3,5,5,{"- 2 Opp Power Min 4"},{"Stop Opp Bonus"},"An invisible flying creature that is rarely seen, though it sparkles in light. It looks similar to a devilfish."},
		{"Ripper",2,6,1,{"- 3 Opp Damage Min 2"},{"Stop Opp Bonus"},"A humanoid creature that strips its body of its flesh to attack anything suitable for consumption. Its own flesh is stripped of similar to what it does to its victims"},
		{"Eye Wolf",3,5,3,{"- 4 Opp Power Min 4"},{"Stop Opp Bonus"},"A wolf-like creature with green eyes covering its entire body."},
		{"Devourer",3,6,3,{"+ 1 Life per Damage"},{"Stop Opp Bonus"},"A mass of fleshy mouths with different kind of teeth all over its body."},
		{"Splitter",3,7,3,{"+ 2 Power"},{"Stop Opp Bonus"},"A large mouth sits on a blueish hairy humanoid body with 2 arms that splits into 4 arms."},
		{"Gobbler",2,6,1,{"+ 3 Life"},{"Stop Opp Bonus"},"A small baby-like creature with an insanely large mouth."},
		{"Slitherer",3,7,3,{"+ 8 Attack"},{"Stop Opp Bonus"},"A snake-like creature that splits up into a mass of snakes."},
		{"Razer",2,6,5,{"Backlash: - 3 Life Min 0"},{"Stop Opp Bonus"},"A small grey creature with blade-like arms and a sleek head."},
		{"Shellshocker",4,5,7,{"Courage: - 3 Opp Power Min 4"},{"Stop Opp Bonus"},"A huge, grey crab-like creature with lightning arcing between parts of its bodies."},
		{"Doppelganger",4,7,7,{"Damage = Opp Damage"},{"Stop Opp Bonus"},"A greyish blue humanoid creature that can change its body at will into other creatures, creating a perfect copy in the process."},
		{"Tendril Bearer",5,7,6,{"Defeat: - 3 Opp Life Min 2"},{"Stop Opp Bonus"},"A hulking, hairy mass of a beast with fleshy tendrils and tentacles coming out of many parts of its body."},
		{"Amalgamation",5,7,7,{"Heal 1 Max 15"},{"Stop Opp Bonus"},"A light-yellow mass that can shoot energy beams by absorbing energy from the surrounding area."},
		{"Green Gazer",2,6,2,{"Poison 1 Min 1"},{"Stop Opp Bonus"},"A small creature with hard, stone-like skin that has two green eyes that are above each other. It has vile vomit that it can spit on other creatures."},
		{"Hulking Frogman",4,8,2,{"Poison 2 Min 0"},{"Stop Opp Bonus"},"A huge humanoid creature with a teeth-spiked frog mouth that is dripping with poison."},
		{"Brain Eater",4,7,3,{"Steal 2 Life Min 1"},{"Stop Opp Bonus"},"A Brain Eater is a humanoid creature with a mouth so big it can fit entire heads into it to suck the brains out of people's skulls."},
		{"Void Horror",5,8,2,{"Steal 3 Life Min 1"},{"Stop Opp Bonus"},"A dark cloud of mist from which long insectoid claw-like blades emerge."},
		{"Brain Dragon",5,7,7,{"Stop Opp Ability"},{"Stop Opp Bonus"},"A dragon with a gigantic brain mounted on its back that slithers to the wings and its head."},
		{"Evil Eye",4,6,6,{"Stop Opp Ability"},{"Stop Opp Bonus"},"A flying eye with immense pressure it opposes on creatures around it."},
		{"Enabler",4,7,5,{"Team: - 3 Opp Attack Min 12"},{"Stop Opp Bonus"},"A human with many connections that lets the aberrations run wild and offers them anything they want in order to take over the city."},
	};
}
