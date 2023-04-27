#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "subsetSumBrute.h"
#include "subsetSumGreedy.h"
#include <chrono>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include "baseConversions.h"

using namespace std;

void vcToSs(string file, vector<long long int> &included) {
    ifstream f;
    f.open(file);

    // if file can't be opened
    if (!f.is_open()) { 
        cout << "File cannot be opened." << endl;
        return;
    }

    string line;
    getline(f, line);
    stringstream s(line);
    int k; // holds the number of min vertex cover
    int numNodes;
    s >> numNodes >> k;
    int firstNum;
    int secondNum;
    int numEdges = 0;

    vector<pair<int, int>> edges; // holds pairs of edges

    while (getline(f, line) && line != "$") {
        if (line[0] == '$') break;
        stringstream ss(line);
        ss >> firstNum >> secondNum;
        edges.push_back(make_pair(firstNum, secondNum));
        numEdges++;
    }

    int n = numNodes;
    int m = edges.size();
    vector<vector<int>> bits((n + m), vector<int>(m + 1));

    // Initialize each integer's first digit to 1; init other digits to 1 if they have an edge
    for (int i = 0; i < n; i++) {
        bits[i][0] = 1;
        for (int j = 0; j < m; j++) {
                if (edges[j].first == i || edges[j].second == i) {
                    bits[i][j+1] = 1;
                }
        }
    }

    // edges
    int offset = 1;
    for (int i = n; i < m+n; i++) {
        bits[i][0] = 0;
        bits[i][offset] = 1;
        offset++;
    }

    // find target sum
    int targetSum = 0;
    for (int i = 0; i <= m-1; i++) {
        targetSum += 2 * pow(4,i);
    }
    targetSum += k * pow(4, m);

    // convert integers above to ints
    vector<long long int> nums;
    for (size_t i = 0; i < bits.size(); i++) {
        string num_str = "";
        for (size_t j = 0; j < bits[i].size(); j++) {
            num_str += to_string(bits[i][j]);
        }
        nums.push_back(stol(num_str));
    }

    // convert to base 10
    for (size_t i = 0; i < nums.size(); i++) {
        nums[i] = base10(nums[i]);
    }

    // subset sum brute
    auto start = chrono::high_resolution_clock::now();
    bool result = subsetSumBrute(nums, nums.size(), targetSum, included, true);
    auto stop = chrono::high_resolution_clock::now();
    auto bruteDuration = chrono::duration_cast<std::chrono::microseconds>(stop - start);

    if (result) {
        cout << "Subset sum using brute force found with sum = " << targetSum << " and k = " << k << endl;
        cout << "Time: " << bruteDuration.count() << " microseconds" << endl;
    }
    else {
        cout << "No subset sum found using brute force with sum = " << targetSum << endl;
    }
    included.clear();

    // subset sum greedy
    start = chrono::high_resolution_clock::now();
    result = subsetSumGreedy(nums, nums.size(), targetSum, included);
    stop = chrono::high_resolution_clock::now();
    auto greedyDuration = chrono::duration_cast<std::chrono::microseconds>(stop - start);
    if (result) {
        cout << "Subset sum using greedy algorithm found with sum = " << targetSum << " and k = " << k <<  endl;
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
        cout << "No subset sum found using greedy algorithm with sum = " << targetSum << endl;
        cout << "Time: " << greedyDuration.count() << " microseconds" << endl;
    }    
    f.close();
}