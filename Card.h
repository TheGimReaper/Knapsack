#ifndef KNAPSACK_CARD_H
#define KNAPSACK_CARD_H

#include <iostream>
#include <string.h>

class Card
{
    private:
		int market_price;
		int cost;
	public:
        Card();
		Card(int m, int c);
        int get_market_price();
        int get_cost();
        float price_by_weight();		
};


#endif
