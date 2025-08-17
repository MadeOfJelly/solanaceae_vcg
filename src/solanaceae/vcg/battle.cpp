#include "./battle.hpp"

#include "./do_ability.hpp"

bool battle(GameState& gs, Round& round) {
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

	return true;
}

