#pragma once

#include "./card.hpp"

#include <concepts>
#include <cassert>

template<typename T, typename... Args>
requires (std::same_as<T, Args> || ...)
constexpr bool contains_type(void) {
	return true;
}
template<typename T, typename... Args>
requires (!(std::same_as<T, Args> || ...))
constexpr bool contains_type(void) {
	return false;
}

template <typename>
constexpr bool ability_has_min(void) { return false; }
template <>
constexpr bool ability_has_min<Abilities::OppDamage>(void) { return true; }
template <>
constexpr bool ability_has_min<Abilities::OppPower>(void) { return true; }
template <>
constexpr bool ability_has_min<Abilities::OppAttack>(void) { return true; }
template <>
constexpr bool ability_has_min<Abilities::LifeMin>(void) { return true; }
template <>
constexpr bool ability_has_min<Abilities::PotionMin>(void) { return true; }
template <>
constexpr bool ability_has_min<Abilities::OppLife>(void) { return true; }
template <>
constexpr bool ability_has_min<Abilities::OppPotion>(void) { return true; }
template <>
constexpr bool ability_has_min<Abilities::StealLife>(void) { return true; }
template <>
constexpr bool ability_has_min<Abilities::StealPotion>(void) { return true; }
template <>
constexpr bool ability_has_min<Abilities::Poison>(void) { return true; }
template <>
constexpr bool ability_has_min<Abilities::SelfPoison>(void) { return true; }

template <typename T>
constexpr bool ability_has_min(void)
	requires requires(T t) { t.inner; }
{
	return ability_has_min<decltype(T::inner)>();
}

template <typename>
constexpr bool ability_has_max(void) { return false; }
template <>
constexpr bool ability_has_max<Abilities::Heal>(void) { return true; }

template <typename T>
constexpr bool ability_has_max(void)
	requires requires(T t) { t.inner; }
{
	return ability_has_max<decltype(T::inner)>();
}

template<typename T>
constexpr const auto& get_ability_value(const T& a)
	requires requires(T t) { t.value; }
{
	return a.value;
}
template<typename T>
constexpr const auto& get_ability_value(const T& a)
	requires requires(T t) { t.inner; }
{
	return get_ability_value(a.inner);
}

template<typename T>
constexpr const auto& get_ability_min(const T& a)
	requires requires(T t) { t.min; }
{
	return a.min;
}
template<typename T>
constexpr const auto& get_ability_min(const T& a)
	requires requires(T t) { t.inner; }
{
	return get_ability_min(a.inner);
}

template<typename T>
constexpr const auto& get_ability_max(const T& a)
	requires requires(T t) { t.max; }
{
	return a.max;
}
template<typename T>
constexpr const auto& get_ability_max(const T& a)
	requires requires(T t) { t.inner; }
{
	return get_ability_max(a.inner);
}

template<typename T, typename... Args>
constexpr bool variant_contains_type(const std::variant<Args...>) {
	return contains_type<T, Args...>();
}

template<typename T>
constexpr bool ability_type_possible(void) {
	return variant_contains_type<T>(decltype(Ability{}.a){});
}

template<typename T>
static bool apply_value_ability(int16_t& value, const Ability& a, bool invert_value = false) {
	if constexpr (ability_type_possible<T>()) {
		if (std::holds_alternative<T>(a.a)) {
			const auto& a_var = std::get<T>(a.a);
			const auto value_before = value;

			const int16_t a_value = get_ability_value(a_var) * (invert_value ? -1 : 1);

			value += a_value;

			if constexpr (ability_has_min<T>()) {
				if (a_value < 0) {
					value = std::min<int16_t>(value_before, std::max<int16_t>(value, get_ability_min(a_var)));
				} // else cant dip
			} else if constexpr (ability_has_max<T>()) {
				//static_assert(false); // fails sometimes on clang (macos and android). Yes, sometimes.
				assert(false && "how did you get there");
			}
			return true;
		}
	}
	return false;
}
template<typename T, typename... Args>
static void apply_value_abilities(int16_t& value, const Ability& a, const Ability& b) {
	apply_value_ability<T>(value, a);
	apply_value_ability<T>(value, b);
	if constexpr (sizeof...(Args) > 0) {
		apply_value_abilities<Args...>(value, a, b);
	}
}

template<typename T, typename A>
concept same_as_variants =
	std::same_as<T, A> ||
	std::same_as<T, Abilities::Defeat<A>> ||
	std::same_as<T, Abilities::Stop<A>> ||
	std::same_as<T, Abilities::Courage<A>> ||
	std::same_as<T, Abilities::Revenge<A>> ||
	std::same_as<T, Abilities::Team<A>>
;

template<typename T, typename... Args>
bool holds_alternative_safe(const std::variant<Args...>& v) {
	if constexpr (contains_type<T, Args...>()) {
		return std::holds_alternative<T>(v);
	}
	return false;
}

template<typename T, typename... Args>
const T& get_safe(const std::variant<Args...>& v) {
	if constexpr (contains_type<T, Args...>()) {
		return std::get<T>(v);
	} else {
		assert(false);
		static T t{};
		return t;
	}
}

// catch all
template<typename A>
bool holds_alternative_variants_extra(const auto& variant) {
	return
		holds_alternative_safe<A>(variant) ||
		holds_alternative_safe<Abilities::Defeat<A>>(variant) ||
		holds_alternative_safe<Abilities::Stop<A>>(variant) ||
		holds_alternative_safe<Abilities::Courage<A>>(variant) ||
		holds_alternative_safe<Abilities::Revenge<A>>(variant) ||
		holds_alternative_safe<Abilities::Team<A>>(variant)
	;
}

template<typename T, typename... Args>
const T& get_variants(const std::variant<Args...>& v) {
	assert(holds_alternative_variants_extra<T>(v));

	if (std::holds_alternative<T>(v)) {
		return std::get<T>(v);
	} else if (holds_alternative_safe<Abilities::Defeat<T>>(v)) {
		return get_safe<Abilities::Defeat<T>>(v).inner;
	} else if (holds_alternative_safe<Abilities::Stop<T>>(v)) {
		return get_safe<Abilities::Stop<T>>(v).inner;
	} else if (holds_alternative_safe<Abilities::Courage<T>>(v)) {
		return get_safe<Abilities::Courage<T>>(v).inner;
	} else if (holds_alternative_safe<Abilities::Revenge<T>>(v)) {
		return get_safe<Abilities::Revenge<T>>(v).inner;
	} else if (holds_alternative_safe<Abilities::Team<T>>(v)) {
		return get_safe<Abilities::Team<T>>(v).inner;
	} else {
		assert(false);
		static T t{};
		return t;
	}
}


// TODO: rewrite with a simple bitset
bool holds_defeat(const Ability& a);
bool holds_stop_activation(const Ability& a);
bool holds_courage(const Ability& a);
bool holds_revenge(const Ability& a);
bool holds_team(const Ability& a);

