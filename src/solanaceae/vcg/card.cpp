#include "./card.hpp"

#include <cstdint>
#include <regex>
#include <stdexcept>
#include <vector>
#include <string>
#include <charconv>
#include <functional>
#include <utility>
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

struct MatcherEntry {
	std::regex r;
	std::function<void(const std::smatch&, decltype(Ability::a)&)> fn;
};

template<typename WrapperFN>
static std::vector<MatcherEntry> genMatchersPreAttack(const WrapperFN& wfn) {
	return std::vector<MatcherEntry> {
		{
			std::regex("([+-]) ([0-9]+) Opp Damage Min ([0-9]+)"),
			[&](const std::smatch& m, auto& _a) {
				_a = wfn(Abilities::OppDamage{
					value_from_match(m[2].str(), m[1].str()),
					value_from_match(m[3].str()),
				});
			}
		},
		{
			std::regex("([+-]) ([0-9]+) Opp Power Min ([0-9]+)"),
			[&](const std::smatch& m, auto& _a) {
				_a = wfn(Abilities::OppPower{
					value_from_match(m[2].str(), m[1].str()),
					value_from_match(m[3].str()),
				});
			}
		},
		{
			std::regex("([+-]) ([0-9]+) Damage"),
			[&](const std::smatch& m, auto& _a) {
				_a = wfn(Abilities::Damage{
					value_from_match(m[2].str(), m[1].str()),
				});
			}
		},
		{
			std::regex("([+-]) ([0-9]+) Power"),
			[&](const std::smatch& m, auto& _a) {
				_a = wfn(Abilities::Power{
					value_from_match(m[2].str(), m[1].str()),
				});
			}
		},
		{
			std::regex("Damage = Opp Damage"),
			[&](const std::smatch&, auto& _a) {
				_a = wfn(Abilities::CopyDamage{
				});
			}
		},
		{
			std::regex("Power = Opp Power"),
			[&](const std::smatch&, auto& _a) {
				_a = wfn(Abilities::CopyDamage{
				});
			}
		},
		{
			std::regex("Stop Opp Ability"),
			[&](const std::smatch&, auto& _a) {
				_a = wfn(Abilities::StopOppAbility{
				});
			}
		},
		{
			std::regex("Stop Opp Bonus"),
			[&](const std::smatch&, auto& _a) {
				_a = wfn(Abilities::StopOppBonus{
				});
			}
		},
	};
}

template<typename WrapperFN>
static std::vector<MatcherEntry> genMatchersAttack(const WrapperFN& wfn) {
	return std::vector<MatcherEntry> {
		{
			std::regex("([+-]) ([0-9]+) Opp Attack Min ([0-9]+)"),
			[&](const std::smatch& m, auto& _a) {
				_a = wfn(Abilities::OppAttack{
					value_from_match(m[2].str(), m[1].str()),
					value_from_match(m[3].str()),
				});
			}
		},
		{
			std::regex("([+-]) ([0-9]+) Attack"),
			[&](const std::smatch& m, auto& _a) {
				_a = wfn(Abilities::Attack{
					value_from_match(m[2].str(), m[1].str()),
				});
			}
		},
	};
}

template<typename WrapperFN>
static std::vector<MatcherEntry> genMatchersPostAttack(const WrapperFN& wfn) {
	return std::vector<MatcherEntry> {
		{
			std::regex("([+-]) ([0-9]+) Opp Life Min ([0-9]+)"),
			[&](const std::smatch& m, auto& _a) {
				_a = wfn(Abilities::OppLife{
					value_from_match(m[2].str(), m[1].str()),
					value_from_match(m[3].str()),
				});
			}
		},
		{
			std::regex("([+-]) ([0-9]+) Opp Potion Min ([0-9]+)"),
			[&](const std::smatch& m, auto& _a) {
				_a = wfn(Abilities::OppPotion{
					value_from_match(m[2].str(), m[1].str()),
					value_from_match(m[3].str()),
				});
			}
		},
		{
			std::regex("([+-]) ([0-9]+) Life"),
			[&](const std::smatch& m, auto& _a) {
				_a = wfn(Abilities::Life{
					value_from_match(m[2].str(), m[1].str()),
				});
			}
		},
		{
			std::regex("([+-]) ([0-9]+) Potion"),
			[&](const std::smatch& m, auto& _a) {
				_a = wfn(Abilities::Potion{
					value_from_match(m[2].str(), m[1].str()),
				});
			}
		},
		{
			std::regex("([+-]) ([0-9]+) Life per Damage"),
			[&](const std::smatch& m, auto& _a) {
				_a = wfn(Abilities::LifePerDamage{
					value_from_match(m[2].str(), m[1].str()),
				});
			}
		},
		{
			std::regex("([+-]) ([0-9]+) Life Min ([0-9]+)"),
			[&](const std::smatch& m, auto& _a) {
				_a = wfn(Abilities::LifeMin{
					value_from_match(m[2].str(), m[1].str()),
					value_from_match(m[3].str()),
				});
			}
		},
		{
			std::regex("([+-]) ([0-9]+) Potion Min ([0-9]+)"),
			[&](const std::smatch& m, auto& _a) {
				_a = wfn(Abilities::PotionMin{
					value_from_match(m[2].str(), m[1].str()),
					value_from_match(m[3].str()),
				});
			}
		},
		{
			std::regex("Steal ([0-9]+) Life Min ([0-9]+)"),
			[&](const std::smatch& m, auto& _a) {
				_a = wfn(Abilities::StealLife{
					value_from_match(m[1].str()),
					value_from_match(m[2].str()),
				});
			}
		},
		{
			std::regex("Steal ([0-9]+) Potion Min ([0-9]+)"),
			[&](const std::smatch& m, auto& _a) {
				_a = wfn(Abilities::StealPotion{
					value_from_match(m[1].str()),
					value_from_match(m[2].str()),
				});
			}
		},
		{
			std::regex("Heal ([0-9]+) Max ([0-9]+)"),
			[&](const std::smatch& m, auto& _a) {
				_a = wfn(Abilities::Heal{
					value_from_match(m[1].str()),
					value_from_match(m[2].str()),
				});
			}
		},
		{
			std::regex("Poison ([0-9]+) Min ([0-9]+)"),
			[&](const std::smatch& m, auto& _a) {
				_a = wfn(Abilities::Poison{
					value_from_match(m[1].str()),
					value_from_match(m[2].str()),
				});
			}
		},
		{
			std::regex("Self Poison ([0-9]+) Min ([0-9]+)"),
			[&](const std::smatch& m, auto& _a) {
				_a = wfn(Abilities::SelfPoison{
					value_from_match(m[1].str()),
					value_from_match(m[2].str()),
				});
			}
		},
		{
			std::regex("Recover 1 of 2 Potion"),
			[&](const std::smatch&, auto& _a) {
				_a = wfn(Abilities::RecoverPotions{
				});
			}
		},
	};
}

static auto empty_fn = [](auto&& a){ return a; };

bool applyRegexMatchers(const std::string& string, std::vector<MatcherEntry>& matchers, decltype(Ability::a)& a) {
	for (const auto& it : matchers) {
		std::smatch m;
		if (!std::regex_match(string, m, it.r)) {
			continue;
		}
		it.fn(m, a);
		return true;
	}
	return false;
}

Ability::Ability(const std::string& _string) : string(_string) {
	if (string.starts_with("Defeat: ")) {
		static auto fn = [](auto&& a_){ return Abilities::Defeat{std::move(a_)}; };
		static auto dmvPostA = genMatchersPostAttack(fn);

		const auto substring = string.substr(std::string_view{"Defeat: "}.size());

		if (applyRegexMatchers(substring, dmvPostA, a)) { return; }
	} else if (string.starts_with("Stop: ")) {
		static auto fn = [](auto&& a_){ return Abilities::Stop{std::move(a_)}; };
		static auto smvPreA = genMatchersPreAttack(fn);
		static auto smvA = genMatchersAttack(fn);
		static auto smvPostA = genMatchersPostAttack(fn);

		const auto substring = string.substr(std::string_view{"Stop: "}.size());

		if (applyRegexMatchers(substring, smvPreA, a)) { return; }
		if (applyRegexMatchers(substring, smvA, a)) { return; }
		if (applyRegexMatchers(substring, smvPostA, a)) { return; }
	} else if (string.starts_with("Courage: ")) {
		static auto fn = [](auto&& a_){ return Abilities::Courage{std::move(a_)}; };
		static auto smvPreA = genMatchersPreAttack(fn);
		static auto smvA = genMatchersAttack(fn);

		const auto substring = string.substr(std::string_view{"Courage: "}.size());

		if (applyRegexMatchers(substring, smvPreA, a)) { return; }
		if (applyRegexMatchers(substring, smvA, a)) { return; }
	} else if (string.starts_with("Revenge: ")) {
		static auto fn = [](auto&& a_){ return Abilities::Revenge{std::move(a_)}; };
		static auto smvPreA = genMatchersPreAttack(fn);
		static auto smvA = genMatchersAttack(fn);
		static auto smvPostA = genMatchersPostAttack(fn);

		const auto substring = string.substr(std::string_view{"Revenge: "}.size());

		if (applyRegexMatchers(substring, smvPreA, a)) { return; }
		if (applyRegexMatchers(substring, smvA, a)) { return; }
		if (applyRegexMatchers(substring, smvPostA, a)) { return; }
	} else if (string.starts_with("Team: ")) {
		static auto fn = [](auto&& a_){ return Abilities::Team{std::move(a_)}; };
		static auto smvPreA = genMatchersPreAttack(fn);
		static auto smvA = genMatchersAttack(fn);
		static auto smvPostA = genMatchersPostAttack(fn);

		const auto substring = string.substr(std::string_view{"Team: "}.size());

		if (applyRegexMatchers(substring, smvPreA, a)) { return; }
		if (applyRegexMatchers(substring, smvA, a)) { return; }
		if (applyRegexMatchers(substring, smvPostA, a)) { return; }
	} else if (string.starts_with("Backlash: ")) {
		// does nothing special
		static auto smvPreA = genMatchersPreAttack(empty_fn);
		static auto smvA = genMatchersAttack(empty_fn);
		static auto smvPostA = genMatchersPostAttack(empty_fn);

		const auto substring = string.substr(std::string_view{"Backlash: "}.size());

		if (applyRegexMatchers(substring, smvPreA, a)) { return; }
		if (applyRegexMatchers(substring, smvA, a)) { return; }
		if (applyRegexMatchers(substring, smvPostA, a)) { return; }
	} else {
		static auto mvPreA = genMatchersPreAttack(empty_fn);
		static auto mvA = genMatchersAttack(empty_fn);
		static auto mvPostA = genMatchersPostAttack(empty_fn);

		if (applyRegexMatchers(string, mvPreA, a)) { return; }
		if (applyRegexMatchers(string, mvA, a)) { return; }
		if (applyRegexMatchers(string, mvPostA, a)) { return; }
	}

	throw std::runtime_error("unknown ability, did not match");
}

std::string Card::toStringNLPD(void) const {
	return {
		"N:" + name + ","
		"P:" + std::to_string(power) + ","
		"L:" + std::to_string(level) + ","
		"D:" + std::to_string(damage)
	};
}

