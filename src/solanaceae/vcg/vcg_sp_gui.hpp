#pragma once

#include "./vcg.hpp"

#include <memory>

struct CurrentGame;

// vcg single player
struct VCGSPGUI {
	std::unique_ptr<CurrentGame> _game;

	VCGSPGUI(void);
	~VCGSPGUI(void);
	float render(float delta);
};

