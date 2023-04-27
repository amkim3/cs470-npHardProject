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
#include "3satToSs.h"
#include "mapFromVC.h"

using namespace std;

int main() {
    int command;
    while (true) {
        cout << "Select number to execute command: " << endl;
        cout << "1 - subset sum - compare brute and heuristic" << endl;
        cout << "2 - map from vertex cover to subset sum" << endl;
        cout << "3 - map from 3sat to subset sum" << endl;
        cout << "4 - exit" << endl;
        cout << "Enter a command: ";
        cin >> command;

        // read in file
        if (command == 4) break; // exit

        else if (command == 1) { // subset sum
            string file;
            cout << "Enter file to perform subset sum: ";
            cin >> file;
            cout << "----------------------------------" << endl;
            ifstream f;
            f.open(file);

            // if file can't be opened
            if (!f.is_open()) { 
                cout << "File cannot be opened." << endl;
                return -1;
            }
        
            string line;
            getline(f, line);
            long int sum = stoi(line); // set sum equal to the first line
            vector<long long int> arr; // read integers and store in array
            int num = 0;

            // add numbers to array
            while (getline(f, line) && line != "$") {
                if (line[0] == '$') break;
                stringstream ss(line);
                ss >> num;
                arr.push_back(num);
            }
            f.close();

            // Get the size of vector
            int size = arr.size();

            vector<long long int> included; // vector to hold elements included in subset sum
            auto start = chrono::high_resolution_clock::now(); // start timer
            bool result = subsetSumBrute(arr, size, sum, included);
            auto stop = chrono::high_resolution_clock::now(); // stop timer
            auto bruteDuration = chrono::duration_cast<std::chrono::microseconds>(stop - start); // duration

            // if subset sum was found
            if (result) {
                cout << "Subset sum using brute force found with sum = " << sum << endl;
                cout << "Time: " << bruteDuration.count() << " microseconds" << endl;
                cout << "[ ";
                for (int x : included) { // print elements included to find subset sum
                    cout << x << ' ';
                }
                cout << "]" << endl;
            }

            // if no subset sum was found
            else {
                cout << "No subset sum found using brute force with sum = " << sum << endl;
            }

            included.clear(); // clear to run greedy algorithm

            start = chrono::high_resolution_clock::now(); // start timer
            result = subsetSumGreedy(arr, size, sum, included);
            stop = chrono::high_resolution_clock::now(); // stop timer
            auto greedyDuration = chrono::duration_cast<std::chrono::microseconds>(stop - start); // duration

            // if subset sum was found
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
                // cout << total << endl;
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

            // if no subset sum was found
            else {
                cout << "No subset sum found using greedy algorithm with sum = " << sum << endl;
                cout << "Time: " << greedyDuration.count() << " microseconds" << endl;
            }    
        }

        // Vertex cover -> subset sum
        else if (command == 2) {
            string file;
            cout << "Enter file of vertex cover format to map to subset sum: ";
            cin >> file;
            cout << "--------------------------------------------------------" << endl;
            vector<long long int> included;
            vcToSs(file, included);
        }

        // 3sat -> subset sum
        else if (command == 3) {
            string file;
            cout << "Enter file of 3sat format to map to subset sum: ";
            cin >> file;
            cout << "------------------------------------------------" << endl;;
            ifstream f;
            f.open(file);

            // if file can't be opened
            if (!f.is_open()) { 
                cout << "File cannot be opened." << endl;
                return -1;
            }
        
            string line;
            getline(f, line);
            int numVars = stoi(line); // num vars equal to first line
            vector<tuple<int, int, int>> ints; // read integers and store in vertex of tuples
            int num1;
            int num2;
            int num3;
            while (getline(f, line) && line != "$") {
                if (line[0] == '$') break;
                stringstream ss(line);
                ss >> num1 >> num2 >> num3;
                ints.push_back(make_tuple(num1, num2, num3));
            }
            satToSs(ints, numVars);
            f.close();
        }
    }
    
    return 0;
}