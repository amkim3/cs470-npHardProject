#include "subsetSumGreedy.h"
#include <random>
#include <algorithm>
#include <iostream>

bool subsetSumGreedy(vector<int> array, int size, int sum) {
    sort(array.begin(), array.end(), greater<int>());

    int remaining = sum;
    cout << "begin " << remaining << endl;
    int j = 0;
    int jumps = 1;
    while (array[j] > remaining) {
        j++;
    }
    for (int i = j; i < size; i++) {
        if (array[i] == remaining) {
            return true;
        }
        if (remaining < array[size]) {
            remaining = remaining + array[i-jumps];
            jumps+=2;
        }
        if (remaining > array[i]) {
            remaining = remaining - array[i];
        }
    }
    return false;
}