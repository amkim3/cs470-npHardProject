#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "subsetSumGreedy.h"
#include <chrono>
#include <bits/stdc++.h>
#include "subsetSumBrute.h"
#include <iomanip>


using namespace std;

int main(int argc, char *argv[]) {
    // read in file
    ifstream f;
    f.open(argv[1]);

    // if file can't be opened
    if (!f.is_open()) { 
        cout << "File cannot be opened." << endl;
        return -1;
    }
    
    string line;
    getline(f, line);
    int sum = stoi(line); // set sum equal to the first line

    
    vector<int> arr; // read integers and store in array
    int num = 0;
    while (getline(f, line)) {
        stringstream ss(line);
        ss >> num;
        arr.push_back(num);
    }
    f.close();

    // Get the size of vector
    int size = arr.size();

    vector<int> included; // vector to hold elements included in subset sum
    auto start = chrono::high_resolution_clock::now();
    bool result = subsetSumBrute(arr, size, sum, included);
    auto stop = chrono::high_resolution_clock::now();
    auto bruteDuration = chrono::duration_cast<std::chrono::microseconds>(stop - start);

    if (result) {
        cout << "Subset sum using brute force found with sum = " << sum << endl;
        cout << "Time: " << bruteDuration.count() << " microseconds" << endl;
        cout << "[ ";
        for (int x : included) {
            cout << x << ' ';
        }
        cout << "]" << endl;
    }
    else {
        cout << "No subset sum found using brute force with sum = " << sum << endl;
    }
    included.clear();
    start = chrono::high_resolution_clock::now();
    int c =  0;
    // for (int i = 0; i < 5; i++) {
    //     included.clear();
    //     result = subsetSumGreedy(arr, size, sum, included);
    //     cout << i << " " << result << endl;
    //     if (result) {
    //         c++;
    //     }
    // }
    // cout << c << endl;
    // cout << static_cast<double>(c)  << endl;
    result = subsetSumGreedy(arr, size, sum, included);
    stop = chrono::high_resolution_clock::now();
    auto greedyDuration = chrono::duration_cast<std::chrono::microseconds>(stop - start);
    if (result) {
        cout << "Subset sum using greedy algorithm found with sum = " << sum << endl;
        cout << "Time: " << greedyDuration.count() << " microseconds" << endl;
        cout << "[ ";
        for (int x : included) {
            cout << x << ' ';
        }
        cout << "]" << endl;
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
    

    return 0;
}