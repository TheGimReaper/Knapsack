#include "Card.h"

using namespace std;

Card::Card()
{
    cost = -1;
    market_price = -1;
}

Card::Card(int m, int c)
{
    market_price = m;
    cost = c;
}

int Card::get_market_price()
{
    return market_price;
}

int Card::get_cost()
{
    return cost;
}

float Card::price_by_weight()
{
    return (float) market_price/cost;
}