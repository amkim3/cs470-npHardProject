#include "subsetSumGreedy.h"
#include <random>
#include <algorithm>
#include <iostream>

bool subsetSumGreedy(vector<int> array, int size, int sum) {
    sort(array.begin(), array.end(), greater<int>());
    while (array.back() == 0) {
        array.pop_back();
    }
    int remaining = sum;
    int jumps = 1;
    int j = lower_bound(array.begin(), array.end(), remaining, greater<int>()) - array.begin();
    for (int i = j; i < size;i++) {
        // cout << "index: " << i << endl;
        // cout << remaining << endl;
        if (array[i] == remaining) {
            return true;
        }
        if (array[i] > remaining) {
            // cout << array[i] << " too big" << endl;
            int idx = std::lower_bound(array.begin() + i, array.end(), remaining, greater<int>()) - array.begin();
            if (idx != array.size() && array[idx] == remaining) {
                return true;
            }
            i = idx;
            // cout << "next good index: " << array[i] << endl;
            // cout << "i is now: " << i << endl;
        }
        if (remaining < array.back()) {
            remaining = remaining + array[i-jumps];
            jumps+=1;
        }
        if (remaining > array[i]) {
            remaining = remaining - array[i];
            // cout << "new: " << remaining << endl;
        }
    }    
    
    return false;
}