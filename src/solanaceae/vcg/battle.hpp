#pragma once

#include <cstddef>
#include <cstdint>

// fwd
struct GameState;
struct Round;

bool battle(GameState& gs, Round& round);

struct StrongestHeals {
	int16_t p0;
	int16_t p1;
};
struct StrongestPoisons {
	int16_t p0;
	int16_t p1;
};

// uses current round vols (post-battle)
StrongestHeals getStrongestHeals(const GameState& gs, const Round& curr_round);
StrongestPoisons getStrongestPoisons(const GameState& gs, const Round& curr_round);

bool hasHeal(const GameState& gs, size_t player);
bool hasPoison(const GameState& gs, size_t player);
