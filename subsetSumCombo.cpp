#include "subsetSumRandom.h"
#include <ctime>
#include <cstdlib>
#include <random>
#include <algorithm>
#include <cmath>
#include <iostream>

bool subsetSumCombo(vector<int> array, int size, int sum) {
    int newSize = 10;
    vector<int> subsetNums;
    for (int i = 0; i < newSize; i++) {
        srand(time(NULL));
        subsetNums.push_back(rand() % size);
    }
    vector<vector<bool>> cache(size+1, vector<bool>(sum+1));
    for (int i = 0; i <= newSize; i++) {
        cache[i][0] = true;
    }
    for (int i = 1; i <= sum; i++) {
        cache[0][i] = false;
    }
    for (int i = 1; i <= newSize; i++) { // i represents the size of array
        for (int j = 1; j <=sum; j++) { // j is the sum
            int currSum = j;
            int currElement = array[i-1];
            // If currElement is bigger than currSum, set the value to the previous element
            if (currElement > currSum) {
                cache[i][j] = cache[i-1][j];
            }
            // Else, see if sum can be reached by either including the current element, or excluding it using recursion
            else {
                cache[i][j] = cache[i-1][j] || cache[i-1][j-array[i-1]];
            }
        }
    }
    if (cache[newSize][sum] == true) {
        return true;
    }
    else {
        sort(array.begin(), array.end(), greater<int>());

        int remaining = sum;

        for (int i = 0; i < size; i++) {
            if (array[i] > remaining) {
                continue;
            }
            else if (array[i] == remaining) {
                return true;
            }
            else {
                remaining = remaining - array[i];
            }
        }
        return false;
    }
    
}
