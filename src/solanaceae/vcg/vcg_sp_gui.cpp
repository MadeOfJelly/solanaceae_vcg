#include "./vcg_sp_gui.hpp"

#include "./card.hpp"
#include "./game_state.hpp"

#include "./sp_gui_states.hpp"

#include "./cards/predefined_decks.hpp"
#include "./cards/easy_cards.hpp"
#include "./cards/random.hpp"
#include "./cards/aberrations.hpp"
#include "./cards/assassins.hpp"
#include "./cards/bandits.hpp"
#include "./cards/clerics.hpp"
#include "./cards/crafters.hpp"
#include "./cards/cultists.hpp"
#include "./cards/farmers.hpp"
#include "./cards/invaders.hpp"
#include "./cards/junkies.hpp"
#include "./cards/mages.hpp"
#include "./cards/merchants.hpp"
#include "./cards/monsters.hpp"
#include "./cards/nobles.hpp"
#include "./cards/parasites.hpp"
#include "./cards/thieves.hpp"

#include <imgui.h>

#include <memory>
#include <random>
#include <optional>

// TODO: refactor
template<typename RNG>
static std::vector<Card> drawCards(RNG& rng, const std::vector<Card>& full_deck) {
	// TODO: avoid extra copy
	std::vector<Card> subset = full_deck;
	while (subset.size() > 4) {
		size_t to_remove_idx = rng()%subset.size();
		subset.erase(subset.cbegin() + to_remove_idx);
	}
	return subset;
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

struct CurrentGame {
	GameState game_state;
	std::optional<Round> round;
	std::unique_ptr<PhaseI> phase;

	CurrentGame(GameState&& _game_state) : game_state(_game_state) {}
};

VCGSPGUI::VCGSPGUI(void) {
	//_game = std::make_unique<CurrentGame>();
}

VCGSPGUI::~VCGSPGUI(void) {
}

float VCGSPGUI::render(float delta) {
	if (ImGui::Begin("VCG sp")) {
		struct Deck {
			const char* name;
			decltype(Cards::monsters_deck1)& get_deck;
		};
		static const std::vector<Deck> decks{
			Deck{"monster1", Cards::monsters_deck1},
			Deck{"monsters+clerics1", Cards::monsters_clerics_deck1},
			Deck{"clerics+junkies1", Cards::clerics_junkies_deck1},
			Deck{"aberrations+parasites1", Cards::aberrations_parasites_deck1},

			Deck{"full aberrations faction", Cards::aberrations},
			Deck{"full assassins faction", Cards::assassins},
			Deck{"full bandits faction", Cards::bandits},
			Deck{"full clerics faction", Cards::clerics},
			Deck{"full crafters faction", Cards::crafters},
			Deck{"full cultists faction", Cards::cultists},
			Deck{"full easy_cards faction", Cards::easy_cards},
			Deck{"full farmers faction", Cards::farmers},
			Deck{"full invaders faction", Cards::invaders},
			Deck{"full junkies faction", Cards::junkies},
			Deck{"full mages faction", Cards::mages},
			Deck{"full merchants faction", Cards::merchants},
			Deck{"full monsters faction", Cards::monsters},
			Deck{"full nobles faction", Cards::nobles},
			Deck{"full parasites faction", Cards::parasites},
			Deck{"full thieves faction", Cards::thieves},

			Deck{"dev (ignore)", Cards::random},
		};
		static int deck_selection {0};
		if (ImGui::Button("new game")) {
			const std::vector<Card> cards = decks.at(deck_selection).get_deck();

			std::default_random_engine rng{std::random_device{}()};

			_game = std::make_unique<CurrentGame>(
				GameState(
					drawCards(rng, cards),
					drawCards(rng, cards)
				)
			);
			_game->game_state.determineStartingPlayer(rng);

			_game->phase = std::make_unique<PhaseCardSelection>();
		}

		ImGui::SameLine();
		{
			//ImGui::Combo("select your deck", &deck_selection, decks);
			ImGui::Combo(
				"select deck",
				&deck_selection,
				+[](void* ctx, int i){ return reinterpret_cast<const decltype(decks)*>(ctx)->at(i).name; },
				(void*)&decks,
				decks.size()
			);
		}

		if (_game) {
			ImGui::Separator();
			auto& gs = _game->game_state;

			// player is player 0
			// bot is player 1
			ImGui::Text("starting player: %zu (%s)", gs.starting_player, gs.starting_player == 0 ? "human" : "bot");

			if (ImGui::CollapsingHeader("details")) {
				const auto str = gs.toString();
				ImGui::TextWrapped("%s", str.c_str());
			}

			const size_t human_rindex = _game->round->players.at(0) == 0 ? 0 : 1;
			const size_t bot_rindex = _game->round->players.at(0) == 0 ? 1 : 0;
			const bool can_show_human_selection = _game->round->turns.size() == 2 || (_game->round->turns.size() == 1 && human_rindex == 0);
			const bool can_show_bot_selection = _game->round->turns.size() == 2 || (_game->round->turns.size() == 1 && bot_rindex == 0);

			ImGui::Text("Bot Pots:%d Life:%d cards:", gs.vols.at(1).pots, gs.vols.at(1).life);
			ImGui::Indent();
			ImGui::PushID(1); // bot
			for (size_t i = 0; i < gs.cards.at(1).size(); i++) {
				const auto label = gs.cards.at(1).at(i).toStringNLPD();
				const bool used = gs.cards_used.at(1).at(i);
				if (used) {
					ImGui::TextDisabled("%s", label.c_str());
				} else if (can_show_bot_selection && i == _game->round->turns.at(bot_rindex).card_idx) {
					ImGui::Selectable(label.c_str(), true, ImGuiSelectableFlags_Disabled);
				} else {
					ImGui::TextUnformatted(label.c_str());
				}
				cardHoverDetails(gs.cards.at(1).at(i));
			}
			ImGui::PopID();
			ImGui::Unindent();

			// bot flavor text here?
			//_game->phase->

			ImGui::Text("Your Pots:%d Life:%d cards:", gs.vols.at(0).pots, gs.vols.at(0).life);
			if (_game->phase->showPlayerCards()) {
				// TODO: toggle render, or inject selectable?
				ImGui::Indent();
				for (size_t i = 0; i < gs.cards.at(0).size(); i++) {
					const auto label = gs.cards.at(0).at(i).toStringNLPD();
					const bool used = gs.cards_used.at(0).at(i);
					if (used) {
						ImGui::TextDisabled("%s", label.c_str());
					} else if (can_show_human_selection && i == _game->round->turns.at(human_rindex).card_idx) {
						ImGui::Selectable(label.c_str(), true, ImGuiSelectableFlags_Disabled);
					} else {
						ImGui::TextUnformatted(label.c_str());
					}
					cardHoverDetails(gs.cards.at(0).at(i));
				}
				ImGui::Unindent();
			}

			// phases?
			// a round gets constructed from both players selections

			// get current phase ?
			// if card selection
			// 	- if bot -> do ai
			// 	- if player -> show handcards and make clickable
			// 	both end selection and either end general card selection or next player selects cards
			// if card selection over -> reveal and show battle
			// if battle -> end battle
			// if end battle
			//  - if end game cond -> end screen
			//  - else card selection


			auto new_phase = _game->phase->render(gs, _game->round, delta);
			if (new_phase) {
				_game->phase = std::move(new_phase);
			}
		}
	}
	ImGui::End();

	return 2.f;
}


