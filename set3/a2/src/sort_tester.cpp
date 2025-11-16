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
    SortTester(int minN, int maxN, int step, int repeats)
        : minN_(minN), maxN_(maxN), step_(step), repeats_(repeats), generator_(maxN) {}

    void RunAll() {
        std::ofstream fout("data.csv");
        fout << "N,"
             << "merge_rand,merge_insertion_15_rand,merge_insertion_30_rand,merge_insertion_50_rand,"
             << "merge_reversed,merge_insertion_15_reversed,merge_insertion_30_reversed,merge_insertion_50_reversed,"
             << "merge_almost_sorted,merge_insertion_15_almost_sorted,merge_insertion_30_almost_sorted,merge_insertion_50_almost_sorted\n";

        const std::vector<int> thresholds = {15, 30, 50};

        for (int n = minN_; n <= maxN_; n += step_) {
            auto randArr = generator_.GetRandomSubarray(n);
            auto revArr = generator_.GetReversedSubarray(n);
            auto almostArr = generator_.GetAlmostSortedSubarray(n);

            double merge_rand = Benchmark(randArr, [](std::vector<int>& a){ MergeSort(a); });
            double merge_rev = Benchmark(revArr, [](std::vector<int>& a){ MergeSort(a); });
            double merge_almost = Benchmark(almostArr, [](std::vector<int>& a){ MergeSort(a); });

            fout << n << "," << merge_rand;

            for (int t : thresholds)
                fout << "," << Benchmark(randArr, [t](std::vector<int>& a){ MergeInsertionSort(a, t); });

            fout << "," << merge_rev;
            for (int t : thresholds)
                fout << "," << Benchmark(revArr, [t](std::vector<int>& a){ MergeInsertionSort(a, t); });

            fout << "," << merge_almost;
            for (int t : thresholds)
                fout << "," << Benchmark(almostArr, [t](std::vector<int>& a){ MergeInsertionSort(a, t); });

            fout << "\n";

            if (n % (10 * step_) == 0)
                std::cout << "N=" << n << " done.\n";
        }

        fout.close();
        std::cout << "Data written to data.csv\n";
    }

private:
    int minN_, maxN_, step_, repeats_;
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
        double result;
        if (times.size() % 2 == 1)
            result = times[times.size() / 2];
        else
            result = 0.5 * (times[times.size() / 2 - 1] + times[times.size() / 2]);

        return result; // микросекунды
    }
};
