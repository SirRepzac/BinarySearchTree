#include <iostream>
#include "BSTTree.h"
#include "BSTTreeUnbalanced.h"
#include <chrono>
#include <algorithm>
#include <random>


using namespace std::chrono;
using namespace std;
int x = 100000;
int cycle_test = 1000;

int main()
{
    double total_time = 0;
    BSTTree t = BSTTree();
    vector<int> values;

    srand(time(NULL));

    for (int i = 0; i < x; i++)
    {
        int random = rand() % x;
        values.push_back(random);
    }

    for (unsigned z = 0; z < cycle_test; ++z) {

        t.DeleteTree();
      
        auto start = high_resolution_clock::now();
        for (unsigned i = 0; i < x; ++i)
        {
            int p = values[i];
            t.Insert(p);
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        total_time += duration.count();
    }

    cout << "Average time (balanced): " << (total_time / cycle_test) / 1'000'000 << " seconds" << endl;

    total_time = 0;
    BSTTreeUnbalanced u = BSTTreeUnbalanced();

    for (unsigned z = 0; z < cycle_test; ++z)
    {

        u.DeleteTree();

        auto start = high_resolution_clock::now();
        for (unsigned i = 0; i < x; ++i)
        {
            int p = values[i];
            u.Insert(p);
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        total_time += duration.count();
    }

    cout << "Average time (unbalanced): " << (total_time / cycle_test) / 1'000'000 << " seconds" << endl;
}
