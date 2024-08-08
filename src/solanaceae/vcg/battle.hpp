#pragma once

#include <cstdint>
#include <regex>
#include <vector>
#include <memory>
#include <variant>
#include <string>
#include <charconv>
#include <cassert>

#if 0

// commands are what modify the state?
namespace BattleCommands {

struct Damage {
	size_t player_to{0};
	int32_t damage {0};
	// src - what part of the card did this?
};

struct Power {
	size_t player_to{0};
	int32_t power {0};
	// src - what part of the card did this?
};

} // BattleCommands

struct BattleCommand {
	std::variant<
};

struct BattleGeneratorI {
	virtual std::unique_ptr<BattleGeneratorI> tick(std::vector<BattleCommand>& commands_out/*, state*/) = 0;
	virtual bool end(void) { return false; } // return true if in an end state
};

#endif

