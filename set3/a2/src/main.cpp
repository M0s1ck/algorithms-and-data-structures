#include "sort_tester.cpp"

int main() {
    int minN = 500;
    int maxN = 100000;
    int step = 100;
    int repeats = 20;
    SortTester tester(minN, maxN, step, repeats);
    tester.RunAll();
    return 0;
}