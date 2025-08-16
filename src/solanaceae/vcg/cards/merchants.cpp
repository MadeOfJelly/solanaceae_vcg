#include "./merchants.hpp"

std::vector<Card> Cards::merchants(void) {
	return {
		{"Jewelry Merchant",4,6,5,{"- 12 Opp Attack Min 12"},{"+ 8 Attack"},"The Jewelry Merchant is popular with the nobles, but also common folk regularly browse his wares, if only to dream of what they could buy if they had the money. Rings, amulets, piercings, the Jewelry Merchant has it all"},
		{"Aspiring Merchant",2,7,1,{"- 2 Opp Damage Min 1"},{"+ 8 Attack"},"The Aspiring Merchant can be found with the other Merchants, learning as much as he can while trying to find his way."},
		{"Shipping Merchant",3,5,5,{"- 3 Opp Damage Min 3"},{"+ 8 Attack"},"The Shipping Merchant deals with all kinds of goods, though they must come from overseas."},
		{"Monopoly Keeper",5,7,6,{"- 3 Opp Power Min 5"},{"+ 8 Attack"},"The Monopoly Keeper once got his hands on special goods, of which he is now the only vendor. Anyone who tries to enter his market mysteriously disappears."},
		{"Food Merchant",2,5,3,{"+ 2 Life"},{"+ 8 Attack"},"The Food Merchant is not seeing much money in the recent months, but he has steady buyers and will never be without customers."},
		{"Vendor",2,6,2,{"+ 2 Potion"},{"+ 8 Attack"},"The Vendor is a simply worker that sells goods and can be seen at market stalls."},
		{"Ore Merchant",3,5,5,{"+ 2 Power"},{"+ 8 Attack"},"The Ore Merchant is a baseline Merchant for many others, as he handles the delivery of the raw material needed to make their goods."},
		{"Herb Merchant",3,7,2,{"+ 3 Potion"},{"+ 8 Attack"},"The Herb Merchant sells all kinds of herbs that can be used to enhance the flavor of food, brew tea, or even smell good when burned."},
		{"Potion Merchant",5,7,5,{"+ 4 Potion"},{"+ 8 Attack"},"The Potion Merchant might not understand much in terms of alchemy, but he knows how to store and how to sell potions."},
		{"Weapon Merchant",4,7,5,{"+ 8 Attack"},{"+ 8 Attack"},"The Weapon Merchant has everything in stock to beat down a variable number of people. Swords, axes, bows, catapults, cannons, there is no weapon he can't procure."},
		{"Paid Guard",3,8,4,{"Backlash: - 3 Potion Min 0"},{"+ 8 Attack"},"The Paid Guard stands watch near the stall or the caravan of the Merchant, keeping uninvited fingers away from the goods."},
		{"Luxury Goods Merchant",4,5,7,{"Courage: + 12 Attack"},{"+ 8 Attack"},"The Luxury Goods Merchant is especially popular with nobles. He sells all kinds of gems, rare spices and animals and can set up deliveries or rare materials from all over the world."},
		{"Fake Merchant",2,6,2,{"Defeat: - 2 Opp Potion Min 4"},{"+ 8 Attack"},"The Fake Merchant is selling fake goods and will never appear at the same place twice. Additionally, he is always disguised when praising his excellent wares."},
		{"Remedy Merchant",3,6,3,{"Heal 2 Max 13"},{"+ 8 Attack"},"The Remedy Merchant has all kinds of balms and creams in stock that easy pain."},
		{"Envious Merchant",4,6,6,{"Revenge: - 3 Opp Damage Min 1"},{"+ 8 Attack"},"The Envious Merchant is doing good in life, quite good actually. However, he strives for more and is envious of everyone who is having more sales, if only once."},
		{"Supply Chain Puppeteer",5,7,6,{"Steal 2 Potion Min 5"},{"+ 8 Attack"},"The Supply Chain Puppeteer is the master of caravans, warehouses and pricing. He knows which goods go where and which route they take."},
		{"Auctioneer",3,5,5,{"Stop Opp Ability"},{"+ 8 Attack"},"The Auctioneer can be seen on the market place, screaming at the top of his lungs. He is trying to raise the best price for a product, though he might simply not hear you when he doesn't like you."},
		{"Supplier",3,6,4,{"Stop Opp Bonus"},{"+ 8 Attack"},"The Supplier is there for every Merchant and knows who needs what and when. He makes sure everyone gets their crates and packages."},
		{"Guild Leader",5,5,8,{"Team: - 4 Opp Attack Min 12"},{"+ 8 Attack"},"The Guild Leader is the leader of the Merchants, at least on paper. He has many connections and will use them to keep his position of power."},
	};
}
