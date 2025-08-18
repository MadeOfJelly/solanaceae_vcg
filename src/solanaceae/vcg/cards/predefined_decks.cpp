#include "./predefined_decks.hpp"

#include "./monsters.hpp"
#include "./clerics.hpp"
#include "./aberrations.hpp"
#include "./parasites.hpp"

#include <stdexcept>

static const Card& find_from_deck(const std::vector<Card>& deck, const std::string& name) {
	for (const auto& it : deck) {
		if (it.name == name) {
			return it;
		}
	}
	throw std::runtime_error(name + " not found in deck");
}

std::vector<Card> Cards::monster_deck1(void) {
	const auto monsters_faction_deck = monsters();
	return {
		find_from_deck(monsters_faction_deck, "Living Gargoyle"),
		find_from_deck(monsters_faction_deck, "Beast of the Fields"),
		find_from_deck(monsters_faction_deck, "Giant Centipede"),
		find_from_deck(monsters_faction_deck, "Slicing Mantis"),
		find_from_deck(monsters_faction_deck, "Troll"),
		find_from_deck(monsters_faction_deck, "Hell Hornet"),
		find_from_deck(monsters_faction_deck, "Werewolf"),
		find_from_deck(monsters_faction_deck, "Poison Lizard"),
	};
}

std::vector<Card> Cards::monster_cleric_deck1(void) {
	const auto monsters_faction_deck = monsters();
	const auto clerics_faction_deck = clerics();
	return {
		find_from_deck(monsters_faction_deck, "Living Gargoyle"),
		find_from_deck(monsters_faction_deck, "Slicing Mantis"),
		find_from_deck(monsters_faction_deck, "Werewolf"),
		find_from_deck(monsters_faction_deck, "Snapper"),

		find_from_deck(clerics_faction_deck, "Life Cleric"),
		find_from_deck(clerics_faction_deck, "Nature Cleric"),
		find_from_deck(clerics_faction_deck, "Inquisitor"),
		find_from_deck(clerics_faction_deck, "Mass Preparer"),
	};
}

std::vector<Card> Cards::aberration_parasites_deck1(void) {
	const auto aberrations_faction_deck = aberrations();
	const auto parasites_faction_deck = parasites();
	return {
		find_from_deck(aberrations_faction_deck, "Slitherer"),
		find_from_deck(aberrations_faction_deck, "Razer"),
		find_from_deck(aberrations_faction_deck, "Shellshocker"),
		find_from_deck(aberrations_faction_deck, "Doppelganger"),

		find_from_deck(parasites_faction_deck, "River Stench"),
		find_from_deck(parasites_faction_deck, "Spore King"),
		find_from_deck(parasites_faction_deck, "Plaguebearer"),
		find_from_deck(parasites_faction_deck, "Pandemic Oven"),
	};
}

