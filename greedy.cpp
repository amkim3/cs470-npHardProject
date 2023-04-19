#include "subsetSumGreedy.h"
#include <random>
#include <algorithm>
#include <iostream>

using namespace std;

bool subsetSumGreedy(vector<int> array, int size, int sum, vector<int>* included) {
    sort(array.begin(), array.end(), greater<int>()); // Begin by sorting the array

    // Remove all zeros from the sorted array
    while (array.back() == 0) {
        array.pop_back();
    }
    int remaining = sum; // Remaining will be sum at start
    int j = lower_bound(array.begin(), array.end(), remaining, greater<int>()) - array.begin(); // j is where we start (finds the largest element <= remaining)
    int smallest = array.back();     // smallest makes sure that we don't remove the smallest int in the array when we can't find the sum
    int newSize = 0; // size of included
    int dontAddBack = -1; // don't add back the element that we removed when we do random removal

    for (int i = j; i < size;i++) { // Loop through sorted array
        bool removed = false;
        srand(time(0)); // initialize the random seed
        int start = 0;
        int end;
        if (remaining < array.back()) {
            removed = true;
            start = 0;
            end = newSize;
            int randomIndex = start + (rand() % (end - start)); 
            if (included->at(randomIndex) == smallest) { // if the random element to be removed is smallest, take the next element largest to it
                randomIndex--;
            }
            // cout << "The subset sum cannot be found with the remaining available elements. Removing " << included->at(randomIndex) << " from the subset." << endl;
            remaining = remaining + included->at(randomIndex); // add back in the element at index i-jumps
            // cout << "remaining sum is now: " << remaining << endl;

            array.push_back(included->at(randomIndex));
            sort(array.begin(), array.end(), greater<int>());

            auto it = find(array.begin(), array.end(), included->at(randomIndex));
            if (it != array.end()) {
                i = it - array.begin()-1;
            }
            dontAddBack = included->at(randomIndex);
            auto last = find(included->begin(), included->end(), included->at(randomIndex)); // find that element in the included vector
            included->erase(last);
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
            // for (auto it = included->begin(); it != included->end(); ++it) {
            //     std::cout << *it << " ";
            // }
            // cout << "]" << endl;
            // cout << "index is now at" << i+1 << " " << array[i+1] << endl;
        }
        // pick a random index between 0 and whatever size we have
        if (array[i] == remaining) { // if curr element = remaining
            if (removed == true) i++;
            // cout << "adding " << array[i] << " to the subset. Subset sum is found." << endl;
            included->push_back(array[i]); // This vector stores the elements that are included in the subset sum
            return true; // break from the loop and return true
            if (removed == true) i--;
        }
        if (array[i] > remaining) { // curr element too big, we need to loop and find next biggest element <= remaining
            if (removed == true) i++;
            if (array[i] == dontAddBack) continue;
            int idx = std::lower_bound(array.begin() + i, array.end(), remaining, less_equal<int>()) - array.begin();
            // if the new index isn't at the end and it is equal to the remaining
            if (idx == array.size()) continue;
            if (idx != array.size() && array[idx] >= remaining) {
                // cout << remaining << endl;
                // cout << "Next largest element that can be added is: " << array[idx] << ". Adding to the subset." << endl;
                included->push_back(array[idx]); // add to included
                array.erase(array.begin() + idx);
                return true; // end
                // cout << "included is now: " << endl;
                // cout << "[ ";
                // for (auto it = included->begin(); it != included->end(); ++it) {
                //     std::cout << *it << " ";
                // }
                // cout << "]" << endl;
                if (remaining == 0) return true;

            }
            i = idx-1; // set i to the index
        }
        if (remaining > array[i]) {
            if (removed == true) i++;
            if (array[i] == dontAddBack) continue;
        
            // cout << "i is now " << i + 1 << endl;
            // cout << "adding " << array[i] << " to the subset. The remaining sum needed is now " << remaining - array[i] << "." << endl;
            remaining = remaining - array[i];
            included->push_back(array[i]); // add to included
            // cout << "included is now: " << endl;
            // cout << "[ ";
            // for (auto it = included->begin(); it != included->end(); ++it) {
            //     std::cout << *it << " ";
            // }
            // cout << "]" << endl;
            newSize++;

            // this might break
            if (i >= array.size()) {
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
    return false; // if we get to end of loop and haven't returned true, we return false
}