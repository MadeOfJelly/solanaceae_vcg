#include "./card.hpp"

#include <stdexcept>
#include <vector>
#include <iostream>


int main(void) {
	std::vector<std::string> ability_strings {
		//- X Opp Power Min Y,"During the Battle, the opponents Power is reduced by X down to a minimum of Y."
		"- 2 Opp Power Min 2",
		//- X Opp Damage Min Y,"During the Battle, the opponents Damage is reduced by X down to a minimum of Y."
		"- 2 Opp Damage Min 2",
		//- X Opp Attack Min Y,"During the Battle, the opponents Attack is reduced by X down to a minimum of Y."
		"- 2 Opp Attack Min 2",
		//- X Opp Life Min Y,"After the Battle, the enemies’ Lives are reduced by X down to a minimum of Y after the Damage is applied."
		"- 2 Opp Life Min 2",
		//- X Opp Potion Min Y,"After the Battle, the enemies’ Potions are reduced by X down to a minimum of Y."
		"- 2 Opp Potion Min 2",

		"+ 2 Power",
		"- 2 Power",
		"+ 2 Damage",
		"- 2 Damage",
		"+ 2 Attack",
		"- 2 Attack",
		//+ X Life,When this Card wins you get X Life.
		"+ 2 Life",
		"- 2 Life",
		//+ X Potion,When this Card wins you get X Potion.
		"+ 2 Potion",
		"- 2 Potion",

		//Damage = Opp Damage,The Damage of this Card is equal to the base Damage of the opposing Card.
		"Damage = Opp Damage",
		//Power = Opp Power,The Power of this Card is equal to the base Power of the opposing Card.
		"Power = Opp Power",

		//+ X Life per Damage,"If this Card wins the Battle, you gain Lives equal to X-times the Damage the Card dealt."
		"+ 2 Life per Damage",

		//Heal X Max Y,"If this Card wins the Battle, you regain X Lives after each of the following Battles up to a maximum of Y. Between multiple Heals, only the strongest is applied, unless another Heal would heal more Lives due to the maximum of Y. Heal always acts before Poison."
		"Heal 2 Max 2",

		//Poison X Min Y,"If this Card wins the Battle, the enemy takes X damage after each of the following Battles down to a minimum of Y. Between multiple poisons, only the strongest is applied, unless another poison would deal more damage due to the minimum of Y. Poison always acts after Heal."
		"Poison 2 Min 2",

		//Recover 1 of 2 Potion,"After the Battle, you recover 50% of the Potions the Card had, rounded up. This includes the Potion it has by default."
		"Recover 1 of 2 Potion",

		//Stop Opp Ability,The opponent’s Card’s Ability is ignored.
		"Stop Opp Ability",
		//Stop Opp Bonus,The opponent’s Card’s Faction Bonus is ignored.
		"Stop Opp Bonus",

		// TODO: steal conditional
		//Steal X Opp Y Min Z,Removes X of Y down to a minimum of Z from the enemy and gives you the amount that was removed.
		//"Steal 2 Opp Power Min 2",
		//"Steal 2 Opp Power Min 2",

		"Defeat: - 2 Opp Life Min 2",
		"Defeat: - 2 Opp Potion Min 2",
		"Defeat: - 2 Life",
		"Defeat: + 2 Life",
		"Defeat: + 2 Potion",
		"Defeat: + 2 Life per Damage",
		"Defeat: Heal 2 Max 2",
		"Defeat: Poison 2 Min 2",
		"Defeat: Recover 1 of 2 Potion",

		"Stop: - 2 Opp Power Min 2",
		"Stop: - 2 Opp Damage Min 2",
		"Stop: - 2 Opp Attack Min 2",
		"Stop: - 2 Opp Life Min 2",
		"Stop: - 2 Opp Potion Min 2",
		"Stop: + 2 Power",
		"Stop: + 2 Damage",
		"Stop: + 2 Attack",
		"Stop: + 2 Life",
		"Stop: + 2 Potion",
		"Stop: Damage = Opp Damage",
		"Stop: Power = Opp Power",
		"Stop: + 2 Life per Damage",
		"Stop: Heal 2 Max 2",
		"Stop: Poison 2 Min 2",
		"Stop: Recover 1 of 2 Potion",
		//"Stop: Stop Opp Ability",
		//"Stop: Stop Opp Bonus",
	};

	//std::vector<std::string> ability_prefix_string {
	//    //Backlash: XYZ,A Backlash Ability triggers upon winning a Battle with the Card. You yourself are affected by this Ability and not your enemy.
	//    "Backlash:",
	//    //Confidence (most likely not integrating it?),This Ability activates when one of your Cards won the last Battle.
	//    //"Confidence:",
	//    //Courage: XYZ,An Ability with Courage gets activated when the Card gets played first for a Battle.
	//    "Courage:",
	//    //Revenge: XYZ,This Ability activates when one of your Cards lost the last Battle.
	//    "Revenge:",
	//    //Ruler: XYZ,Ruler abilities are applied to all of your Cards on every Battle.
	//    "Ruler:",
	//    //Stop: XYZ,This Ability activates when the opposing Card possesses „Stop Opp Ability“.
	//    "Stop:",
	//    //Support: XYZ,A Support ability increases in strength for each member of the Faction drawn.
	//    "Support:",
	//    //Win: XYZ,The effect triggers when this Card wins the batte.
	//    "Win:",
	//    "Defeat:",

	//    //"Steal:",
	//};

	bool failed {false};
	for (const auto& astr : ability_strings) {
		std::cout << "parsing '" << astr << "'\n";
		try {
			Ability a{astr};
		} catch (const std::runtime_error& ex) {
			std::cerr << "failed parsing '" << astr << "', with exception: " << ex.what() << "\n";
			failed = true;
		} catch (...) {
			std::cerr << "bad exception\n";
			return 2;
		}
	}

	if (failed) {
		return 1;
	}

	return 0;
}
