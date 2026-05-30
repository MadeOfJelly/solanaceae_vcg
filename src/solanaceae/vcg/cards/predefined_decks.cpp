#include "./predefined_decks.hpp"

#include "./aberrations.hpp"
#include "./assassins.hpp"
#include "./bandits.hpp"
#include "./clerics.hpp"
#include "./crafters.hpp"
#include "./cultists.hpp"
#include "./farmers.hpp"
#include "./invaders.hpp"
#include "./junkies.hpp"
#include "./mages.hpp"
#include "./merchants.hpp"
#include "./monsters.hpp"
#include "./nobles.hpp"
#include "./parasites.hpp"
//supporters
#include "./thieves.hpp"

#include <stdexcept>

constexpr static const Card& find_from_deck(const std::vector<Card>& deck, const std::string& name) {
	for (const auto& it : deck) {
		if (it.name == name) {
			return it;
		}
	}
	throw std::runtime_error(name + " not found in deck");
}

Card Cards::get_from_all_factions(const std::string& name) {
	// all this try catch is rather slow and should never be done for anything time critical
	{
		const auto aberrations_faction_deck = aberrations();
		try {
			return find_from_deck(aberrations_faction_deck, name);
		} catch(...) {}
	}
	{
		const auto assassins_faction_deck = assassins();
		try {
			return find_from_deck(assassins_faction_deck, name);
		} catch(...) {}
	}
	{
		const auto bandits_faction_deck = bandits();
		try {
			return find_from_deck(bandits_faction_deck, name);
		} catch(...) {}
	}
	{
		const auto clerics_faction_deck = clerics();
		try {
			return find_from_deck(clerics_faction_deck, name);
		} catch(...) {}
	}
	{
		const auto crafters_faction_deck = crafters();
		try {
			return find_from_deck(crafters_faction_deck, name);
		} catch(...) {}
	}
	{
		const auto cultists_faction_deck = cultists();
		try {
			return find_from_deck(cultists_faction_deck, name);
		} catch(...) {}
	}
	{
		const auto farmers_faction_deck = farmers();
		try {
			return find_from_deck(farmers_faction_deck, name);
		} catch(...) {}
	}
	{
		const auto invaders_faction_deck = invaders();
		try {
			return find_from_deck(invaders_faction_deck, name);
		} catch(...) {}
	}
	{
		const auto junkies_faction_deck = junkies();
		try {
			return find_from_deck(junkies_faction_deck, name);
		} catch(...) {}
	}
	{
		const auto mages_faction_deck = mages();
		try {
			return find_from_deck(mages_faction_deck, name);
		} catch(...) {}
	}
	{
		const auto merchants_faction_deck = merchants();
		try {
			return find_from_deck(merchants_faction_deck, name);
		} catch(...) {}
	}
	{
		const auto monsters_faction_deck = monsters();
		try {
			return find_from_deck(monsters_faction_deck, name);
		} catch(...) {}
	}
	{
		const auto nobles_faction_deck = nobles();
		try {
			return find_from_deck(nobles_faction_deck, name);
		} catch(...) {}
	}
	{
		const auto parasites_faction_deck = parasites();
		try {
			return find_from_deck(parasites_faction_deck, name);
		} catch(...) {}
	}
//supporters
	{
		const auto thieves_faction_deck = thieves();
		try {
			return find_from_deck(thieves_faction_deck, name);
		} catch(...) {}
	}

	throw std::runtime_error(name + " not found");
}

std::vector<Card> Cards::monsters_deck1(void) {
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

std::vector<Card> Cards::monsters_clerics_deck1(void) {
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

std::vector<Card> Cards::clerics_junkies_deck1(void) {
	const auto clerics_faction_deck = clerics();
	const auto junkies_faction_deck = junkies();
	return {
		find_from_deck(clerics_faction_deck, "Life Cleric"),
		find_from_deck(clerics_faction_deck, "War Cleric"),
		find_from_deck(clerics_faction_deck, "Tempest Cleric"),
		find_from_deck(clerics_faction_deck, "Mass Servant"),

		find_from_deck(junkies_faction_deck, "Ultraspritzer"),
		find_from_deck(junkies_faction_deck, "Glue Sniffer"),
		find_from_deck(junkies_faction_deck, "Dope Fiend"),
		find_from_deck(junkies_faction_deck, "Gambler"),
	};
}

std::vector<Card> Cards::aberrations_parasites_deck1(void) {
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

