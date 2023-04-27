#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "subsetSumBrute.h"
#include "subsetSumGreedy.h"
#include <chrono>
#include <tuple>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cmath>
#include "baseConversions.h"

using namespace std;

void satToSs(vector<tuple<int, int, int>> clauses, int numVars) {
    int numClauses = clauses.size();

    vector<vector<int>> bits((numVars + numClauses)*2, vector<int>(numClauses + numVars)); // matrix

    // each var has two rows: 1 for if true, 1 for if false
    for (int i = 0; i < numVars * 2; i++) {
        int col_index = i / 2;
        bits[i][col_index] = 1;
    }

    // each clause also has 1s or 0s
    for (int i = numVars * 2; i < (numVars + numClauses) * 2; i++) {
        int col_index = i / 2;
        bits[i][col_index] = 1;
    }

    // fill rows with 1s
    for (int i = 0; i < numClauses; i++) {
        auto& clause = clauses[i];
        for (int j = 0; j < 3; j++) {
            int val;
            int row;
            switch (j) {
                case 0:
                    val = get<0>(clause);
                    if (val == 1) row = 0;
                    else {
                        row = (abs(val) * 2) - 2;
                        if (val < 0) row++;
                    }
                    bits[row][numVars + i] = 1;
                    break;
                case 1:
                    val = get<1>(clause);
                    if (val == 1) row = 0;
                    else {
                        row = (abs(val) * 2) - 2;
                        if (val < 0) row++;
                    }
                    bits[row][numVars + i] = 1;
                    break;
                case 2:
                    val = get<2>(clause);
                    if (val == 1) row = 0;
                    else {
                        row = (abs(val) * 2) - 2;
                        if (val < 0) row++;
                    }
                    bits[row][numVars + i] = 1;
                    break;
            }
        }
    }
    string total; // will be a 1 for each var, 3 for each clause (ex. 11133)
    for (int i = 0; i < numVars; i++) {
        total += "1";
    }
    for (int i = 0; i < numClauses; i++) {
        total += "3";
    }

    long long int sum;
    sum = stoll(total); 

    vector<long long int> nums; // holds the nums when converted from bits
    for (size_t i = 0; i < bits.size(); i++) {
        string num_str = "";
        for (size_t j = 0; j < bits[i].size(); j++) {
            num_str += to_string(bits[i][j]);
        }
        if (num_str.length() <= 9) {
            nums.push_back(stoi(num_str));
        }
        else  {
            nums.push_back(stol(num_str));
        }
        
    }
    // convert to base 10
    for (size_t i = 0; i < nums.size(); i++) {
        nums[i] = base10(nums[i]);
    }
    sum = base10(sum);

    // subset sum - brute
    auto start = chrono::high_resolution_clock::now();
    vector<long long int> included;
    bool result = subsetSumBrute(nums, nums.size(), sum, included);
    auto stop = chrono::high_resolution_clock::now();
    auto bruteDuration = chrono::duration_cast<std::chrono::microseconds>(stop - start);
    if (result) {
        cout << "Subset sum using brute force found with sum = " << sum << endl;
        cout << "Time: " << bruteDuration.count() << " microseconds" << endl;
    }
    else {
        cout << "No subset sum found using brute force with sum = " << sum << endl;
    }

    included.clear();

    // subset sum greedy
    start = chrono::high_resolution_clock::now();
    result = subsetSumGreedy(nums, nums.size(), sum, included);
    stop = chrono::high_resolution_clock::now();
    auto greedyDuration = chrono::duration_cast<std::chrono::microseconds>(stop - start);
    if (result) {
        cout << "Subset sum using greedy algorithm found with sum = " << sum << endl;
        cout << "Time: " << greedyDuration.count() << " microseconds" << endl;
        int total = 0;
        for (auto it = included.begin(); it != included.end(); ++it) {
            total+=*it;
        }
        cout << total << endl;
        if (greedyDuration.count() < bruteDuration.count()) {
            float diff = bruteDuration.count() - greedyDuration.count();
            int ratio = bruteDuration.count() / greedyDuration.count();
            if (diff > 1000000) {
                diff = diff / 1000000.00;
                cout << "The greedy algorithm is " << diff << " seconds faster, or " << fixed << setprecision(2) << ratio << "x faster." << endl;
            }
            else {
                cout << "The greedy algorithm is " << diff << " microseconds faster, or " << fixed << setprecision(2) << ratio << "x faster." << endl;
            }
        }
    }

    else {
        cout << "No subset sum found using greedy algorithm with sum = " << sum << endl;
        cout << "Time: " << greedyDuration.count() << " microseconds" << endl;
    }    

}