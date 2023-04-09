#ifndef SUBSETSUMTHREAD_H
#define SUBSETSUMTHREAD_H

#include <vector>

bool subsetSumGreedy2Helper(std::vector<int> array, int size, int sum, int jumps);
void subsetSumGreedy2Thread(std::vector<int> array, int size, int sum, int jumps, bool &result);
bool subsetSumGreedy2(std::vector<int> array, int size, int sum);

#endif