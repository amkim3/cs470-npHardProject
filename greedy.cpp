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
        // cout << "Next. i is at " << i << ". size of array is " << array.size() << ". array[i] is " << array[i] << ". remaining is " << remaining << endl;
        // bool removed = false;
        srand(time(0)); // initialize the random seed
        int start = 0;
        int end;
        // if (it > 20) return false;
        if (remaining < array.back()) {
            // removed = true;
            // srand(time(0));
            start = 0;
            end = newSize;
            // cout << newSize << endl;
            long int randomIndex = start + (rand() % (end - start)); 
            if (!randNums.empty()) {
                while (randNums.top() == randomIndex) {
                    // randNums.pop();
                    // randomIndex--;
                    randomIndex = start + (rand() % (end - start)); 
                }
            }
            randNums.push(randomIndex);
            if (included.at(randomIndex) == smallest) { // if the random element to be removed is smallest, take the next element largest to it
                randomIndex--;
                if (randomIndex < 0) return false;
            }
            // cout << "random: " << randomIndex << ". size of included: " << included.size() << endl;
            // it++;
            // cout << "The subset sum cannot be found with the remaining available elements. Removing " << included.at(randomIndex) << " from the subset." << endl;
            remaining = remaining + included.at(randomIndex); // add back in the element at index i-jumps
            // cout << "remaining sum is now: " << remaining << endl;

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
            // cout << "replacement made" << endl;
            // cout << "remaining elements is now: "<< endl;
            // cout << "[ ";
            // for (int x : array) {
            //     cout << x << ' ';
            // }
            // cout << "]" << endl;
            // cout << "included is now: " << endl;
            // cout << "[ ";
            // for (auto it = included.begin(); it != included.end(); ++it) {
            //     std::cout << *it << " ";
            // }
            // cout << "]" << endl;
            size++;
            // cout << "index is now at" << i+1 << " " << array[i+1] << endl;
        }
        // pick a random index between 0 and whatever size we have
        else if (array[i] == remaining) { // if curr element = remaining
            // cout << remaining << endl;
            // cout << array[i] << endl;
            // if (removed == true) i++;
            // cout << "adding " << array[i] << " to the subset. Subset sum is found." << endl;
            included.push_back(array[i]); // This vector stores the elements that are included in the subset sum
            // return true; // break from the loop and return true
            break;
            // if (removed == true) i--;
        }
        else if (array[i] > remaining) { // curr element too big, we need to loop and find next biggest element <= remaining
            // if (removed == true) i++;
            // if (array[i] == dontAddBack) continue;
            int idx = lower_bound(array.begin() + i, array.end(), remaining, greater<int>()) - array.begin();
            // if the new index isn't at the end and it is equal to the remaining
            if (static_cast<size_t>(idx) == array.size()) return false;
            while (array[idx] == dontAddBack && (size_t)(idx) != (array.size())) {
                idx++;
            }
            if (array[idx] <= remaining) {
                // cout << "remaining: " << remaining << endl;
                // cout << "Next largest element that can be added is: " << array[idx] << ". Adding to the subset." << endl;
                included.push_back(array[idx]); // add to included
                remaining = remaining - array[idx];
                array.erase(array.begin() + idx);
                // cout << "included is now: " << endl;
                // cout << "[ ";
                // for (auto it = included.begin(); it != included.end(); ++it) {
                //     std::cout << *it << " ";
                // }
                // cout << "]" << endl;
                // cout << "remaining is now: " << remaining << endl;
                if (remaining == 0) break;
            }
            i = idx-1; // set i to the index
        }
        else if (remaining > array[i]) {
            if (array[i] == dontAddBack) i++;
            // cout << "size of array: " << array.size() << endl;
            // cout << "i: " << i << endl;
            // cout << "remaining: " << remaining << ". array[i]: " << array[i] << endl;
            // cout << "adding " << array[i] << " to the subset. The remaining sum needed is now " << remaining - array[i] << "." << endl;
            remaining = remaining - array[i];
            included.push_back(array[i]); // add to included
            // cout << "included is now: " << endl;
            // cout << "[ ";
            // for (auto it = included.begin(); it != included.end(); ++it) {
            //     std::cout << *it << " ";
            // }
            // cout << "]" << endl;
            newSize++;

            // this might break
            if (static_cast<size_t>(i) >= array.size()) {
                i = array.size() -1;
            }
            array.erase(array.begin() + i);
            i--;
            // cout << "remaining elements is now: "<< endl;
            // cout << "[ ";
            // for (int x : array) {
            //     cout << x << ' ';
            // }
            // cout << "]" << endl;
            
            // cout << "i is now " << i + 1 << endl;
        }
    }    
    int total = 0;
    for (auto it = included.begin(); it != included.end(); ++it) {
        total+=*it;
    }
    if (total == sum) return true;
    return false;
}