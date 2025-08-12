#pragma once

#include <cstdint>
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

	struct OppLife {
		int16_t value {0};
		int16_t to_at_least {0};
	};

	struct OppPotion {
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

	struct Life {
		int16_t value {0};
	};

	struct Potion {
		int16_t value {0};
	};

	struct CopyDamage {
	};

	struct CopyPower {
	};

	struct LifePerDamage {
		int16_t value {0};
	};

	struct Heal {
		int16_t value {0};
		int16_t to_at_most {0};
	};

	struct Poison {
		int16_t value {0};
		int16_t to_at_least {0};
	};

	struct RecoverPotions {
	};

	struct StopOppAbility {
	};

	struct StopOppBonus {
	};

	template<typename Inner>
	struct Defeat {
		Inner inner;
	};
	template<typename Inner> Defeat( Inner ) -> Defeat<Inner>;

	template<typename Inner>
	struct Stop {
		Inner inner;
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
		Abilities::OppLife,
		Abilities::OppPotion,

		Abilities::Damage,
		Abilities::Power,
		Abilities::Attack,
		Abilities::Life,
		Abilities::Potion,

		Abilities::CopyDamage,
		Abilities::CopyPower,

		Abilities::LifePerDamage,

		Abilities::Heal,
		Abilities::Poison,
		Abilities::RecoverPotions,

		Abilities::StopOppAbility,
		Abilities::StopOppBonus,

		// all current variants
		Abilities::Defeat<Abilities::Life>,
		Abilities::Defeat<Abilities::Poison>,
		Abilities::Defeat<Abilities::Heal>,
		Abilities::Defeat<Abilities::OppLife>,
		Abilities::Defeat<Abilities::Potion>,
		Abilities::Defeat<Abilities::RecoverPotions>,
		// extra for compat
		Abilities::Defeat<Abilities::OppPotion>,
		Abilities::Defeat<Abilities::LifePerDamage>
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

