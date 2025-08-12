#include "./card.hpp"

#include <cstdint>
#include <regex>
#include <vector>
#include <variant>
#include <string>
#include <charconv>
#include <functional>
#include <cassert>

int16_t value_from_match(const std::string& match, const std::string& sign) {
	int16_t value {0};

	std::from_chars(match.c_str(), match.c_str()+match.size(), value);

	if (sign == "-") {
		value *= -1;
	} else if (sign != "+") {
		assert(false);
	}

	return value;
}

Ability::Ability(const std::string& _string) : string(_string) {
	struct MatcherEntry {
		std::regex r;
		std::function<void(const std::smatch&, decltype(a)&)> fn;
	};
	static std::vector<MatcherEntry> mv {
		{
			std::regex("([+-]) ([0-9]+) Opp Damage Min ([0-9]+)"),
			[](const std::smatch& m, decltype(a)& _a) {
				_a = Abilities::OppDamage{
					value_from_match(m[2].str(), m[1].str()),
					value_from_match(m[3].str()),
				};
			}
		},
		{
			std::regex("([+-]) ([0-9]+) Opp Power Min ([0-9]+)"),
			[](const std::smatch& m, decltype(a)& _a) {
				_a = Abilities::OppPower{
					value_from_match(m[2].str(), m[1].str()),
					value_from_match(m[3].str()),
				};
			}
		},
		{
			std::regex("([+-]) ([0-9]+) Opp Attack Min ([0-9]+)"),
			[](const std::smatch& m, decltype(a)& _a) {
				_a = Abilities::OppAttack{
					value_from_match(m[2].str(), m[1].str()),
					value_from_match(m[3].str()),
				};
			}
		},
		{
			std::regex("([+-]) ([0-9]+) Damage"),
			[](const std::smatch& m, decltype(a)& _a) {
				_a = Abilities::Damage{
					value_from_match(m[2].str(), m[1].str()),
				};
			}
		},
		{
			std::regex("([+-]) ([0-9]+) Power"),
			[](const std::smatch& m, decltype(a)& _a) {
				_a = Abilities::Power{
					value_from_match(m[2].str(), m[1].str()),
				};
			}
		},
		{
			std::regex("([+-]) ([0-9]+) Attack"),
			[](const std::smatch& m, decltype(a)& _a) {
				_a = Abilities::Attack{
					value_from_match(m[2].str(), m[1].str()),
				};
			}
		},
	};

	for (const auto& it : mv) {
		std::smatch m;
		if (!std::regex_match(string, m, it.r)) {
			continue;
		}
		it.fn(m, a);
		return;
	}

	assert(false);
}

std::string Card::toStringNLPD(void) const {
	return {
		"N:" + name + ","
		"P:" + std::to_string(power) + ","
		"L:" + std::to_string(level) + ","
		"D:" + std::to_string(damage)
	};
}

