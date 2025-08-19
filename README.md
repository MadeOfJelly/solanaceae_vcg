# solanaceae_vcg

This repository is for a virtual card game (VCG) (as of now unnamed) that is heavily based on the mechanics of Urban Rivals (UR).
It is a 1v1 card game that offers quick matches that are decided by the players' skill and actions rather than by randomness.

The current state of this repo is best to be described as a prototype.
Down the road there is multiplayer, using cryptographically secure [random numbers](https://github.com/Green-Sky/solanaceae_tox_p2prng) and state exchanges.

## Gameplay

### Basic Gameplay rundown

Players chose a deck of 8 different cards each to play.
4 of these cards get drawn to be used in a match.

Alternating, one player will play one of their cards, while the other player then plays of of their cards.
However, the players can invest a limited resource to increase the attack of their cards. The amount of resource used is only revealed, when both players played their cards.

After the stronger cards is decided, effects will play out, depending on the abilities of the cards. (????)

Every card can only be played once per match.
The player that reduces their opponent to 0 Life first wins. Alternatively, the player with more remaining Life after all cards have been played wins.

### Detailed Gameplay rundown

Players chose a deck of 8 different cards each to play.
4 of these cards get drawn to be used in a match.
Every player starts with 12 Potions and 12 Life.
Every dard has a Level, Power, Damage, a Faction Bonus and can have an Ability.
After the Cards are drawn, the player with more total Levels drawn has to play their card first (if the same amount of total Levels is drawn one of the players starts at random).
The starting player plays one of their cards and secretly sets the amounts of Potions their card will be getting and whether or not the card will be getting Focus, which costs 3 Potions and increases the Damage of the card by 2.
The other player will respond by doing the same.
Every card has 1 free Potion, upon which the chosen Potions are added.
Abilities and Faction Bonuses can affect the battle between cards, but also what happens after a battle.
Abilities are either always active or conditional, while a Faction Bonus is only active when at least 2 cards from the same Faction/with the same Faction Bonus are drawn.
Abilities and Factions Bonuses with a "Min" are applied in the order of highest Min to lowest Min.
Attack is calculated by multiplying the Power of the card with the Potions it uses and adding and substracting any additional manipulation results in the Attack of the card.
The card with more Attack wins. If both have the same Attack the card with the lower Level wins. If both also have the same Level, the card that was played first wins.
The winning card substracts its Damage from the opposing player's Life and triggers all Abilities and its Faction Bonus if those trigger on a Win.
The losing card triggers all Abilities and its Faction Bonus if those trigger on a Defeat.
By default, most abilities help in the battle themselves or trigger on a Win.
After that, Heal and Poison apply their effects, if this was not the battle that they were applied in.
Both players then get to see the resulting gamestate, while the player that responded by playing a card has to play first now.
Every card can only be played once.
This repeats until either every card has been played or one of the players is reduced to 0 Life.
The player that reduces their opponent to 0 Life first wins. Alternatively, the player with more remaining Life after all cards have been played wins.
If both players get reduced to 0 Life in the same turn, it is a draw. Additionally, if both players have the same amount of Life after all cards have been played, the match is also a draw.

## Glossary

|                      |                     |
|----------------------|---------------------|
| - X Opp Attack Min Y | During the Battle, the opponents Attack is reduced by X down to a minimum of Y. |
| - X Opp Damage Min Y | During the Battle, the opponents Damage is reduced by X down to a minimum of Y. |
| - X Opp Life Min Y   | After the Battle, the enemies' Lives are reduced by X down to a minimum of Y after the Damage is applied. |
| - X Opp Potion Min Y | After the Battle, the enemies' Potions are reduced by X down to a minimum of Y. |
| - X Opp Power Min Y  | During the Battle, the opponents Power is reduced by X down to a minimum of Y. |
| + X Life             | When this Card wins you get X Life. |
| + X Life per Damage  | If this Card wins the Battle, you gain Lives equal to X-times the Damage the Card dealt. |
| + X Potion           | When this Card wins you get X Potion. |
| Ability              | Every Card can have an Ability that grants the Card bonuses during or after Battles. |
| Attack (Att)         | By multiplying the Power of the Card with the Potions it uses and adding and substracting any additional manipulation results in the Attack of the Card. In general, the Card with more Attack wins the Battle. |
| Backlash: XYZ        | A Backlash Ability triggers upon winning a Battle with the Card. You yourself are affected by this Ability and not your enemy. |
| Battle               | A Battle is when 2 Cards are fighting against each other. The Card with more Attack wins. If both have the same Attack the Card with the lower Level wins. If both also have the same Level, the Card that was played first wins. |
| Cards                | Cards are what is used to determine who wins the game. Every Card has a Level, Power, Damage, a Faction Bonus and can have an Ability. |
| Courage              | An Ability with Courage gets activated when the Card gets played first for a Battle. |
| Damage (Dmg)         | The amount of Life that is substracted from the enemy if your card wins its Battle. |
| Damage = Opp Damage  | The Damage of this Card is equal to the base Damage of the opposing Card. |
| Deck                 | Each player's Deck consists of 8 different cards, 4 of which are drawn at the beginning of a match. |
| Defeat: XYZ          | The effect triggers when this Card loses the batte. |
| Faction              | Different Factions have different Cards and can be used with each other to unlock their Faction Bonus. |
| Faction Bonus        | A Faction Bonus is activated when you have at least 2 Cards of the same Faction drawn. |
| Focus                | A player can use 3 Potions to increase the Damage of his Card by 2 instead of using them to increase the Cards Attack. |
| Heal X Max Y         | If this Card wins the Battle, you regain X Lives after each of the following Battles up to a maximum of Y. Between multiple Heals, only the strongest is applied, unless another Heal would heal more Lives due to the maximum of Y. Heal always acts before Poison. |
| Life                 | Each player starts each Match with 12 Life by default. The Player that reduces the other player's Life to 0 or has more Life after every card was played wins the Match. |
| Poison X Min Y       | If this Card wins the Battle, the enemy takes X damage after each of the following Battles down to a minimum of Y. Between multiple poisons, only the strongest is applied, unless another poison would deal more damage due to the minimum of Y. Poison always acts after Heal. |
| Potions (Pots)       | The amount of Potions put to a Card are multiplied with its Power to determine its Attack before manipulation. Every Card has 1 Potion by default. Each player starts each Match with 12 Potions. |
| Power (Pwr)          | The amount of Power is multiplied by a Card's Potions to determine its Attack before manipulation. |
| Power = Opp Power    | The Power of this Card is equal to the base Power of the opposing Card. |
| Recover 1 of 2 Potion | After the Battle, you recover 50% of the Potions the Card had, rounded up. This includes the Potion it has by default. |
| Revenge: XYZ         | This Ability activates when one of your Cards lost the last Battle. |
| Support: XYZ         | Supporter abilities are applied to all of your Cards on every Battle. |
| Steal X Y Min Z      | Removes X of Y down to a minimum of Z from the enemy and gives you the amount that was removed. |
| Stop Opp Ability     | The opponent's Card's Ability is ignored. |
| Stop Opp Bonus       | The opponent's Card's Faction Bonus is ignored. |
| Stop: XYZ            | This Ability activates when the opposing Card possesses "Stop Opp Ability". |
| Team: XYZ            | A Support ability increases in strength for each member of the Faction drawn. |


## Authors

Game Design by Bankraeuber

Programming by https://github.com/Green-Sky

