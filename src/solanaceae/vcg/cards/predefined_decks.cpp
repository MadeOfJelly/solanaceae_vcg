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
#include <map>

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

static const std::map<std::string, std::vector<std::string>> g_level25_semirandom_solofaction{
	{"Aberration1", {"Brain Dragon", "Razer", "Enabler", "Ripper", "Devourer", "Shellshocker", "Gobbler", "Green Gazer"}},
	{"Aberration2", {"Tendril Bearer", "Amalgamation", "Ripper", "Gobbler", "Razer", "Green Gazer", "Cloaker", "Doppelganger"}},
	{"Aberration3", {"Hulking Frogman", "Brain Eater", "Ripper", "Bone Monger", "Cloaker", "Slitherer", "Spitter", "Eye Wolf"}},
	{"Assassin1", {"Coordinator", "Tracker", "Sister Jealousy", "Number A", "Detective", "Dissolver", "Madlad", "Suicide Bomber"}},
	{"Assassin2", {"Brother Rage", "Mr. Plan Z", "Frontman", "Fake Colleague", "Detective", "Tracker", "Poisoner", "Overwhelmer"}},
	{"Assassin3", {"Mass Murderer", "Butcher", "Blackmailer", "Tracker", "Detective", "Infiltrator", "Coordinator", "Separator"}},
	{"Bandit1", {"Former Noble", "Inciter", "Old Captain", "Camp Cook", "Vengeful Impersonator", "Former Worker", "Street Lurker", "Outcast"}},
	{"Bandit2", {"Trap Layer", "Camp Cook", "Fallback Man", "Rusher", "Deminisher", "Former Trader", "Childfinder", "Former Worker"}},
	{"Bandit3", {"Hateful Targeter", "Last One Standing", "Rogue Veteran", "Watcher", "Rusher", "Street Lurker", "Outcast", "Vengeful Impersonator"}},
	{"Cleric1", {"Vengeance Cleric", "Death Cleric", "Mass Servant", "Preacher", "Mass Preparer", "Pastor", "Inquisitor", "Union Cleric"}},
	{"Cleric2", {"Union Cleric", "Life Cleric", "Stability Cleric", "Mass Preparer", "Mass Servant", "Nightmare Cleric", "Acolyte", "Nature Cleric"}},
	{"Cleric3", {"Tempest Cleric", "Nature Cleric", "Acolyte", "Nightmare Cleric", "Preacher", "War Cleric", "Union Cleric", "Prophet"}},
	{"Crafter1", {"Builder", "Tailor", "Carpenter", "Scrivener", "Goldsmith", "Toymaker", "Storage Keeper", "Stonemason"}},
	{"Crafter2", {"Head Alchemist", "Blacksmith", "Leatherworker", "Recycler", "Toymaker", "Apprentice", "Storage Keeper", "Glasblower"}},
	{"Crafter3", {"Cobbler", "Builder", "Baker", "Recycler", "Potter", "Scrivener", "Goldsmith", "Tailor"}},
	{"Cultist1", {"Cult Leader", "Well Keeper", "Ritualist", "Regular Bleeder", "Flesh Gatherer", "Sacrificial Lamb", "Child Sacrifice", "Bloodletter"}},
	{"Cultist2", {"Rampaging Demon", "Contracted Devil", "Zealot", "Regular Bleeder", "Curse Spreader", "Frenzied Follower", "Child Sacrifice", "Bloodletter"}},
	{"Cultist3", {"Slaughterer", "Guru", "Curse Spreader", "Flesh Gatherer", "Sacrificial Lamb", "Goat Provider", "Frenzied Follower", "Regular Bleeder"}},
	{"Farmer1", {"Village Elder", "Grandma", "Silo Keeper", "Bison Breeder", "Data Forger", "Fruit Vendor", "Oppressed Offspring", "Expropriated Parent"}},
	{"Farmer2", {"Woodcutter", "Pitchforker", "Grandma", "Barn Builder", "Shepherd", "Fruit Vendor", "Transporter", "Crop Master"}},
	{"Farmer3", {"Village Cook", "Silo Keeper", "Transporter", "Crop Master", "Bison Breeder", "Pitchforker", "Data Forger", "Grandma"}},
	{"Invader1", {"Warlord", "Scout", "Field Medic", "Pillager", "Archer", "Sharpener", "Cannonist", "Brandisher"}},
	{"Invader2", {"Foreign King", "Commander", "Polymath", "Scout", "Field Medic", "Pillager", "Archer", "Wallclimber"}},
	{"Invader3", {"Ration Keeper", "Polisher", "Traveling Cook", "Wallclimber", "Foreign Soldier", "Brandisher", "Scout", "Cannonist"}},
	{"Junkie1", {"Ultraspritzer", "Moonshiner", "Overdoser", "Herbalist", "Glue Sniffer", "Dope Fiend", "Gambler", "Frog Licker"}},
	{"Junkie2", {"Piller", "Dealer", "Overdoser", "Spiker", "Chainsmoker", "Injecter", "Shroomer", "Frog Licker"}},
	{"Junkie3", {"Powder Master", "Injecter", "Chainsmoker", "Overdoser", "Dealer", "Glue Sniffer", "Gambler", "Bouncer"}},
	{"Mage1", {"Destruction Mage", "Iron Mage", "Potion Keeper", "Student", "Librarian", "Transmutation Mage", "Necromancer", "Magical Enchanter"}},
	{"Mage2", {"Ancient Scholar", "God Hater", "Spellblade", "Dispeller", "Librarian", "Student", "Conjuration Mage", "Illusion Mage"}},
	{"Mage3", {"Librarian", "Evocation Mage", "Ancient Scholar", "Professor", "Dispeller", "Necromancer", "Conjuration Mage", "Enchantment Mage"}},
	{"Merchant1", {"Guild Leader", "Potion Merchant", "Aspiring Merchant", "Food Merchant", "Vendor", "Fake Merchant", "Weapon Merchant", "Herb Merchant"}},
	{"Merchant2", {"Shipping Merchant", "Ore Merchant", "Herb Merchant", "Paid Guard", "Remedy Merchant", "Auctioneer", "Supplier", "Luxury Goods Merchant"}},
	{"Merchant3", {"Envious Merchant", "Jewelry Merchant", "Supply Chain Puppeteer", "Fake Merchant", "Vendor", "Aspiring Merchant", "Paid Guard", "Supplier"}},
	{"Monster1", {"Blood Fly", "Giant Centipede", "Rabies Bison", "Beast of the Fields", "Sea Serpent", "Flooded Spirit", "Snapper", "Storm Shark"}},
	{"Monster2", {"Snapper", "Hell Hornet", "Werewolf", "Troll", "Burrower", "Poison Lizard", "Storm Shark", "Hydra"}},
	{"Monster3", {"Sandworm", "Mutated Gorilla", "Living Gargoyle", "Rabies Bison", "Giant Centipede", "Storm Shark", "Snapper", "Poison Lizard"}},
	{"Noble1", {"Bodyguard", "Godfather", "Vintner", "Carriage Driver", "Spoiled Brat", "Housekeeper", "Private Doctor", "Book Keeper"}},
	{"Noble2", {"Book Keeper", "Rebel Child", "Butler", "Distant Relative", "Courtesan", "Stable Keeper", "Sponsor", "Second in Line"}},
	{"Noble3", {"Council Member", "Courtesan", "Stable Keeper", "Book Keeper", "Pact Keeper", "Carriage Driver", "Vintner", "Rebel Child"}},
	{"Parasite1", {"Gigantic Leech", "Spore King", "Acidic Former", "Cannibalistic Consumer", "Delayed Spreader", "Airborne Integrator", "Combining Mass", "Shapeworm"}},
	{"Parasite2", {"Shapeworm", "Contagious Virus", "Combining Mass", "Bloater", "Vile Infector", "Airborne Integrator", "Delayed Spreader", "Cannibalistic Consumer"}},
	{"Parasite3", {"Shapeworm", "Combining Mass", "Contagious Virus", "Pandemic Oven", "Shapechanger", "Vile Infector", "Overgrowth Shroom", "Rapid Overtaker"}},
	{"Thief1", {"Mastermind", "Stash Keeper", "Chokehold", "Pickpocket", "Lookout", "Child Thief", "Scammer", "Homebrewer"}},
	{"Thief2", {"Burglar", "Robber", "Mugger", "Homebrewer", "Societary Leech", "Con Artist", "Con Artist", "Stash Keeper"}},
	{"Thief3", {"Trade Route Camper", "Smuggler", "Childless Parent", "Thug", "Child Thief", "Lookout", "Pickpocket", "Fortune Teller"}},
};

static const std::map<std::string, std::vector<std::string>> g_level25_semirandom_dualfaction{
	{"Aberration-Assassin", {"Hulking Frogman", "Void Horror", "Ripper", "Gobbler", "Overwhelmer", "Cutthroat", "Poisoner", "Dissolver"}},
	{"Aberration-Cleric", {"Brain Dragon", "Slitherer", "Razer", "Eye Wolf", "Pastor", "Prophet", "Acolyte", "Mass Servant"}},
	{"Crafter-Mage", {"Stonemason", "Carpenter", "Potter", "Toymaker", "Aspiring Mage", "Transmutation Mage", "Student", "Enchantment Mage"}},
	{"Cultist-Invader", {"Masochist", "Flesh Gatherer", "Goat Provider", "Bloodletter", "Flanker", "Wallclimber", "Archer", "Cannonist"}},
	{"Assassin-Cleric", {"Blackmailer", "Infiltrator", "Fake Colleague", "Suicide Bomber", "Hollow Cleric", "War Cleric", "Nightmare Cleric", "Preacher"}},
	{"Farmer-Junkie", {"Shepherd", "Trapper", "Bison Breeder", "Crop Master", "Bouncer", "Injecter", "Drunkard", "Chainsmoker"}},
	{"Crafter-Parasite", {"Recycler", "Armorer", "Baker", "Glasblower", "Pandemic Oven", "Cannibalistic Consumer", "Separating Splitter", "Shapechanger"}},
	{"Cultist-Farmer", {"Rampaging Demon", "Slaughterer", "Sacrificial Lamb", "Child Sacrifice", "Stable Keeper", "Council Member", "Vintner", "Distant Relative"}},
	{"Monster-Thief", {"Flooded Spirit", "Poison Lizard", "Beast of the Fields", "Giant Centipede", "Con Artist", "Child Thief", "Robber", "Thug"}},
	{"Merchant-Parasite", {"Eldest Son", "Fruit Vendor", "Woodcutter", "Oppressed Offspring", "Gigantic Leech", "Acidic Former", "Cannibalistic Consumer", "Vile Infector"}},
	{"Noble-Thief", {"Homebrewer", "Mugger", "Burglar", "Pickpocket", "Insider", "Godfather", "Carriage Driver", "Book Keeper"}},
	{"Mage-Merchant", {"Herb Merchant", "Ore Merchant", "Aspiring Merchant", "Luxury Goods Merchant", "Student", "Dispeller", "Evocation Mage", "Aspiring Mage"}},
	{"Invader-Junkie", {"Powder Master", "Piller", "Spiker", "Glue Sniffer", "Traveling Cook", "Ration Keeper", "Field Medic", "Polisher"}},
	{"Merchant-Monster", {"Supply Chain Puppeteer", "Jewelry Merchant", "Vendor", "Fake Merchant", "Troll", "Slicing Mantis", "Blood Fly", "Hell Hornet"}},
};

static const std::map<std::string, std::vector<std::string>> g_levelopen_semirandom_solofaction{
	{"AberrationBig", {"Brain Dragon", "Void Horror", "Enabler", "Evil Eye", "Brain Eater", "Hulking Frogman", "Amalgamation", "Tendril Bearer"}},
	{"AssassinBig", {"Master Tactician", "Overwhelmer", "Sister Jealousy", "Number B", "Brother Rage", "Mr. Plan Z", "Blackmailer", "Butcher"}},
	{"BanditBig", {"Old Captain", "Former Noble", "Inciter", "Childfinder", "Hateful Targeter", "Last One Standing", "Stash Burner", "Former Trader"}},
	{"ClericBig", {"Vengeance Cleric", "Death Cleric", "Oracle", "War Cleric", "Life Cleric", "Water Cleric", "Peace Cleric", "Prophet"}},
	{"CrafterBig", {"Builder", "Stonemason", "Armorer", "Carpenter", "Enchanter", "Head Alchemist", "Blacksmith", "Leatherworker"}},
	{"CultistBig", {"Ritualist", "Cult Leader", "Heretic", "Masochist", "Well Keeper", "Rampaging Demon", "Guru", "Slaughterer"}},
	{"FarmerBig", {"Village Elder", "Trapper", "Druid", "Land Owner", "Expropriated Parent", "Barn Builder", "Eldest Son", "Woodcutter"}},
	{"InvaderBig", {"Sharpener", "Flanker", "Foreign King", "Polymath", "Warlord", "Cannonist", "Commander", "Strategist"}},
	{"JunkieBig", {"Trip Guide", "Herbalist", "Ultraspritzer", "Piller", "Powder Master", "Opiod User", "Bouncer", "Moonshiner"}},
	{"MageBig", {"Ancient Scholar", "God Hater", "Counterspeller", "Iron Mage", "Aspiring Mage", "Evocation Mage", "Destruction Mage", "Abjuration Mage"}},
	{"MerchantBig", {"Guild Leader", "Supply Chain Puppeteer", "Envious Merchant", "Luxury Goods Merchant", "Weapon Merchant", "Potion Merchant", "Monopoly Keeper", "Jewelry Merchant"}},
	{"MonsterBig", {"Hydra", "Mutated Gorilla", "Sea Serpent", "Slicing Mantis", "Red Dragon", "Beast of the Fields", "Mountain Troll", "Living Gargoyle"}},
	{"NobleBig", {"Insider", "Council Member", "Second in Line", "Private Doctor", "Bodyguard", "Pact Keeper", "Gardener", "Godfather"}},
	{"ParasiteBig", {"Shapeworm", "Hookvine", "Plaguebearer", "Gigantic Leech", "Spore King", "Bloater", "Massive Gasser", "River Stench"}},
	{"ThiefBig", {"Mastermind", "Stash Keeper", "Noble's Horror", "Chokehold", "Trade Route Camper", "Smuggler", "Childless Parent", "Thug"}},
};

std::vector<std::string> Cards::level25_semirandom_solofaction_list(const std::string) {
	std::vector<std::string> list;
	for (const auto& [key, _] : g_level25_semirandom_solofaction) {
		list.push_back(key);
	}
	return list;
}

std::vector<Card> Cards::level25_semirandom_solofaction(const std::string& name) {
	if (!g_level25_semirandom_solofaction.count(name)) {
		throw std::runtime_error(name + " deck not found");
	}

	std::vector<Card> res;

	for (const auto& card_name : g_level25_semirandom_solofaction.at(name)) {
		res.emplace_back(get_from_all_factions(card_name));
	}

	return res;
}

std::vector<std::string> Cards::level25_semirandom_dualfaction_list(const std::string) {
	std::vector<std::string> list;
	for (const auto& [key, _] : g_level25_semirandom_dualfaction) {
		list.push_back(key);
	}
	return list;
}

std::vector<Card> Cards::level25_semirandom_dualfaction(const std::string& name) {
	if (!g_level25_semirandom_dualfaction.count(name)) {
		throw std::runtime_error(name + " deck not found");
	}

	std::vector<Card> res;

	for (const auto& card_name : g_level25_semirandom_dualfaction.at(name)) {
		res.emplace_back(get_from_all_factions(card_name));
	}

	return res;
}

std::vector<std::string> Cards::levelopen_semirandom_solofaction_list(const std::string) {
	std::vector<std::string> list;
	for (const auto& [key, _] : g_levelopen_semirandom_solofaction) {
		list.push_back(key);
	}
	return list;
}

std::vector<Card> Cards::levelopen_semirandom_solofaction(const std::string& name) {
	if (!g_levelopen_semirandom_solofaction.count(name)) {
		throw std::runtime_error(name + " deck not found");
	}

	std::vector<Card> res;

	for (const auto& card_name : g_levelopen_semirandom_solofaction.at(name)) {
		res.emplace_back(get_from_all_factions(card_name));
	}

	return res;
}
