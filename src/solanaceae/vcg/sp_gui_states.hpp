#include "./game_state.hpp"

#include <memory>
#include <random>
#include <optional>

struct PhaseI {
	float _timer {0.f}; // time since phase start
	virtual ~PhaseI(void) {}

	virtual std::unique_ptr<PhaseI> render_impl(GameState& gs, std::optional<Round>& round, float delta) = 0;

	std::unique_ptr<PhaseI> render(GameState& gs, std::optional<Round>& round, float delta) {
		_timer += delta;
		return render_impl(gs, round, delta);
	}

	virtual bool showPlayerCards(void) const { return true; };
};

struct PhaseCardSelectionHuman : public PhaseI {
	TurnSelection _turn;
	PhaseCardSelectionHuman(const GameState& gs);
	~PhaseCardSelectionHuman(void) override {}

	std::unique_ptr<PhaseI> render_impl(GameState& gs, std::optional<Round>& round, float delta) override;
	bool showPlayerCards(void) const override { return false; };
};

struct PhaseCardSelectionBot : public PhaseI {
	std::default_random_engine _rng{std::random_device{}()};
	const float _fake_time {1.4f + std::uniform_real_distribution<float>{}(_rng) * 2.66f};

	~PhaseCardSelectionBot(void) override {}

	std::unique_ptr<PhaseI> render_impl(GameState& gs, std::optional<Round>& round, float delta) override;
};

// start, redirect to homan/bot
struct PhaseCardSelection : public PhaseI {
	~PhaseCardSelection(void) override {}

	std::unique_ptr<PhaseI> render_impl(GameState& gs, std::optional<Round>& round, float delta) override;
};

// aka pre battle
struct PhaseRevealSelections : public PhaseI {
	~PhaseRevealSelections(void) override {}

	std::unique_ptr<PhaseI> render_impl(GameState& gs, std::optional<Round>& round, float delta) override;
};

// ?
struct PhaseBattle : public PhaseI {
	~PhaseBattle(void) override {}

	std::unique_ptr<PhaseI> render_impl(GameState& gs, std::optional<Round>& round, float delta) override;
};

// aka post battle
struct PhaseBattleEnd : public PhaseI {
	~PhaseBattleEnd(void) override {}

	std::unique_ptr<PhaseI> render_impl(GameState& gs, std::optional<Round>& round, float delta) override;
};

struct PhaseEndScreen : public PhaseI {
	~PhaseEndScreen(void) override {}

	std::unique_ptr<PhaseI> render_impl(GameState& gs, std::optional<Round>& round, float delta) override;
};

