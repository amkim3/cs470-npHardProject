#include "subsetSumThread.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>

using namespace std;

bool subsetSumGreedy2Helper(vector<int> array, int size, int sum, int jumps) {
    sort(array.begin(), array.end(), greater<int>());
    while (array.back() == 0) {
        array.pop_back();
    }
    int remaining = sum;
    int j = 0;
    while (array[j] > remaining) {
        j++;
    }
    for (int i = j; i < size*2; i++) {
        if (array[i] == remaining) {
            return true;
        }
        if (remaining < array.back()) {
            remaining = remaining + array[i-jumps];
            j +=1;
        }
        if (remaining > array[i]) {
            remaining = remaining - array[i];
        }
    }
    return false;
}

void subsetSumGreedy2Thread(vector<int> array, int size, int sum, int jumps, bool &result) {
    result = subsetSumGreedy2Helper(array, size, sum, jumps);
}

bool subsetSumGreedy2(vector<int> array, int size, int sum) {
    vector<thread> threads;

    bool result = false;
    for (int jumps = 1; jumps <= 3; jumps++) {
        threads.emplace_back(subsetSumGreedy2Thread, array, size, sum, jumps, ref(result));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return result;
}
