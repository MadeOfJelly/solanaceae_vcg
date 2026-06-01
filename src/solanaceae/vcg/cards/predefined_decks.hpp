#pragma once

#include "../card.hpp"

#include <vector>

namespace Cards {

Card get_from_all_factions(const std::string& name);

std::vector<Card> monsters_deck1(void);
std::vector<Card> monsters_clerics_deck1(void);
std::vector<Card> clerics_junkies_deck1(void);
std::vector<Card> aberrations_parasites_deck1(void);

std::vector<std::string> level25_semirandom_solofaction_list(const std::string);
std::vector<Card> level25_semirandom_solofaction(const std::string& name);

std::vector<std::string> level25_semirandom_dualfaction_list(const std::string);
std::vector<Card> level25_semirandom_dualfaction(const std::string& name);

std::vector<std::string> levelopen_semirandom_solofaction_list(const std::string);
std::vector<Card> levelopen_semirandom_solofaction(const std::string& name);

} // Cards
