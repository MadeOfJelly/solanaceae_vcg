#include "./sp_gui_states.hpp"

#include "./card.hpp"
#include "./game_state.hpp"

#include <imgui.h>

#include <cstdint>
#include <memory>
#include <numeric>
#include <optional>
#include <variant>
#include <concepts>

#include <iostream>

template<typename RNG>
static TurnSelection turnSelectRandom(RNG& rng, const std::vector<Card>& cards, const std::vector<bool>& cards_used, const PlayerVolatiles& vol) {
	const bool last_round = std::accumulate(cards_used.cbegin(), cards_used.cend(), 0) == 3;
	size_t extra_pots = 0;
	if (last_round) {
		extra_pots = vol.pots;
	} else {
		extra_pots = rng()%(vol.pots + 1);
	}

	bool frenzy = (vol.pots - extra_pots) >= 3 ? rng()%10 == 0 : false;

	size_t card_idx = rng()%cards.size();
	while (cards_used.at(card_idx)) {
		card_idx = (card_idx+1)%cards.size();
	}

	return {
		cards,
		card_idx,
		extra_pots,
		frenzy,
	};
}

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


// TODO: fragile, runtime
// out of date?
bool holds_defeat(const auto& a) {
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

bool holds_stop_activation(const auto& a) {
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
		std::holds_alternative<Abilities::Stop<Abilities::Heal>>(a.a) ||
		std::holds_alternative<Abilities::Stop<Abilities::Poison>>(a.a) ||
		std::holds_alternative<Abilities::Stop<Abilities::SelfPoison>>(a.a) ||
		std::holds_alternative<Abilities::Stop<Abilities::RecoverPotions>>(a.a) ||
		std::holds_alternative<Abilities::Stop<Abilities::StopOppAbility>>(a.a) ||
		std::holds_alternative<Abilities::Stop<Abilities::StopOppBonus>>(a.a)
	;
}

bool holds_courage(const auto& a) {
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
		std::holds_alternative<Abilities::Courage<Abilities::StopOppBonus>>(a.a)
	;
}

bool holds_revenge(const auto& a) {
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
		std::holds_alternative<Abilities::Revenge<Abilities::Heal>>(a.a) ||
		std::holds_alternative<Abilities::Revenge<Abilities::Poison>>(a.a) ||
		std::holds_alternative<Abilities::Revenge<Abilities::SelfPoison>>(a.a) ||
		std::holds_alternative<Abilities::Revenge<Abilities::RecoverPotions>>(a.a) ||
		std::holds_alternative<Abilities::Revenge<Abilities::StopOppAbility>>(a.a) ||
		std::holds_alternative<Abilities::Revenge<Abilities::StopOppBonus>>(a.a)
	;
}

bool holds_team(const auto& a) {
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
		std::holds_alternative<Abilities::Team<Abilities::Heal>>(a.a) ||
		std::holds_alternative<Abilities::Team<Abilities::Poison>>(a.a) ||
		std::holds_alternative<Abilities::Team<Abilities::SelfPoison>>(a.a) ||
		std::holds_alternative<Abilities::Team<Abilities::RecoverPotions>>(a.a) ||
		std::holds_alternative<Abilities::Team<Abilities::StopOppAbility>>(a.a) ||
		std::holds_alternative<Abilities::Team<Abilities::StopOppBonus>>(a.a)
	;
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

static inline void cardHoverDetails(const Card& card) {
	if (ImGui::BeginItemTooltip()) {
		ImGui::Text("Name: %s", card.name.c_str());
		ImGui::Text("Level: %hu", card.level);
		ImGui::Text("Power: %hu", card.power);
		ImGui::Text("Damage: %hu", card.damage);
		ImGui::Separator();
		ImGui::Text("Ability: %s", card.ability.string.c_str());
		ImGui::Text("Faction: %s", card.faction_bonus.string.c_str());
		ImGui::Separator();
		ImGui::TextWrapped("%s", card.description.c_str());
		ImGui::EndTooltip();
	}
}

std::unique_ptr<PhaseI> PhaseCardSelection::render_impl(GameState& gs, std::optional<Round>& round, float) {
	if (!round) {
		// construct current round
		round = Round{};
		round->players.at(0) = gs.nextRoundStartingPlayer();
		round->players.at(1) = (round->players.at(0)+1)%2;
	}

	if (round->turns.size() == 2) {
		return std::make_unique<PhaseRevealSelections>();
	} else {
		if (round->players.at(round->turns.size()) == 0) {
			return std::make_unique<PhaseCardSelectionHuman>(gs);
		} else {
			return std::make_unique<PhaseCardSelectionBot>();
		}
	}
	return nullptr;
}

PhaseCardSelectionHuman::PhaseCardSelectionHuman(const GameState& gs) : _turn(gs.cards.at(0)) {
}

std::unique_ptr<PhaseI> PhaseCardSelectionHuman::render_impl(GameState& gs, std::optional<Round>& round, float) {
	assert(round);

	ImGui::Indent();
	for (size_t i = 0; i < _turn.deck.size(); i++) {
		const auto label = _turn.deck.at(i).toStringNLPD();
		// TODO: annoying, remove deck from turn?
		const bool used = gs.cards_used.at(0).at(i);
		if (used) {
			ImGui::Selectable(label.c_str(), false, ImGuiSelectableFlags_Disabled);
		} else {
			if (ImGui::Selectable(label.c_str(), i == _turn.card_idx)) {
				_turn.card_idx = i;
			}
		}
		cardHoverDetails(gs.cards.at(0).at(i));
	}
	ImGui::Unindent();

	ImGui::TextUnformatted("> select a card, pots and frenzy");

	ImGui::Text("have pots: %d", gs.vols.at(0).pots);
	{
		const size_t min_v {0};
		const size_t max_v {static_cast<size_t>(std::max(0, gs.vols.at(0).pots - _turn.frenzy*3))};
		ImGui::SliderScalar("extra pots", ImGuiDataType_U64, &_turn.pots, &min_v, &max_v);
	}

	if (ImGui::Checkbox("frenzy (+2 dmg for 3 pots)", &_turn.frenzy)) {
		if (int64_t(_turn.pots + _turn.frenzy*3) > int64_t(gs.vols.at(0).pots)) {
			_turn.frenzy = false;
		}
	}

	ImGui::Text("attack: %zu (without abilities)", _turn.card().power * (1+_turn.pots));
	ImGui::TextDisabled("^ the most useless metric ever");

	if (ImGui::Button("confirm")) {
		round->turns.emplace_back(_turn);
		return std::make_unique<PhaseCardSelection>();
	}

	return nullptr;
}

std::unique_ptr<PhaseI> PhaseCardSelectionBot::render_impl(GameState& gs, std::optional<Round>& round, float) {
	assert(round);
	ImGui::TextUnformatted("smart-ai 9000 is thinking...");
	if (_timer >= _fake_time) {
		// "smart-ai™ 9000"
		round->turns.emplace_back(turnSelectRandom(_rng, gs.cards.at(1), gs.cards_used.at(1), gs.vols.at(1)));
		return std::make_unique<PhaseCardSelection>();
	}
	return nullptr;
}

std::unique_ptr<PhaseI> PhaseRevealSelections::render_impl(GameState& gs, std::optional<Round>& round, float) {
	assert(round);

	size_t human_idx = round->players.at(0) == 0 ? 0 : 1;
	size_t bot_idx = (human_idx+1)%2;

	if (round->turns.at(bot_idx).haveFactionBonus()) {
		ImGui::TextUnformatted("bot has faction bonus.");
	}
	if (round->turns.at(human_idx).haveFactionBonus()) {
		ImGui::TextUnformatted("you have faction bonus.");
	}

	ImGui::Text("bot chose 1+%zu pots%s.", round->turns.at(bot_idx).pots, round->turns.at(bot_idx).frenzy ? ", and frenzy" : "");
	ImGui::Text("you chose 1+%zu pots%s.", round->turns.at(human_idx).pots, round->turns.at(human_idx).frenzy ? ", and frenzy" : "");
	if (ImGui::Button("continue to battle")) {
		return std::make_unique<PhaseBattle>();
	}

	return nullptr;
}

// sad
//// strip wrapper
//template<typename T>
//    requires requires(T t) { t.inner; }
//void doAbility(Round& round, size_t ridx, const Ability& ability) {
//    std::cout << "removed wrapper " << typeid(T).name() << "\n";
//    doAbility<decltype(T::inner)>(round, ridx, ability, is_faction_bonus);
//}

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

#if 0
template<typename A>
bool holds_alternative_variants(const auto& variant) {
	return
		holds_alternative_safe<A>(variant) ||
		//holds_alternative_safe<Abilities::Defeat<A>>(variant) ||
		holds_alternative_safe<Abilities::Stop<A>>(variant) ||
		holds_alternative_safe<Abilities::Courage<A>>(variant) ||
		holds_alternative_safe<Abilities::Revenge<A>>(variant)
	;
}
#endif

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
const T& get_safe(const std::variant<Args...>& v) {
	if constexpr (contains_type<T, Args...>()) {
		return std::get<T>(v);
	} else {
		assert(false);
		static T t{};
		return t;
	}
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

template<typename T>
//void doAbility(Round& round, size_t ridx, const Ability& ability) = delete;
void doAbility(Round& /*round*/, size_t /*ridx*/, const Ability& ability) {
	// do nothing
	std::cout << "nop for " << ability.a.index() << " '" << typeid(T).name() << "'\n";
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
		round.volatile_temps.at(ridx).hp,
		ability
	);
}

template<typename T>
requires
	same_as_variants<T, Abilities::OppLife>
void doAbility(Round& round, size_t ridx, const Ability& ability) {
	size_t opp_ridx = (ridx+1)%2;
	apply_value_ability<T>(
		round.volatile_temps.at(opp_ridx).hp,
		ability
	);
}

template<typename T>
requires
	same_as_variants<T, Abilities::StealLife>
void doAbility(Round& round, size_t ridx, const Ability& ability) {
	size_t opp_ridx = (ridx+1)%2;
	const auto value_before = round.volatile_temps.at(opp_ridx).hp;
	apply_value_ability<T>(
		round.volatile_temps.at(opp_ridx).hp,
		ability,
		true
	);
	const auto diff = value_before - round.volatile_temps.at(opp_ridx).hp;
	round.volatile_temps.at(ridx).hp += diff; // steal
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
	round.volatile_temps.at(ridx).hp += get_ability_value(a_v) * round.card_temps.at(ridx).damage;
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
void doAbilitiesPlayerWrapRevenge(const GameState& gs, Round& round, size_t ridx, bool faction_bonus) {
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
void doAbilitiesPlayerWrapTeam(const GameState& gs, Round& round, size_t ridx, bool faction_bonus) {
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
void doAbilitiesPlayerWrapStop(const GameState& gs, Round& round, size_t ridx, bool faction_bonus) {
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
void doAbilitiesPlayerWrapCourage(const GameState& gs, Round& round, size_t ridx, bool faction_bonus) {
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
void doAbilitiesPlayer(const GameState& gs, Round& round, size_t ridx) {
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
void doAbilities(const GameState& gs, Round& round) {
	for (size_t i = 0; i < round.card_temps.size(); i++) {
		doAbilitiesPlayer<T>(gs, round, i);
	}

	// continue on
	if constexpr (sizeof...(Ts) > 0) {
		doAbilities<Ts...>(gs, round);
	}
}

std::unique_ptr<PhaseI> PhaseBattle::render_impl(GameState& gs, std::optional<Round>& round_opt, float) {
	assert(round_opt);
	auto& round = round_opt.value();

	// calculate all the values for the selected cards (temp cards)
	for (size_t i = 0; i < round.card_temps.size(); i++) { // fill in base
		round.card_temps.at(i).power = round.turns.at(i).card().power;
		round.card_temps.at(i).damage = round.turns.at(i).card().damage;
	}

	doAbilities<
		Abilities::StopOppAbility,
		Abilities::StopOppBonus
	>(gs, round);

	// copy abilities (before frenzy)
	doAbilities<
		Abilities::CopyPower,
		Abilities::CopyDamage
	>(gs, round);

	for (size_t i = 0; i < round.card_temps.size(); i++) { // fill in base
		// apply frenzy dmg bonus
		if (round.turns.at(i).frenzy) {
			round.card_temps.at(i).damage += 2;
		}

		// init temp vols, so we can edit them in respects to min/max
		round.volatile_temps.at(i).hp = gs.vols.at(round.players.at(i)).hp;
		round.volatile_temps.at(i).pots = gs.vols.at(round.players.at(i)).pots - (round.turns.at(i).pots + round.turns.at(i).frenzy*3);
	}

	// apply power and dmg
	doAbilities<
		Abilities::Power,
		Abilities::Damage,
		Abilities::OppPower,
		Abilities::OppDamage
	>(gs, round);

	// calc attack
	for (size_t i = 0; i < round.card_temps.size(); i++) {
		round.card_temps.at(i).attack = round.card_temps.at(i).power * (round.turns.at(i).pots + 1);
	}

	doAbilities<
		Abilities::Attack,
		Abilities::OppAttack
	>(gs, round);

	auto [win_ridx, reason] = round.decide_winning_card();
	const size_t loose_ridx = (win_ridx+1)%2;

	// the primary dmg -> hp effect
	round.volatile_temps.at(loose_ridx).hp -= round.card_temps.at(win_ridx).damage;

	{ // win
		doAbilitiesPlayer<
			Abilities::LifePerDamage,
			Abilities::RecoverPotions,
			Abilities::Life,
			Abilities::Potion,
			Abilities::LifeMin,
			Abilities::PotionMin,
			Abilities::OppLife,
			Abilities::OppPotion,
			Abilities::StealLife,
			Abilities::StealPotion,
			Abilities::Poison,
			Abilities::SelfPoison,
			Abilities::Heal
		>(gs, round, win_ridx);
	}

	{ // loose (defeat)
		doAbilitiesPlayer<
			//Abilities::Defeat<Abilities::LifePerDamage> // ??
			Abilities::Defeat<Abilities::RecoverPotions>,
			Abilities::Defeat<Abilities::Life>,
			Abilities::Defeat<Abilities::Potion>,
			Abilities::Defeat<Abilities::LifeMin>,
			Abilities::Defeat<Abilities::PotionMin>,
			Abilities::Defeat<Abilities::OppLife>,
			Abilities::Defeat<Abilities::OppPotion>,
			Abilities::Defeat<Abilities::StealLife>,
			Abilities::Defeat<Abilities::StealPotion>,
			Abilities::Defeat<Abilities::Poison>,
			Abilities::Defeat<Abilities::SelfPoison>,
			Abilities::Defeat<Abilities::Heal>
		>(gs, round, loose_ridx);
	}

	{ // tick heal
		int16_t strongst_heal_p0 {0};
		int16_t strongst_heal_p1 {0};

		// curr round
		size_t ridx_p0 = round.players.at(0) == 0 ? 0 : 1;
		size_t ridx_p1 = (ridx_p0+1)%2;

		for (const auto& prev_round : gs.rounds) {
			// prev round
			size_t pridx_p0 = prev_round.players.at(0) == 0 ? 0 : 1;
			size_t pridx_p1 = (pridx_p0+1)%2;
			for (const auto& [h_v, h_m] : prev_round.heals.at(pridx_p0)) {
				auto nt = std::min<int16_t>(round.volatile_temps.at(ridx_p0).hp + h_v, h_m);
				auto diff = nt - round.volatile_temps.at(ridx_p0).hp;
				if (diff > strongst_heal_p0) {
					strongst_heal_p0 = diff;
				}
			}
			for (const auto& [h_v, h_m] : prev_round.heals.at(pridx_p1)) {
				auto nt = std::min<int16_t>(round.volatile_temps.at(ridx_p1).hp + h_v, h_m);
				auto diff = nt - round.volatile_temps.at(ridx_p1).hp;
				if (diff > strongst_heal_p1) {
					strongst_heal_p1 = diff;
				}
			}
		}

		round.volatile_temps.at(ridx_p0).hp += strongst_heal_p0;
		round.volatile_temps.at(ridx_p1).hp += strongst_heal_p1;
	}
	{ // tick poison
		int16_t strongst_poison_p0 {0};
		int16_t strongst_poison_p1 {0};

		// curr round
		size_t ridx_p0 = round.players.at(0) == 0 ? 0 : 1;
		size_t ridx_p1 = (ridx_p0+1)%2;

		for (const auto& prev_round : gs.rounds) {
			// prev round
			size_t pridx_p0 = prev_round.players.at(0) == 0 ? 0 : 1;
			size_t pridx_p1 = (pridx_p0+1)%2;
			for (const auto& [p_v, p_m] : prev_round.poisons.at(pridx_p0)) {
				auto nt = std::max<int16_t>(round.volatile_temps.at(ridx_p0).hp - p_v, p_m);
				auto diff = nt - round.volatile_temps.at(ridx_p0).hp;
				if (diff < strongst_poison_p0) {
					strongst_poison_p0 = diff;
				}
			}
			for (const auto& [p_v, p_m] : prev_round.poisons.at(pridx_p1)) {
				auto nt = std::max<int16_t>(round.volatile_temps.at(ridx_p1).hp - p_v, p_m);
				auto diff = nt - round.volatile_temps.at(ridx_p1).hp;
				if (diff < strongst_poison_p1) {
					strongst_poison_p1 = diff;
				}
			}
		}

		round.volatile_temps.at(ridx_p0).hp += strongst_poison_p0;
		round.volatile_temps.at(ridx_p1).hp += strongst_poison_p1;
	}

	// sanitize pots
	round.volatile_temps.at(0).pots = std::max<int16_t>(round.volatile_temps.at(0).pots, 0);
	round.volatile_temps.at(1).pots = std::max<int16_t>(round.volatile_temps.at(1).pots, 0);

	return std::make_unique<PhaseBattleEnd>();
}

std::unique_ptr<PhaseI> PhaseBattleEnd::render_impl(GameState& gs, std::optional<Round>& round, float) {
	assert(round);

	size_t human_idx = round->players.at(0) == 0 ? 0 : 1;
	size_t bot_idx = (human_idx+1)%2;

	if (round->turns.at(bot_idx).haveFactionBonus()) {
		ImGui::TextUnformatted("bot has faction bonus.");
	}
	if (round->turns.at(human_idx).haveFactionBonus()) {
		ImGui::TextUnformatted("you have faction bonus.");
	}

	ImGui::Text("bot chose 1+%zu pots%s.", round->turns.at(bot_idx).pots, round->turns.at(bot_idx).frenzy ? ", and frenzy" : "");
	ImGui::Text("you chose 1+%zu pots%s.", round->turns.at(human_idx).pots, round->turns.at(human_idx).frenzy ? ", and frenzy" : "");

	// show values
	ImGui::Text("bot  attack: %hd", round->card_temps.at(bot_idx).attack);
	ImGui::Text("your attack: %hd", round->card_temps.at(human_idx).attack);

	// show winner
	auto [win_ridx, reason] = round->decide_winning_card();
	const auto winning_player = round->players.at(win_ridx);
	if (winning_player == 0) {
		ImGui::TextUnformatted("player wins round!");
	} else {
		ImGui::TextUnformatted("bot wins round.");
	}
	ImGui::SameLine();
	switch (reason) {
		case Round::WinReason::ATTACK:
			ImGui::TextUnformatted("by attack");
			break;
		case Round::WinReason::LEVEL:
			ImGui::TextUnformatted("by level");
			break;
		case Round::WinReason::DEFAULT:
			ImGui::TextUnformatted("by default");
			break;
	}

	ImGui::SeparatorText("resulting in");
	ImGui::Text("bot  hp: %d (%+d)", round->volatile_temps.at(bot_idx).hp, round->volatile_temps.at(bot_idx).hp - gs.vols.at(1).hp);
	ImGui::Text("your hp: %d (%+d)", round->volatile_temps.at(human_idx).hp, round->volatile_temps.at(human_idx).hp - gs.vols.at(0).hp);
	ImGui::Text("bot  pots: %d (%+d)", round->volatile_temps.at(bot_idx).pots, round->volatile_temps.at(bot_idx).pots - gs.vols.at(1).pots);
	ImGui::Text("your pots: %d (%+d)", round->volatile_temps.at(human_idx).pots, round->volatile_temps.at(human_idx).pots - gs.vols.at(0).pots);

	if (!round->poisons.at(bot_idx).empty()) {
		ImGui::Text("bot suffered poison:");
		ImGui::Indent();
		for (const auto& poison : round->poisons.at(bot_idx)) {
			ImGui::Text("%d, min %d", poison.value, poison.min);
		}
		ImGui::Unindent();
	}
	if (!round->poisons.at(human_idx).empty()) {
		ImGui::Text("you suffered poison:");
		ImGui::Indent();
		for (const auto& poison : round->poisons.at(human_idx)) {
			ImGui::Text("%d, min %d", poison.value, poison.min);
		}
		ImGui::Unindent();
	}

	if (!round->heals.at(bot_idx).empty()) {
		ImGui::Text("bot received heal:");
		ImGui::Indent();
		for (const auto& heal : round->heals.at(bot_idx)) {
			ImGui::Text("%d, max %d", heal.value, heal.max);
		}
		ImGui::Unindent();
	}
	if (!round->heals.at(human_idx).empty()) {
		ImGui::Text("you received heal:");
		ImGui::Indent();
		for (const auto& heal : round->heals.at(human_idx)) {
			ImGui::Text("%d, max %d", heal.value, heal.max);
		}
		ImGui::Unindent();
	}

	if (ImGui::Button("continue")) {
		// apply dmg here? or ad end of battle?

		gs.update(*round);
		round = std::nullopt;

		std::cout << "--- round ---\n";

		if (gs.rounds.size() == 4 || gs.vols.at(0).hp <= 0 || gs.vols.at(1).hp <= 0) {
			return std::make_unique<PhaseEndScreen>();
		} else {
			return std::make_unique<PhaseCardSelection>();
		}
	}

	return nullptr;
}

std::unique_ptr<PhaseI> PhaseEndScreen::render_impl(GameState& gs, std::optional<Round>& round, float) {
	assert(!round);

	if (gs.vols.at(0).hp > gs.vols.at(1).hp) {
		ImGui::TextUnformatted("You won!");
	} else if (gs.vols.at(0).hp < gs.vols.at(1).hp) {
		ImGui::TextUnformatted("Bot won.");
	} else {
		ImGui::TextUnformatted("Draw!");
	}

	return nullptr;
}
