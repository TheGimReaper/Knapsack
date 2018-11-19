#include "Knapsack.h"

using namespace std;

Knapsack::Knapsack(int c, int n)
{
    capacity = c;
    num_cards = n;
    card_list = new Card*[n];
    curr_index = 0;
    max_profit = 0; 
    /*
    curr_row = new int[c];
    next_row = new int[c];
    */
}

int Knapsack::get_capacity()
{
    return capacity;
}

int Knapsack::get_num_cards()
{
    return num_cards;
}

Card** Knapsack::get_card_list()
{
    return card_list;
}

vector<Card*> Knapsack::get_best()
{
    return best;
}

vector<Card*> Knapsack::get_include()
{
    return include;
}

int Knapsack::get_max_profit()
{
    return max_profit;
}

void Knapsack::add_card_to_list(Card* new_card)
{
    if (curr_index <= num_cards) card_list[curr_index++] = new_card;   
}

void Knapsack::print_card_list()
{
    for (int i = 0; i < curr_index; i++) cout << card_list[i]->get_cost() << ", " << card_list[i]->get_market_price() << "; ";
    cout << endl;
}

void Knapsack::print_card_list2()
{
    for (int i = 0; i < curr_index; i++) cout << (float) card_list[i]->get_market_price()/card_list[i]->get_cost() << "; ";
    cout << endl;
}

void Knapsack::quick_sort(Card** cards, int first, int last)
{
    if (first < last)
    {
        int q = partition(cards, first, last);
        //int q = random_partition(cards, first, last);
        quick_sort(cards, first, q - 1);
        //if (q + 1 <=  last)
        quick_sort(cards, q + 1, last);
    }
}

int Knapsack::partition(Card** cards, int first, int last)
{
    //if (first == last) return first;
    int i = first - 1;
    for (int j = first; j < last; j++)
    {
        if (cards[j]->price_by_weight() > cards[last]->price_by_weight()  
        
        || (cards[j]->price_by_weight() == cards[last]->price_by_weight() 
        && cards[j]->get_market_price() > cards[last]->get_market_price()))
        
        {
            swap(card_list, ++i, j);
        }
    }
    swap(card_list, i + 1, last);
    return i + 1;
}

void Knapsack::swap(Card** cards, int index1, int index2)
{
    Card* temp = card_list[index1];
    card_list[index1] = card_list[index2];
    card_list[index2] = temp;
}

//assumes num_cards is sorted
void Knapsack::greedy()
{
    vector<Card*> ret;
    int curr_weight = 0;
    int profit = 0;
    for (int i = 0; i < num_cards; i++) 
    {
        if (curr_weight + card_list[i]->get_cost() <= capacity)
        {
            ret.push_back(card_list[i]);
            curr_weight += card_list[i]->get_cost();
            profit += card_list[i]->get_market_price();
        }
    }   
    max_profit = profit;
    best = ret;
}

void Knapsack::better_greedy()
{
    vector<Card*> ret;
    int curr_weight = 0;
    Card* max = card_list[0];
    for (int i = 0; i < num_cards; i++)
    {
        if (curr_weight + card_list[i]->get_cost() <= capacity)
        {
            ret.push_back(card_list[i]);
            curr_weight += card_list[i]->get_cost();
            max_profit += card_list[i]->get_market_price();
        }
        else
        {
            if (card_list[i]->get_market_price() > max->get_market_price() && card_list[i]->get_cost() <= capacity)
                max = card_list[i];
        }
    }
    if (max_profit < max->get_market_price() && max->get_cost() <= capacity)
    {
        ret.clear();
        ret.push_back(max);
        max_profit = max->get_market_price();
    }
    best = ret;
}

/**
 * First node: WSF = 0, Profit = 0, Upperbound = TPL = fractional knapsack
 * If node is promising, expand. Else, prune
 * Need to store best combination
**/
void Knapsack::backtracking(int curr, int profit, int weight)
{
    if (weight <= capacity && profit > max_profit)
    {
        max_profit = profit;
        best = include;
    }
    if (curr < num_cards && is_promising(weight, fractional_knapsack(curr, weight, profit)))
    {
        include.push_back(card_list[curr]);
        backtracking(curr + 1, profit + card_list[curr]->get_market_price(), weight + card_list[curr]->get_cost());
        include.pop_back();
        backtracking(curr + 1, profit, weight);
    }
}

bool Knapsack::is_promising(int weight_so_far, float upper_bound)
{
    return (weight_so_far < capacity && max_profit < upper_bound);
}

// Assumes cards are in nondescending order
float Knapsack::fractional_knapsack(int start, int curr_weight, int curr_profit)
{
    float total_profit = curr_profit;
    int total_weight = curr_weight;
    for (int i = start; i < num_cards && total_weight < capacity; i++)
    {
        if (total_weight + card_list[i]->get_cost() < capacity) 
        {
            total_profit += card_list[i]->get_market_price();
            total_weight += card_list[i]->get_cost();
        }
        else
        {
            total_profit += card_list[i]->get_market_price() * ((capacity - total_weight)/ (float) card_list[i]->get_cost());
            total_weight = capacity;
        }
    }
    //cout << total_profit << endl;
    return total_profit;
}

// *** DYNAMIC PROGRAMMING CODE STARTS HERE *** 

void Knapsack::dynamic_knapsack()
{
    int* curr = new int[capacity + 1];
    int* prev = new int[capacity + 1];
    for (int i = 0; i < capacity + 1; i++) prev[i] = 0;
    for (int item = 0; item < num_cards + 1; item++)
    {
        Card* my_card = card_list[item - 1];
        for (int weight = 0; weight <= capacity; weight++)
        {
            if (item == 0 || weight == 0) curr[weight] = 0;
            else if (my_card->get_cost() > weight) curr[weight] = prev[weight];
            else curr[weight] = max((prev[weight - my_card->get_cost()] + my_card->get_market_price()), prev[weight]);    
        }
        for (int i = 0; i < capacity + 1; i++) prev[i] = curr[i];
        max_profit = curr[capacity];
    }
}

