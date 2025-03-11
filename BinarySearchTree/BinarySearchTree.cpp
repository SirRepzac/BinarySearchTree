#include <iostream>
#include "BSTTree.h"
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

    //std::mt19937 rng(std::random_device{}());
    //std::uniform_int_distribution<int> dist(0, 999);
    //auto generateRandom = [&]() -> int { return dist(rng); };
    for (unsigned z = 0; z < cycle_test; ++z) {

        t.DeleteTree();
        t;
      
        //generate(values.begin(), values.end(), generateRandom);
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
    t.ToString();
    cout << "Average time: " << (total_time / cycle_test) / 1'000'000 << " seconds" << endl;
}

//TODO: Fix tree!