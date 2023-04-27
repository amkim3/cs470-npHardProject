#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "subsetSumBrute.h"
#include "subsetSumGreedy.h"
#include <chrono>

using namespace std;

void satToSs(vector<tuple<int, int, int>>, int numVars);