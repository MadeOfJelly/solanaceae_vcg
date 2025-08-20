#pragma once

#include "./ability_utils.hpp"
#include "./game_state.hpp"

#include <iostream> // meh

template<typename T>
//void doAbility(Round& round, size_t ridx, const Ability& ability) = delete;
inline void doAbility(Round& /*round*/, size_t /*ridx*/, const Ability& ability) {
	// not an issue if stacked (might appear for defeat), otherwise report.
	// do nothing
	std::cout << "VCG warn: nop for " << ability.a.index() << " '" << typeid(T).name() << "'\n";
}

template<typename T>
requires
	same_as_variants<T, Abilities::StopOppAbility>
void doAbility(Round& round, size_t ridx, const Ability& ability) {
	if (!holds_alternative_safe<T>(ability.a)) {
		return;
	}
	size_t opp_ridx = (ridx+1)%2;
	round.card_stopped.at(opp_ridx).at(0) = true;
}

template<typename T>
requires
	same_as_variants<T, Abilities::StopOppBonus>
void doAbility(Round& round, size_t ridx, const Ability& ability) {
	if (!holds_alternative_safe<T>(ability.a)) {
		return;
	}
	size_t opp_ridx = (ridx+1)%2;
	round.card_stopped.at(opp_ridx).at(1) = true;
}

template<typename T>
requires
	same_as_variants<T, Abilities::CopyPower>
void doAbility(Round& round, size_t ridx, const Ability& ability) {
	if (!holds_alternative_safe<T>(ability.a)) {
		return;
	}
	size_t opp_ridx = (ridx+1)%2;
	round.card_temps.at(ridx).power = round.turns.at(opp_ridx).card().power;
}

template<typename T>
requires
	same_as_variants<T, Abilities::CopyDamage>
void doAbility(Round& round, size_t ridx, const Ability& ability) {
	if (!holds_alternative_safe<T>(ability.a)) {
		return;
	}
	size_t opp_ridx = (ridx+1)%2;
	round.card_temps.at(ridx).damage = round.turns.at(opp_ridx).card().damage;
}

template<typename T>
requires
	same_as_variants<T, Abilities::Power>
void doAbility(Round& round, size_t ridx, const Ability& ability) {
	apply_value_ability<T>(
		round.card_temps.at(ridx).power,
		ability
	);
}

template<typename T>
requires
	same_as_variants<T, Abilities::Damage>
void doAbility(Round& round, size_t ridx, const Ability& ability) {
	apply_value_ability<T>(
		round.card_temps.at(ridx).damage,
		ability
	);
}

template<typename T>
requires
	same_as_variants<T, Abilities::OppPower>
void doAbility(Round& round, size_t ridx, const Ability& ability) {
	size_t opp_ridx = (ridx+1)%2;
	apply_value_ability<T>(
		round.card_temps.at(opp_ridx).power,
		ability
	);
}

template<typename T>
requires
	same_as_variants<T, Abilities::OppDamage>
void doAbility(Round& round, size_t ridx, const Ability& ability) {
	size_t opp_ridx = (ridx+1)%2;
	apply_value_ability<T>(
		round.card_temps.at(opp_ridx).damage,
		ability
	);
}

template<typename T>
requires
	same_as_variants<T, Abilities::Attack>
void doAbility(Round& round, size_t ridx, const Ability& ability) {
	apply_value_ability<T>(
		round.card_temps.at(ridx).attack,
		ability
	);
}

template<typename T>
requires
	same_as_variants<T, Abilities::OppAttack>
void doAbility(Round& round, size_t ridx, const Ability& ability) {
	size_t opp_ridx = (ridx+1)%2;
	apply_value_ability<T>(
		round.card_temps.at(opp_ridx).attack,
		ability
	);
}

template<typename T>
requires
	same_as_variants<T, Abilities::Life> ||
	same_as_variants<T, Abilities::LifeMin>
void doAbility(Round& round, size_t ridx, const Ability& ability) {
	apply_value_ability<T>(
		round.volatile_temps.at(ridx).life,
		ability
	);
}

template<typename T>
requires
	same_as_variants<T, Abilities::OppLife>
void doAbility(Round& round, size_t ridx, const Ability& ability) {
	size_t opp_ridx = (ridx+1)%2;
	apply_value_ability<T>(
		round.volatile_temps.at(opp_ridx).life,
		ability
	);
}

template<typename T>
requires
	same_as_variants<T, Abilities::StealLife>
void doAbility(Round& round, size_t ridx, const Ability& ability) {
	size_t opp_ridx = (ridx+1)%2;
	const auto value_before = round.volatile_temps.at(opp_ridx).life;
	apply_value_ability<T>(
		round.volatile_temps.at(opp_ridx).life,
		ability,
		true
	);
	const auto diff = value_before - round.volatile_temps.at(opp_ridx).life;
	round.volatile_temps.at(ridx).life += diff; // steal
}

template<typename T>
requires
	same_as_variants<T, Abilities::Potion> ||
	same_as_variants<T, Abilities::PotionMin>
void doAbility(Round& round, size_t ridx, const Ability& ability) {
	apply_value_ability<T>(
		round.volatile_temps.at(ridx).pots,
		ability
	);
}

template<typename T>
requires
	same_as_variants<T, Abilities::OppPotion>
void doAbility(Round& round, size_t ridx, const Ability& ability) {
	size_t opp_ridx = (ridx+1)%2;
	apply_value_ability<T>(
		round.volatile_temps.at(opp_ridx).pots,
		ability
	);
}

template<typename T>
requires
	same_as_variants<T, Abilities::StealPotion>
void doAbility(Round& round, size_t ridx, const Ability& ability) {
	size_t opp_ridx = (ridx+1)%2;
	const auto value_before = round.volatile_temps.at(opp_ridx).pots;
	apply_value_ability<T>(
		round.volatile_temps.at(opp_ridx).pots,
		ability,
		true
	);
	const auto diff = value_before - round.volatile_temps.at(opp_ridx).pots;
	round.volatile_temps.at(ridx).pots += diff; // steal
}

template<typename T>
requires
	same_as_variants<T, Abilities::RecoverPotions>
void doAbility(Round& round, size_t ridx, const Ability& ability) {
	if (!holds_alternative_safe<T>(ability.a)) {
		return;
	}
	round.volatile_temps.at(ridx).pots += (round.turns.at(ridx).pots+2) / 2;
}

template<typename T>
requires
	same_as_variants<T, Abilities::LifePerDamage>
void doAbility(Round& round, size_t ridx, const Ability& ability) {
	// TODO: dewrapping getter
	//if (!holds_alternative_safe<Abilities::LifePerDamage>(ability.a)) {
	if (!std::holds_alternative<Abilities::LifePerDamage>(ability.a)) {
		return;
	}
	const auto& a_v = std::get<Abilities::LifePerDamage>(ability.a);
	round.volatile_temps.at(ridx).life += get_ability_value(a_v) * round.card_temps.at(ridx).damage;
}

template<typename T>
requires
	same_as_variants<T, Abilities::Poison>
void doAbility(Round& round, size_t ridx, const Ability& ability) {
	if (!holds_alternative_safe<T>(ability.a)) {
		return;
	}

	size_t opp_ridx = (ridx+1)%2;

	auto [p_v, p_m] = get_variants<Abilities::Poison>(ability.a);

	// add to round stack
	round.poisons.at(opp_ridx).emplace_back(p_v, p_m);
}

template<typename T>
requires
	same_as_variants<T, Abilities::SelfPoison>
void doAbility(Round& round, size_t ridx, const Ability& ability) {
	if (!holds_alternative_safe<T>(ability.a)) {
		return;
	}

	auto [p_v, p_m] = get_variants<Abilities::SelfPoison>(ability.a);

	// add to round stack to self
	round.poisons.at(ridx).emplace_back(p_v, p_m);
}

template<typename T>
requires
	same_as_variants<T, Abilities::Heal>
void doAbility(Round& round, size_t ridx, const Ability& ability) {
	if (!holds_alternative_safe<T>(ability.a)) {
		return;
	}

	auto [h_v, h_m] = get_variants<Abilities::Heal>(ability.a);

	// add heal to round heal stack
	round.heals.at(ridx).emplace_back(h_v, h_m);
}


// conditionally wraps
template<typename T>
inline void doAbilitiesPlayerWrapRevenge(const GameState& gs, Round& round, size_t ridx, bool faction_bonus) {
	const auto& card = round.turns.at(ridx).card();
	const auto& ability = faction_bonus ? card.faction_bonus : card.ability;

	if (!holds_revenge(ability)) {
		// forward T as is
		doAbility<T>(round, ridx, ability);
	} else if (!gs.rounds.empty()) { // have prev round(s)
		// check if ridx player lost prev round
		const auto& prev_round = gs.rounds.back();
		auto [win_pridx, _] = prev_round.decide_winning_card();

		if (prev_round.players.at(win_pridx) != round.players.at(ridx)) {
			doAbility<Abilities::Revenge<T>>(round, ridx, ability);
		} // else nop
	}
}

template<typename T>
inline void doAbilitiesPlayerWrapTeam(const GameState& gs, Round& round, size_t ridx, bool faction_bonus) {
	const auto& card = round.turns.at(ridx).card();
	const auto& ability = faction_bonus ? card.faction_bonus : card.ability;

	if (holds_team(ability)) {
		size_t number_of_activations = round.turns.at(ridx).sameFaction() + 1; // TODO: +1 to include self?
		for (size_t i = 0; i < number_of_activations; i++) {
			// HACK: runtime type injection
			doAbilitiesPlayerWrapRevenge<Abilities::Team<T>>(gs, round, ridx, faction_bonus);
		}
	} else {
		doAbilitiesPlayerWrapRevenge<T>(gs, round, ridx, faction_bonus);
	}
}

template<typename T>
inline void doAbilitiesPlayerWrapStop(const GameState& gs, Round& round, size_t ridx, bool faction_bonus) {
	const auto& card = round.turns.at(ridx).card();
	const auto& ability = faction_bonus ? card.faction_bonus : card.ability;

	if (holds_stop_activation(ability) == round.card_stopped.at(ridx).at(0+faction_bonus)) {
		if (holds_stop_activation(ability)) {
			// HACK: runtime type injection
			doAbilitiesPlayerWrapTeam<Abilities::Stop<T>>(gs, round, ridx, faction_bonus);
		} else {
			doAbilitiesPlayerWrapTeam<T>(gs, round, ridx, faction_bonus);
		}
	}
}

template<typename T>
inline void doAbilitiesPlayerWrapCourage(const GameState& gs, Round& round, size_t ridx, bool faction_bonus) {
	const auto& card = round.turns.at(ridx).card();
	const auto& ability = faction_bonus ? card.faction_bonus : card.ability;

	if (!holds_courage(ability)) {
		// forward T as is
		doAbilitiesPlayerWrapStop<T>(gs, round, ridx, faction_bonus);
	} else {
		// active
		if (ridx == 0) {
			// forward courage wrapped T
			// HACK: runtime type injection
			doAbilitiesPlayerWrapStop<Abilities::Courage<T>>(gs, round, ridx, faction_bonus);
		} // else nop
	}
}

// T is without Stop, Support, Courage, Revenge...
// T is with Defeat (and Win) (change?)
template<typename T, typename... Ts>
inline void doAbilitiesPlayer(const GameState& gs, Round& round, size_t ridx) {
	// TODO: account for "support:"

	// account for "Revenge:"
	// account for "Courage:"
	// account for "Stop:"

	doAbilitiesPlayerWrapCourage<T>(gs, round, ridx, false);

	// faction bonus
	if (round.turns.at(ridx).haveFactionBonus()) {
		doAbilitiesPlayerWrapCourage<T>(gs, round, ridx, true);
	}

	// continue on
	if constexpr (sizeof...(Ts) > 0) {
		doAbilitiesPlayer<Ts...>(gs, round, ridx);
	}
}

template<typename T, typename... Ts>
inline void doAbilities(const GameState& gs, Round& round) {
	for (size_t i = 0; i < round.card_temps.size(); i++) {
		doAbilitiesPlayer<T>(gs, round, i);
	}

	// continue on
	if constexpr (sizeof...(Ts) > 0) {
		doAbilities<Ts...>(gs, round);
	}
}

