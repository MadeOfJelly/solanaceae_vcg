#include "./mages.hpp"

std::vector<Card> Cards::mages(void) {
	return {
		{"Magical Enchanter",3,8,2,{"- 2 Opp Damage Min 1"},{"+ 2 Damage"},"The Magical Enchanter is seen with weird glassware used to enchant weapons, armors and regular items to give them magical effects."},
		{"Enchantment Mage",3,6,3,{"- 3 Opp Potion Min 3"},{"+ 2 Damage"},"The Enchantment Mage specializes in magic that enhances creatures. Whether that is increasing their physical power or mental capacities is up to him."},
		{"Spellblade",4,7,4,{"- 3 Opp Power Min 5"},{"+ 2 Damage"},"The Spellblade combines magic and swordfighting to achieve a dangerous combo of magical and physical warfare."},
		{"Illusion Mage",3,4,4,{"- 4 Opp Power Min 3"},{"+ 2 Damage"},"The Illusion Mage is able to produce illusions of anything. Even dragons aren't safe of being brought to life in images by him."},
		{"Abjuration Mage",5,7,5,{"- 5 Opp Damage Min 2"},{"+ 2 Damage"},"The Abjuration mage is able to block any attack with magical force fields."},
		{"Destruction Mage",5,8,4,{"- 5 Opp Potion Min 5"},{"+ 2 Damage"},"The Destruction Mage evaporates matter, no matter if it is organic or not. When he points his finger at someone, they turn to dust."},
		{"Evocation Mage",4,6,6,{"+ 2 Damage"},{"+ 2 Damage"},"The Evocation Mage is responsible for fireballs and big explosions. His spells devastate entire neighbourhoods."},
		{"Conjuration Mage",3,7,3,{"+ 2 Power"},{"+ 2 Damage"},"The Conjuration Mage can summon magical creatures like fire elementals from thin air."},
		{"Potion Keeper",2,6,1,{"+ 3 Potion"},{"+ 2 Damage"},"The Potion Keeper keeps the shelves stocked with Potions. He knows where to find which one."},
		{"Aspiring Mage",4,6,6,{"Courage: + 3 Power"},{"+ 2 Damage"},"The Aspiring Mage is nearly a master of mages, trying to combine many disciplines at once."},
		{"Necromancer",3,7,2,{"Defeat: + 3 Life"},{"+ 2 Damage"},"The Necromancer is hated, but can turn the tide of a battle by making the dead rise and fight again."},
		{"Transmutation Mage",3,5,4,{"Power = Opp Power"},{"+ 2 Damage"},"The Transmutation Mage can change matter from one to another. Stone into wood, wood into water, nothing is beyond limits."},
		{"Iron Mage",5,6,8,{"Revenge: + 3 Power"},{"+ 2 Damage"},"The Iron Mage is caged in an iron suit to keep his powers in check. This may have restrained his magical powers, but his physical one increased."},
		{"Counterspeller",5,7,7,{"Stop Opp Ability"},{"+ 2 Damage"},"The Counterspeller is the archnemesis of any spell caster. With the flick of a finger he can interrupt any spell being cast."},
		{"Dispeller",3,7,3,{"Stop Opp Ability"},{"+ 2 Damage"},"The Dispeller disenchants and dispells magical effects. He is feared by the community of Mages."},
		{"Professor",3,6,4,{"Stop Opp Bonus"},{"+ 2 Damage"},"The Professor gives lectures about magic and is knowledgable in the theoretical side of things."},
		{"Student",2,7,1,{"Stop Opp Bonus"},{"+ 2 Damage"},"The Student is always scribbling notes when the Mages are talking. Knowledge is power, is what they told him, so it must be true."},
		{"God Hater",4,5,6,{"Stop: + 4 Damage"},{"+ 2 Damage"},"The God Hater wants to kill gods. For now he is still far away in achieving that with his magic, but he is on the way there."},
		{"Ancient Scholar",4,8,3,{"Team: + 1 Damage"},{"+ 2 Damage"},"The Anvient Scholar is the oldest of the Mages, but he has the knowledge of many libraries available to him in his brain."},
		{"Librarian",2,5,2,{"Team: + 1 Power"},{"+ 2 Damage"},"The Librarian is old, but he knows where every book in the gargantuan library of the Mages is."},
	};
}
