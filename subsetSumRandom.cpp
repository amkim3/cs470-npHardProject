#include "subsetSumRandom.h"
#include <ctime>
#include <cstdlib>
#include <cmath>

bool subsetSumRandom(vector<int> array, int size, int sum) {
    int newSize = size;
    newSize = size/2;
    srand(time(NULL));
    vector<int> subsetNums;
    for (int i = 0; i < newSize; i++) {
        subsetNums.push_back(rand() % size);
    }

    bool cache[newSize+1][sum+1];
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
    return cache[newSize][sum];
}
