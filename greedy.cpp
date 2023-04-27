#include "subsetSumGreedy.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <stack> 

using namespace std;

bool subsetSumGreedy(vector<long long int> array, int size, long long int sum, vector<long long int> &included) {
    sort(array.begin(), array.end(), greater<long long int>()); // Begin by sorting the array
    while (array.back() == 0) {
        array.pop_back();
    }
    long long int remaining = sum; // Remaining will be sum at start
    int j = lower_bound(array.begin(), array.end(), remaining, greater<long long int>()) - array.begin(); // j is where we start (finds the largest element <= remaining)
    int smallest = array.back();     // smallest makes sure that we don't remove the smallest int in the array when we can't find the sum
    int newSize = 0; // size of included
    int dontAddBack = -1; // don't add back the element that we removed when we do random removal
    stack<int> randNums;
    for (int i = j; i < size;i++) { // Loop through sorted array
        srand(time(0)); // initialize the random seed
        int start = 0;
        int end;
        if (remaining < array.back()) {
            start = 0;
            end = newSize;
            long int randomIndex = start + (rand() % (end - start)); 
            if (!randNums.empty()) {
                while (randNums.top() == randomIndex) {
                    randomIndex = start + (rand() % (end - start)); 
                }
            }
            randNums.push(randomIndex);
            if (included.at(randomIndex) == smallest) { // if the random element to be removed is smallest, take the next element largest to it
                randomIndex--;
                if (randomIndex < 0) return false;
            }
            remaining = remaining + included.at(randomIndex); // add back in the element at index i-jumps

            array.push_back(included.at(randomIndex));
            sort(array.begin(), array.end(), greater<int>());

            auto it = find(array.begin(), array.end(), included.at(randomIndex));
            if (it != array.end()) {
                i = it - array.begin()-1;
            }
            dontAddBack = included.at(randomIndex);
            auto last = find(included.begin(), included.end(), included.at(randomIndex)); // find that element in the included vector
            included.erase(last);
            newSize--;
            size++;
        }
        // pick a random index between 0 and whatever size we have
        else if (array[i] == remaining) { // if curr element = remaining
            included.push_back(array[i]); // This vector stores the elements that are included in the subset sum
            break;
        }
        else if (array[i] > remaining) { // curr element too big, we need to loop and find next biggest element <= remaining
            
            int idx = lower_bound(array.begin() + i, array.end(), remaining, greater<int>()) - array.begin();
            // if the new index isn't at the end and it is equal to the remaining
            if (static_cast<size_t>(idx) == array.size()) return false;
            while (array[idx] == dontAddBack && (size_t)(idx) != (array.size())) {
                idx++;
            }
            if (array[idx] <= remaining) {
                included.push_back(array[idx]); // add to included
                remaining = remaining - array[idx];
                array.erase(array.begin() + idx);
                if (remaining == 0) break;
            }
            i = idx-1; // set i to the index
        }
        else if (remaining > array[i]) {
            if (array[i] == dontAddBack) i++;
            remaining = remaining - array[i];
            included.push_back(array[i]); // add to included
            newSize++;

            // set i
            if (static_cast<size_t>(i) >= array.size()) {
                i = array.size() -1;
            }
            array.erase(array.begin() + i);
            i--;
        }
    }    

    // double check to make sure subset sum was found
    int total = 0;
    for (auto it = included.begin(); it != included.end(); ++it) {
        total+=*it;
    }
    if (total == sum) return true;
    
    return false;
}