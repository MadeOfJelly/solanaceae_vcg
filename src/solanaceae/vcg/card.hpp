#pragma once

#include <cstdint>
#include <variant>
#include <string>

namespace Abilities {
	struct OppDamage {
		int16_t value {0};
		int16_t min {0};
	};

	struct OppPower {
		int16_t value {0};
		int16_t min {0};
	};

	struct OppAttack {
		int16_t value {0};
		int16_t min {0};
	};

	struct OppLife {
		int16_t value {0};
		int16_t min {0};
	};

	struct OppPotion {
		int16_t value {0};
		int16_t min {0};
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

	struct LifeMin {
		int16_t value {0};
		int16_t min {0};
	};

	struct PotionMin {
		int16_t value {0};
		int16_t min {0};
	};

	struct StealLife {
		int16_t value {0};
		int16_t min {0};
	};

	struct StealPotion {
		int16_t value {0};
		int16_t min {0};
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
		int16_t max {0};
	};

	struct Poison {
		int16_t value {0};
		int16_t min {0};
	};

	struct SelfPoison {
		int16_t value {0};
		int16_t min {0};
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
	template<typename Inner> Stop( Inner ) -> Stop<Inner>;

	template<typename Inner>
	struct Courage {
		Inner inner;
	};
	template<typename Inner> Courage( Inner ) -> Courage<Inner>;

	template<typename Inner>
	struct Revenge {
		Inner inner;
	};
	template<typename Inner> Revenge( Inner ) -> Revenge<Inner>;

	template<typename Inner>
	struct Team {
		Inner inner;
	};
	template<typename Inner> Team( Inner ) -> Team<Inner>;
}

int16_t value_from_match(const std::string& match, const std::string& sign = "+");

struct Ability {
	Ability() = default;
	Ability(const std::string& string);

	std::variant<
		Abilities::OppDamage,	// w
		Abilities::OppPower,	// w
		Abilities::OppAttack,	// w
		Abilities::OppLife,		// w
		Abilities::OppPotion,	// w

		Abilities::Damage,		// w
		Abilities::Power,		// w
		Abilities::Attack,		// w
		Abilities::Life,		// w
		Abilities::Potion,		// w
		Abilities::LifeMin,
		Abilities::PotionMin,
		Abilities::StealLife,
		Abilities::StealPotion,

		Abilities::CopyDamage,	// w
		Abilities::CopyPower,	// w

		Abilities::LifePerDamage,	// w

		Abilities::Heal,
		Abilities::Poison,
		Abilities::SelfPoison,
		Abilities::RecoverPotions,	// w

		Abilities::StopOppAbility,
		Abilities::StopOppBonus,


		Abilities::Defeat<Abilities::OppLife>,			// w
		Abilities::Defeat<Abilities::OppPotion>,
		Abilities::Defeat<Abilities::Life>,				// w
		Abilities::Defeat<Abilities::Potion>,			// w
		Abilities::Defeat<Abilities::LifeMin>,
		Abilities::Defeat<Abilities::PotionMin>,
		Abilities::Defeat<Abilities::StealLife>,
		Abilities::Defeat<Abilities::StealPotion>,
		Abilities::Defeat<Abilities::LifePerDamage>, // ???
		Abilities::Defeat<Abilities::Heal>,
		Abilities::Defeat<Abilities::Poison>,
		Abilities::Defeat<Abilities::SelfPoison>,
		Abilities::Defeat<Abilities::RecoverPotions>,	// w


		Abilities::Stop<Abilities::OppDamage>,
		Abilities::Stop<Abilities::OppPower>, //
		Abilities::Stop<Abilities::OppAttack>,
		Abilities::Stop<Abilities::OppLife>,
		Abilities::Stop<Abilities::OppPotion>,

		Abilities::Stop<Abilities::Damage>, //
		Abilities::Stop<Abilities::Power>, //
		Abilities::Stop<Abilities::Attack>,

		Abilities::Stop<Abilities::Life>, //
		Abilities::Stop<Abilities::Potion>,
		Abilities::Stop<Abilities::LifeMin>,
		Abilities::Stop<Abilities::PotionMin>,
		Abilities::Stop<Abilities::StealLife>,
		Abilities::Stop<Abilities::StealPotion>,

		Abilities::Stop<Abilities::CopyDamage>,
		Abilities::Stop<Abilities::CopyPower>,

		Abilities::Stop<Abilities::LifePerDamage>,

		Abilities::Stop<Abilities::Heal>,
		Abilities::Stop<Abilities::Poison>,
		Abilities::Stop<Abilities::SelfPoison>,
		Abilities::Stop<Abilities::RecoverPotions>,

		// meh
		Abilities::Stop<Abilities::StopOppAbility>,
		Abilities::Stop<Abilities::StopOppBonus>,


		Abilities::Courage<Abilities::OppDamage>,
		Abilities::Courage<Abilities::OppPower>, //
		Abilities::Courage<Abilities::OppAttack>, //

		Abilities::Courage<Abilities::CopyDamage>,
		Abilities::Courage<Abilities::CopyPower>,

		Abilities::Courage<Abilities::Damage>, //
		Abilities::Courage<Abilities::Power>, //
		Abilities::Courage<Abilities::Attack>, //
		Abilities::Courage<Abilities::StopOppAbility>,
		Abilities::Courage<Abilities::StopOppBonus>, //


		Abilities::Revenge<Abilities::OppDamage>, //
		Abilities::Revenge<Abilities::OppPower>,
		Abilities::Revenge<Abilities::OppAttack>, //
		Abilities::Revenge<Abilities::OppLife>, //
		Abilities::Revenge<Abilities::OppPotion>,
		Abilities::Revenge<Abilities::Damage>, //
		Abilities::Revenge<Abilities::Power>, //
		Abilities::Revenge<Abilities::Attack>,
		Abilities::Revenge<Abilities::Life>,
		Abilities::Revenge<Abilities::Potion>, //
		Abilities::Revenge<Abilities::LifeMin>,
		Abilities::Revenge<Abilities::PotionMin>,
		Abilities::Revenge<Abilities::StealLife>,
		Abilities::Revenge<Abilities::StealPotion>,
		Abilities::Revenge<Abilities::CopyDamage>,
		Abilities::Revenge<Abilities::CopyPower>,
		Abilities::Revenge<Abilities::LifePerDamage>,
		Abilities::Revenge<Abilities::Heal>,
		Abilities::Revenge<Abilities::Poison>,
		Abilities::Revenge<Abilities::SelfPoison>,
		Abilities::Revenge<Abilities::RecoverPotions>,
		Abilities::Revenge<Abilities::StopOppAbility>,
		Abilities::Revenge<Abilities::StopOppBonus>, //


		Abilities::Team<Abilities::OppDamage>,
		Abilities::Team<Abilities::OppPower>,
		Abilities::Team<Abilities::OppAttack>, //
		Abilities::Team<Abilities::OppLife>, //
		Abilities::Team<Abilities::OppPotion>,
		Abilities::Team<Abilities::Damage>, //
		Abilities::Team<Abilities::Power>, //
		Abilities::Team<Abilities::Attack>, //
		Abilities::Team<Abilities::Life>, //
		Abilities::Team<Abilities::Potion>, //
		Abilities::Team<Abilities::LifeMin>,
		Abilities::Team<Abilities::PotionMin>,
		Abilities::Team<Abilities::StealLife>,
		Abilities::Team<Abilities::StealPotion>,
		Abilities::Team<Abilities::CopyDamage>,
		Abilities::Team<Abilities::CopyPower>,
		Abilities::Team<Abilities::LifePerDamage>,
		Abilities::Team<Abilities::Heal>,
		Abilities::Team<Abilities::Poison>,
		Abilities::Team<Abilities::SelfPoison>,
		Abilities::Team<Abilities::RecoverPotions>,
		Abilities::Team<Abilities::StopOppAbility>,
		Abilities::Team<Abilities::StopOppBonus>
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

