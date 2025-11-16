#include <iostream>
#include <vector>
#include <random>

#include "sort_tester.cpp"

int main() {
    int minN = 500;
    int maxN = 100000;
    int step = 100;
    int repeats = 20;
    int insertionSwitchThreshold = 16;

    SortTester tester(minN, maxN, step, repeats, insertionSwitchThreshold);
    tester.RunAll();
    return 0;
}