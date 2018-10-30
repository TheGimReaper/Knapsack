#include <fstream>
#include "Knapsack.h"
#include <ctime>
#include <unistd.h>
#include <chrono>
#include <cmath>

using namespace std;
int main(int argc, char** argv)
{
    ifstream input(argv[1]);
    ofstream output(argv[2]);
    string mode = argv[3];
    int num_items, capacity;
    while(input >> num_items >> capacity)
    {
        clock_t start, end;
		start = clock();
        //cout << start << endl;
        Knapsack sack(capacity, num_items);
        int weight, profit;
        for (int i = 0; i < num_items; i++)
        {
            input >> weight >> profit;
            Card *new_card = new Card(profit, weight);
            sack.add_card_to_list(new_card);
        }
        vector<Card*> include;
        output << num_items << " ";
        //sack.print_card_list2();
        sack.quick_sort(sack.get_card_list(), 0, sack.get_num_cards() - 1);
        //sack.print_card_list();
        //sack.print_card_list2();
        if (mode == "0") sack.greedy();
        else sack.better_greedy();
        if (mode == "2") sack.backtracking(0, 0, 0);
        /*
        for (int i = 0; i < 20000; i++)
        {
            for (int j = 0; j < 20000; j++)
            {
                int k = i * j;
            }
        }
        */
        output << sack.get_max_profit() << " ";
        end = clock();
        //cout << CLOCKS_PER_SEC << endl;
        //cout << end << endl;
        //cout << start << endl;
        double duration = (double) (end - start) * 1000.0/ (CLOCKS_PER_SEC);
        //duration =  ((double) (end - start)/(double) (CLOCKS_PER_SEC));
		output << duration << "\n";
    }
    input.close();
    output.close();
    return 0;
}