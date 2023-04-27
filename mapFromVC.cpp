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

struct Graph {
    int numNodes;
    vector<vector<int>> edges;
};

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
    Graph g;
    stringstream s(line);
    int k;
    s >> g.numNodes >> k;
    // g.numNodes = stoi(line); // set sum equal to the first line
    g.edges.resize(g.numNodes);
    for (int i = 0; i < g.numNodes; i++) {
        g.edges[i].resize(0);
    }
    int firstNum;
    int secondNum;
    int numEdges = 0;
    vector<pair<int, int>> edges;
    while (getline(f, line) && line != "$") {
        stringstream ss(line);
        ss >> firstNum >> secondNum;
        g.edges[firstNum].push_back(secondNum);
        g.edges[secondNum].push_back(firstNum);
        edges.push_back(make_pair(firstNum, secondNum));
        numEdges++;
    }

    // for (int i = 0; i < edges.size(); i++) {
    //     cout << "(" << edges[i].first << ", " << edges[i].second << ")" << endl;
    // }

    int n = g.numNodes;
    int m = edges.size();
    vector<vector<int>> bits((n + m), vector<int>(m + 1));

    for (int i = 0; i < n; i++) {
        bits[i][0] = 1;
        for (int j = 0; j < m; j++) {
                if (edges[j].first == i || edges[j].second == i) {
                    bits[i][j+1] = 1;
                }
        }
    }

    int offset = 1;
    for (int i = n; i < m+n; i++) {
        bits[i][0] = 0;
        bits[i][offset] = 1;
        offset++;
    }

    // for (int i = 0; i < (n + m); i++) {
    //     for (int j = 0; j < m+1; j++) {
    //         std::cout << bits[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    int targetSum = 0;
    for (int i = 0; i <= m-1; i++) {
        targetSum += 2 * pow(4,i);
    }
    targetSum += k * pow(4, m);
    // cout << targetSum << endl;
    vector<long long int> nums;
    for (size_t i = 0; i < bits.size(); i++) {
        string num_str = "";
        for (size_t j = 0; j < bits[i].size(); j++) {
            num_str += to_string(bits[i][j]);
        }
        nums.push_back(stol(num_str));
    }
    for (size_t i = 0; i < nums.size(); i++) {
        nums[i] = base10(nums[i]);
    }

    auto start = chrono::high_resolution_clock::now();
    bool result = subsetSumBrute(nums, nums.size(), targetSum, included, true);
    auto stop = chrono::high_resolution_clock::now();
    auto bruteDuration = chrono::duration_cast<std::chrono::microseconds>(stop - start);

    if (result) {
        cout << "Subset sum using brute force found with sum = " << targetSum << " and k = " << k << endl;
        cout << "Time: " << bruteDuration.count() << " microseconds" << endl;
        // cout << "[ ";
        // for (int x : included) {
        //     x = base4(x);
        //     cout << x << ' ';
        // }
        // cout << "]" << endl;
    }
    else {
        cout << "No subset sum found using brute force with sum = " << targetSum << endl;
    }
    included.clear();

    start = chrono::high_resolution_clock::now();
    result = subsetSumGreedy(nums, nums.size(), targetSum, included);
    stop = chrono::high_resolution_clock::now();
    auto greedyDuration = chrono::duration_cast<std::chrono::microseconds>(stop - start);
    if (result) {
        cout << "Subset sum using greedy algorithm found with sum = " << targetSum << " and k = " << k <<  endl;
        cout << "Time: " << greedyDuration.count() << " microseconds" << endl;
        // cout << "[ ";
        // for (int x : included) {
        //     x = base4(x);
        //     cout << x << ' ';
        // }
        // cout << "]" << endl;
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