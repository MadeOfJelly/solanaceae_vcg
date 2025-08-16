#include "./cards/aberrations.hpp"
#include "./cards/assassins.hpp"
#include "./cards/bandits.hpp"
#include "./cards/clerics.hpp"
#include "./cards/crafters.hpp"
#include "./cards/cultists.hpp"
#include "./cards/easy_cards.hpp"
#include "./cards/farmers.hpp"
#include "./cards/invaders.hpp"
#include "./cards/junkies.hpp"
#include "./cards/mages.hpp"
#include "./cards/merchants.hpp"
#include "./cards/monsters.hpp"
#include "./cards/nobles.hpp"
#include "./cards/parasites.hpp"
//#include "./cards/predefined_decks.hpp"
#include "./cards/random.hpp"
#include "./cards/thieves.hpp"

#include <stdexcept>
#include <vector>
#include <iostream>

int main(void) {
	bool failed {false};
	struct DeckEntry {
		const char* name{};
		decltype(Cards::aberrations)& fn;
	};
	std::vector<DeckEntry> fn_list {
#define ENTRY(x) {#x, Cards::x},
		ENTRY(aberrations)
		ENTRY(assassins)
		ENTRY(bandits)
		ENTRY(clerics)
		ENTRY(crafters)
		ENTRY(cultists)
		ENTRY(easy_cards)
		ENTRY(farmers)
		ENTRY(invaders)
		ENTRY(junkies)
		ENTRY(mages)
		ENTRY(merchants)
		ENTRY(monsters)
		ENTRY(nobles)
		ENTRY(parasites)
		//Cards::predefined_decks,
		ENTRY(random)
		ENTRY(thieves)
#undef ENTRY
	};

	for (const auto& deck_entry : fn_list) {
		try {
			auto deck = deck_entry.fn();
			std::cout << "deck " << deck_entry.name << " contained " << deck.size() << " cards\n";
		} catch (const std::runtime_error& ex) {
			std::cerr << "failed parsing '" << deck_entry.name << "', with exception: " << ex.what() << "\n";
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
