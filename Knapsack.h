#ifndef KNAPSACK_KNAPSACK_H
#define KNAPSACK_KNAPSACK_H

#include <iostream>
#include <string.h>
#include <vector>
#include <math.h>
#include "Card.h"

//consider renaming class to Crapsack
class Knapsack
{
    private: 
        int capacity;
        int num_cards;
        Card** card_list;
        int curr_index;
        int max_profit;
        std::vector<Card*> best;
        std::vector<Card*> include;
        /*
        int* curr_row;
        int* next_row;
        */

    public:
        Knapsack(int c, int n);
        int get_capacity();
        int get_num_cards();
        Card** get_card_list();
        std::vector<Card*> get_best();
        std::vector<Card*> get_include();
        int get_max_profit();
        void add_card_to_list(Card* new_card);
        void print_card_list();
        void print_card_list2();
        void quick_sort(Card** cards, int start, int last);
        int partition(Card** cards, int start, int last);
        int random_partition(Card** cards, int start, int last);
        void swap(Card** cards, int index1, int index2);
        void greedy();
        void better_greedy();
        void backtracking(int curr, int profit, int weight);
        bool is_promising(int weight_so_far, float upper_bound);
        float fractional_knapsack(int start, int curr_weight, int curr_profit);
        //float updated_upper_bound(Node my_node, int start_index);
        void dynamic_knapsack();
};

#endif
