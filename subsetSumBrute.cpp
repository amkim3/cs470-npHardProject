#include "subsetSumBrute.h"

// bool subsetSum(vector<int> array, int size, int sum, vector<int>* result) {
bool subsetSumBrute(vector<int> array, int size, int sum) {

    // cache[i,j] will be true if subset of elements in array from 0 to i is equal to j
    // bool cache[size+1][sum+1];
    vector<vector<bool>> cache(size+1, vector<bool>(sum+1));

    // Initialize cache to be true if the sum that we're looking for is 0
    for (int i = 0; i <= size; i++) {
        cache[i][0] = true;
    }
    
    // Initialize cache to be false if the sum is nonzero and the remaining elements is <=0
    for (int i = 1; i <= sum; i++) {
        cache[0][i] = false;
    }

    // set cache to false for all values
    for (int i = 1; i <= size; i++) { // i represents the size of array
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
    return cache[size][sum];
}