#include <fstream>
#include <filesystem>
#include <ranges>
#include <string>
#include <string_view>
#include <valarray>
#include <vector>
#include <iostream>

static std::string ensure_string_quotes(const std::string_view input) {
	if (input.starts_with('"')) {
		return std::string{input};
	} else {
		// TODO: make quoted work
		//return std::string{std::quoted(input)};
		return "\"" + std::string{input} + "\"";
	}
}

int main(int argc, char** argv) {
	if (argc < 3) {
		std::cerr << "error: need in file and out dir\n";
		return 1;
	}

	std::ifstream csv{argv[1], std::ios::binary};
	if (!csv.is_open()) {
		std::cerr << "error: cant open csv file '" << argv[1] << "'\n";
		return 2;
	}

	const auto set_name = std::filesystem::path{argv[1]}.filename().stem().generic_u8string();
	std::string_view set_name_sv{reinterpret_cast<const char*>(set_name.c_str())}; // hello there c++20

	std::cout << "set_name: " << set_name_sv << "\n";

	// TODO: force dir creation?

	std::ofstream hpp{std::filesystem::path{argv[2]} / (std::string{set_name_sv} + ".hpp"), std::ios::binary};
	std::ofstream cpp{std::filesystem::path{argv[2]} / (std::string{set_name_sv} + ".cpp"), std::ios::binary};
	if (!hpp.is_open() || !cpp.is_open()) {
		std::cerr << "error: cant open out files"
			" '" << std::filesystem::path{argv[2]} / (std::string{set_name_sv} + ".hpp") << "'"
			" '" << std::filesystem::path{argv[2]} / (std::string{set_name_sv} + ".cpp") << "'"
			"\n";
		return 3;
	}

	hpp << R"xxx(#pragma once

#include <solanaceae/vcg/card.hpp>

#include <vector>

namespace Cards {

std::vector<Card> )xxx" << set_name_sv << R"xxx((void);

} // Cards)xxx";

	cpp << "#include \"./";
	cpp << set_name_sv << ".hpp\"\n\n";
	cpp << "std::vector<Card> Cards::" << set_name_sv << "(void) {\n";
	cpp << "	return {\n";

	std::string head_line;
	std::getline(csv, head_line);

	size_t name_idx {0};
	size_t level_idx {1};
	size_t power_idx {2};
	size_t damage_idx {3};
	size_t ability_idx {4};
	size_t faction_bonus_idx {5};
	size_t description_idx {6};
	if (head_line == "Name,Level,Power,Damage,Ability,Description,Bonus") {
		// HACKY
		faction_bonus_idx = 6;
		description_idx = 5;
	} else if (head_line != "Name,Level,Power,Damage,Ability,Faction Bonus,Description") {
		std::cerr << "error: csv head line is wrong\n";
		return 4;
	}

	std::string faction_bonus;

	for (std::string line; std::getline(csv, line);) {
		cpp << "		";

		// split line by comma
		std::vector<std::string_view> splits;
		for (const auto split : std::ranges::split_view(line, std::string_view{","})) {
			splits.push_back(std::string_view{std::ranges::data(split), std::ranges::size(split)});
			if (splits.back().empty()) {
				std::cerr << "error: csv line contained empty split: '" << line << "'\n";
				return 5;
			}
		}

		{ // heal splits (")
			bool in_quote {false};
			for (size_t i = 0; i < splits.size();) {
				if (!in_quote) {
					if (splits[i].starts_with('"') && !splits[i].ends_with('"')) {
						in_quote = true;
					}
					i++;
				} else {
					// assert (!starts_with " )
					in_quote = !splits[i].ends_with('"');

					// merge into prev, since they are string_views, you can just extend the length
					splits[i-1] = std::string_view{splits[i-1].data(), splits[i-1].size() + splits[i].size() + 1};

					splits.erase(splits.cbegin()+i);
				}
			}
		}

		if (splits.size() != 7) {
			std::cerr << "error: csv line did not contain 7 splits: '" << line << "'\n";
			return 5;
		}

		if (!faction_bonus.empty()) {
			if (faction_bonus != splits[faction_bonus_idx]) {
				std::cerr << "error: csv line did not have the same faction bonus: '" << line << "'\n";
				return 6;
			}
		} else {
			faction_bonus = splits[faction_bonus_idx];
		}

		cpp << "{";

		// name -> 0
		cpp << ensure_string_quotes(splits[name_idx]) << ",";

		// TODO: check numerical values
		// level -> 1
		cpp << splits[level_idx] << ",";
		// power -> 2
		cpp << splits[power_idx] << ",";
		// damage -> 3
		cpp << splits[damage_idx] << ",";

		// ability -> 4
		cpp << "{" << ensure_string_quotes(splits[ability_idx]) << "},";
		// faction_bonus -> 5
		cpp << "{" << ensure_string_quotes(splits[faction_bonus_idx]) << "},";

		// description -> 6
		cpp << ensure_string_quotes(splits[description_idx]);

		cpp << "},\n";
	}

	cpp << "	};\n";
	cpp << "}\n";

	hpp.close();
	cpp.close();

	std::cout << "csv converted\n";

	return 0;
}
