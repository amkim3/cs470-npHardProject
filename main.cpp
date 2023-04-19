#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "subsetSumGreedy.h"
#include <chrono>
#include "subsetSumBrute.h"
// #include "subsetSumRandom.h"
// #include "subsetSumCombo.h"
// #include "subsetSumThread.h"

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
    
    // set sum equal to the first line
    int sum = 0;
    getline(f, line);
    sum = stoi(line);

    // read integers and store in array
    vector<int> arr;
    int num = 0;
    while (getline(f, line)) {
        stringstream ss(line);
        ss >> num;
        arr.push_back(num);
    }
    f.close();

    // Get the size of vector
    int size = arr.size();

    // vector to hold elements included in subset sum
    // vector<int> result;
    vector<int> included;
    auto start = chrono::high_resolution_clock::now();
    bool result = subsetSumBrute(arr, size, sum, &included);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<std::chrono::microseconds>(stop - start);

    if (result) {
        cout << "Subset sum using brute force found with sum = " << sum << endl;
        cout << "Time: " << duration.count() << " microseconds" << endl;
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
    result = subsetSumGreedy(arr, size, sum, &included);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<std::chrono::microseconds>(stop - start);
    if (result) {
        cout << "Subset sum using greedy algorithm found with sum = " << sum << endl;
        cout << "Time: " << duration.count() << " microseconds" << endl;
        cout << "[ ";
        for (int x : included) {
            cout << x << ' ';
        }
        cout << "]" << endl;
    }
   
    else {
        cout << "No subset sum found using greedy algorithm with sum = " << sum << endl;
        cout << "Time: " << duration.count() << " microseconds" << endl;
    }

    // start = chrono::high_resolution_clock::now();
    // result = subsetSumGreedy2(arr, size, sum);
    // stop = chrono::high_resolution_clock::now();
    // duration = chrono::duration_cast<std::chrono::microseconds>(stop - start);

    // if (result) {
    //     cout << "Subset sum using greedy algorithm (+ threading) found with sum = " << sum << endl;
    //     cout << "Time: " << duration.count() << " microseconds" << endl;
    // }
   
    // else {
    //     cout << "No subset sum found using greedy algorithm (+ threading) with sum = " << sum << endl;
    //     cout << "Time: " << duration.count() << " microseconds" << endl;
    // }

    // start = chrono::high_resolution_clock::now();
    // result = subsetSumRandom(arr, size, sum);
    // stop = chrono::high_resolution_clock::now();
    // duration = chrono::duration_cast<std::chrono::microseconds>(stop - start);

    // if (result) {
    //     cout << "Subset sum using random algorithm found with sum = " << sum << endl;
    //     cout << "Time: " << duration.count() << " microseconds" << endl;
    // }

    // else {
    //     cout << "No subset sum found using random algorithm with sum = " << sum << endl;
    //     cout << "Time: " << duration.count() << " microseconds" << endl;
    // }

    // start = chrono::high_resolution_clock::now();
    // result = subsetSumCombo(arr, size, sum);
    // stop = chrono::high_resolution_clock::now();
    // duration = chrono::duration_cast<std::chrono::microseconds>(stop - start);

    // if (result) {
    //     cout << "Subset sum using combo (greedy + random) algorithm found with sum = " << sum << endl;
    //     cout << "Time: " << duration.count() << " microseconds" << endl;
    // }
    // else {
    //     cout << "No subset sum found using combo (greedy + random) algorithm with sum = " << sum << endl;
    //     cout << "Time: " << duration.count() << " microseconds" << endl;
    // }

    return 0;
}