#include <vector>
#include <fstream>
#include <chrono>
#include <random>
#include <algorithm>
#include <functional>
#include <iostream>

#include "sorts.cpp"
#include "array_generator.cpp"

class SortTester {
public:
    SortTester(int minN, int maxN, int step, int repeats, int introThreshold)
        : minN_(minN), maxN_(maxN), step_(step), repeats_(repeats),
          introThreshold_(introThreshold), generator_(maxN) {}

    void RunAll() {
        std::ofstream fout("data.csv");

        fout << "N,"
             << "quick_rand,intro_rand,"
             << "quick_reversed,intro_reversed,"
             << "quick_almost,intro_almost\n";

        for (int n = minN_; n <= maxN_; n += step_) {
            auto randArr = generator_.GetRandomSubarray(n);
            auto revArr = generator_.GetReversedSubarray(n);
            auto almostArr = generator_.GetAlmostSortedSubarray(n);

            double quick_rand = Benchmark(randArr, [](std::vector<int>& a){ QuickSort(a); });

            double intro_rand = Benchmark(randArr, [this](std::vector<int>& a){ IntroSort(a, introThreshold_); });

            double quick_rev = Benchmark(revArr, [](std::vector<int>& a){ QuickSort(a); });

            double intro_rev = Benchmark(revArr,[this](std::vector<int>& a){ IntroSort(a, introThreshold_); });

            double quick_almost = Benchmark(almostArr, [](std::vector<int>& a){ QuickSort(a); });

            double intro_almost = Benchmark(almostArr, [this](std::vector<int>& a){ IntroSort(a, introThreshold_); });

            fout << n << ","
                 << quick_rand << "," << intro_rand << ","
                 << quick_rev << "," << intro_rev << ","
                 << quick_almost << "," << intro_almost
                 << "\n";

            if (n % (10 * step_) == 0)
                std::cout << "N=" << n << " done.\n";
        }

        fout.close();
        std::cout << "Data written to data.csv\n";
    }

private:
    int minN_, maxN_, step_, repeats_, introThreshold_;
    ArrayGenerator generator_;

    template <typename Func>
    double Benchmark(const std::vector<int>& arr, Func f) {
        std::vector<double> times;
        times.reserve(repeats_);

        for (int i = 0; i < repeats_; ++i) {
            std::vector<int> copy = arr;

            auto start = std::chrono::high_resolution_clock::now();
            f(copy);
            auto end = std::chrono::high_resolution_clock::now();

            double micros = std::chrono::duration<double, std::micro>(end - start).count();
            times.push_back(micros);
        }

        std::sort(times.begin(), times.end());

        // median
        if (times.size() % 2 == 1)
            return times[times.size() / 2];
        else
            return 0.5 * (times[times.size() / 2 - 1] + times[times.size() / 2]);
    }
};
