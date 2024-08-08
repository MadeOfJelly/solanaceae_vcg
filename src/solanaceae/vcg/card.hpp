#pragma once

#include <cstdint>
#include <vector>
#include <variant>
#include <string>

namespace Abilities {
	struct OppDamage {
		int16_t value {0};
		int16_t to_at_least {0};
	};

	struct OppPower {
		int16_t value {0};
		int16_t to_at_least {0};
	};

	struct OppAttack {
		int16_t value {0};
		int16_t to_at_least {0};
	};

	struct Damage {
		int16_t value {0};
	};

	struct Power {
		int16_t value {0};
	};

	struct Attack {
		int16_t value {0};
	};
}

int16_t value_from_match(const std::string& match, const std::string& sign = "+");

struct Ability {
	Ability() = default;
	Ability(const std::string& string);

	std::variant<
		Abilities::OppDamage,
		Abilities::OppPower,
		Abilities::OppAttack,

		Abilities::Damage,
		Abilities::Power,
		Abilities::Attack
	> a;

	std::string string;

	bool operator==(const Ability& rhs) const {
		// TODO: also compare values
		return a.index() == rhs.a.index();
	}
};

struct Card {
	std::string name;

	uint16_t level {0};

	uint16_t power {0};
	uint16_t damage {0};

	Ability ability;
	Ability faction_bonus;

	std::string description;

	//std::string toString(void) const;
	std::string toStringNLPD(void) const;
};

std::vector<Card> getAllCards(void);

