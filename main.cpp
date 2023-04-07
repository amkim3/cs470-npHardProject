#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "subsetSumBrute.h"

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

    if (subsetSumBrute(arr, size, sum)) {
        cout << "Yes!" << endl;
    }
    // if (subsetSum(arr, size, sum, &result)) {
    //     cout << "Yes!" << endl;
    // }
    else {
        cout << "No :(" << endl;
    }
    return 0;
}