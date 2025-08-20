#include "./ability_utils.hpp"

// TODO: fragile, runtime
// out of date?
bool holds_defeat(const Ability& a) {
	return
		std::holds_alternative<Abilities::Defeat<Abilities::Life>>(a.a) ||
		std::holds_alternative<Abilities::Defeat<Abilities::Potion>>(a.a) ||
		std::holds_alternative<Abilities::Defeat<Abilities::OppLife>>(a.a) ||
		std::holds_alternative<Abilities::Defeat<Abilities::OppPotion>>(a.a) ||
		std::holds_alternative<Abilities::Defeat<Abilities::StealLife>>(a.a) ||
		std::holds_alternative<Abilities::Defeat<Abilities::StealPotion>>(a.a) ||
		std::holds_alternative<Abilities::Defeat<Abilities::RecoverPotions>>(a.a) ||
		std::holds_alternative<Abilities::Defeat<Abilities::LifePerDamage>>(a.a) ||
		std::holds_alternative<Abilities::Defeat<Abilities::Heal>>(a.a) ||
		std::holds_alternative<Abilities::Defeat<Abilities::Poison>>(a.a) ||
		std::holds_alternative<Abilities::Defeat<Abilities::SelfPoison>>(a.a)
	;
}

bool holds_stop_activation(const Ability& a) {
	return
		std::holds_alternative<Abilities::Stop<Abilities::OppDamage>>(a.a) ||
		std::holds_alternative<Abilities::Stop<Abilities::OppPower>>(a.a) ||
		std::holds_alternative<Abilities::Stop<Abilities::OppAttack>>(a.a) ||
		std::holds_alternative<Abilities::Stop<Abilities::OppLife>>(a.a) ||
		std::holds_alternative<Abilities::Stop<Abilities::OppPotion>>(a.a) ||
		std::holds_alternative<Abilities::Stop<Abilities::Damage>>(a.a) ||
		std::holds_alternative<Abilities::Stop<Abilities::Power>>(a.a) ||
		std::holds_alternative<Abilities::Stop<Abilities::Attack>>(a.a) ||
		std::holds_alternative<Abilities::Stop<Abilities::Life>>(a.a) ||
		std::holds_alternative<Abilities::Stop<Abilities::Potion>>(a.a) ||
		std::holds_alternative<Abilities::Stop<Abilities::LifeMin>>(a.a) ||
		std::holds_alternative<Abilities::Stop<Abilities::PotionMin>>(a.a) ||
		std::holds_alternative<Abilities::Stop<Abilities::StealLife>>(a.a) ||
		std::holds_alternative<Abilities::Stop<Abilities::StealPotion>>(a.a) ||
		std::holds_alternative<Abilities::Stop<Abilities::CopyDamage>>(a.a) ||
		std::holds_alternative<Abilities::Stop<Abilities::CopyPower>>(a.a) ||
		std::holds_alternative<Abilities::Stop<Abilities::LifePerDamage>>(a.a) ||
		std::holds_alternative<Abilities::Stop<Abilities::RecoverPotions>>(a.a) ||
		std::holds_alternative<Abilities::Stop<Abilities::StopOppAbility>>(a.a) ||
		std::holds_alternative<Abilities::Stop<Abilities::StopOppBonus>>(a.a)
	;
}

bool holds_courage(const Ability& a) {
	return
		std::holds_alternative<Abilities::Courage<Abilities::OppDamage>>(a.a) ||
		std::holds_alternative<Abilities::Courage<Abilities::OppPower>>(a.a) ||
		std::holds_alternative<Abilities::Courage<Abilities::OppAttack>>(a.a) ||
		std::holds_alternative<Abilities::Courage<Abilities::CopyDamage>>(a.a) ||
		std::holds_alternative<Abilities::Courage<Abilities::CopyPower>>(a.a) ||
		std::holds_alternative<Abilities::Courage<Abilities::Damage>>(a.a) ||
		std::holds_alternative<Abilities::Courage<Abilities::Power>>(a.a) ||
		std::holds_alternative<Abilities::Courage<Abilities::Attack>>(a.a) ||
		std::holds_alternative<Abilities::Courage<Abilities::StopOppAbility>>(a.a) ||
		std::holds_alternative<Abilities::Courage<Abilities::StopOppBonus>>(a.a) ||
		std::holds_alternative<Abilities::Courage<Abilities::StealLife>>(a.a) ||
		std::holds_alternative<Abilities::Courage<Abilities::StealPotion>>(a.a) ||
		std::holds_alternative<Abilities::Courage<Abilities::Heal>>(a.a) ||
		std::holds_alternative<Abilities::Courage<Abilities::Poison>>(a.a) ||
		std::holds_alternative<Abilities::Courage<Abilities::SelfPoison>>(a.a)
	;
}

bool holds_revenge(const Ability& a) {
	return
		std::holds_alternative<Abilities::Revenge<Abilities::OppDamage>>(a.a) ||
		std::holds_alternative<Abilities::Revenge<Abilities::OppPower>>(a.a) ||
		std::holds_alternative<Abilities::Revenge<Abilities::OppAttack>>(a.a) ||
		std::holds_alternative<Abilities::Revenge<Abilities::OppLife>>(a.a) ||
		std::holds_alternative<Abilities::Revenge<Abilities::OppPotion>>(a.a) ||
		std::holds_alternative<Abilities::Revenge<Abilities::Damage>>(a.a) ||
		std::holds_alternative<Abilities::Revenge<Abilities::Power>>(a.a) ||
		std::holds_alternative<Abilities::Revenge<Abilities::Attack>>(a.a) ||
		std::holds_alternative<Abilities::Revenge<Abilities::Life>>(a.a) ||
		std::holds_alternative<Abilities::Revenge<Abilities::Potion>>(a.a) ||
		std::holds_alternative<Abilities::Revenge<Abilities::LifeMin>>(a.a) ||
		std::holds_alternative<Abilities::Revenge<Abilities::PotionMin>>(a.a) ||
		std::holds_alternative<Abilities::Revenge<Abilities::StealLife>>(a.a) ||
		std::holds_alternative<Abilities::Revenge<Abilities::StealPotion>>(a.a) ||
		std::holds_alternative<Abilities::Revenge<Abilities::CopyDamage>>(a.a) ||
		std::holds_alternative<Abilities::Revenge<Abilities::CopyPower>>(a.a) ||
		std::holds_alternative<Abilities::Revenge<Abilities::LifePerDamage>>(a.a) ||
		std::holds_alternative<Abilities::Revenge<Abilities::RecoverPotions>>(a.a) ||
		std::holds_alternative<Abilities::Revenge<Abilities::StopOppAbility>>(a.a) ||
		std::holds_alternative<Abilities::Revenge<Abilities::StopOppBonus>>(a.a)
	;
}

bool holds_team(const Ability& a) {
	return
		std::holds_alternative<Abilities::Team<Abilities::OppDamage>>(a.a) ||
		std::holds_alternative<Abilities::Team<Abilities::OppPower>>(a.a) ||
		std::holds_alternative<Abilities::Team<Abilities::OppAttack>>(a.a) ||
		std::holds_alternative<Abilities::Team<Abilities::OppLife>>(a.a) ||
		std::holds_alternative<Abilities::Team<Abilities::OppPotion>>(a.a) ||
		std::holds_alternative<Abilities::Team<Abilities::Damage>>(a.a) ||
		std::holds_alternative<Abilities::Team<Abilities::Power>>(a.a) ||
		std::holds_alternative<Abilities::Team<Abilities::Attack>>(a.a) ||
		std::holds_alternative<Abilities::Team<Abilities::Life>>(a.a) ||
		std::holds_alternative<Abilities::Team<Abilities::Potion>>(a.a) ||
		std::holds_alternative<Abilities::Team<Abilities::LifeMin>>(a.a) ||
		std::holds_alternative<Abilities::Team<Abilities::PotionMin>>(a.a) ||
		std::holds_alternative<Abilities::Team<Abilities::StealLife>>(a.a) ||
		std::holds_alternative<Abilities::Team<Abilities::StealPotion>>(a.a) ||
		std::holds_alternative<Abilities::Team<Abilities::CopyDamage>>(a.a) ||
		std::holds_alternative<Abilities::Team<Abilities::CopyPower>>(a.a) ||
		std::holds_alternative<Abilities::Team<Abilities::LifePerDamage>>(a.a) ||
		std::holds_alternative<Abilities::Team<Abilities::RecoverPotions>>(a.a) ||
		std::holds_alternative<Abilities::Team<Abilities::StopOppAbility>>(a.a) ||
		std::holds_alternative<Abilities::Team<Abilities::StopOppBonus>>(a.a)
	;
}

