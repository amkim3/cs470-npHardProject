#include "subsetSumBrute.h"
#include <algorithm>
#include <iostream>
#include <functional>
#include <numeric>

using namespace std;

bool subsetSumBrute(vector<long long int> array, int size, long long int sum, vector<long long int> &included, bool vc) {

    /* see the below example for how the cache works. the rows are elements in the array, and the columns are the numbers up to the sum.
    -- 0    1   2   3   ...     sum
    0  T    F   F   F   F       F
    5  T    F   F   F   F       F
    3  T    F   F   T   F       F
    8  T    F   F   T   F       F
    .
    .
    .
    */

    vector<vector<bool>> cache(size+1, vector<bool>(sum+1)); // 2d cache that holds true of false for each element and sum

    // Initialize cache to be true if the sum that we're looking for is 0
    for (int i = 0; i <= size; i++) {
        cache[i][0] = true;
    }
    
    // Initialize cache to be false for all values (except when sum == 0)
    for (int i = 1; i <= sum; i++) {
        cache[0][i] = false;
    }

    for (int i = 1; i <= size; i++) { // i represents the size of array
        for (long int j = 1; j <=sum; j++) { // j is the sum
            long int currSum = j;
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

    // This is to store the elements we used to find subset sum in the included vector, to print in main.cpp
    bool found = false;
    for (long int i = size, j = sum; i > 0 && !found; i--) {
        if (cache[i][j] && !cache[i - 1][j]) {
            included.push_back(array[i - 1]);
            j -= array[i - 1];
            found = (j == 0);
        }
    }
    reverse(included.begin(), included.end());
    return cache[size][sum]; // either true or false
    
}