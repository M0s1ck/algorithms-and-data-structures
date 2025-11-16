#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

class ArrayGenerator {
private:
    int maxN_;
    int value_min_, value_max_;
    std::mt19937_64 gen_;
    std::vector<int> random_base_;
    std::vector<int> reverse_sorted_;
    std::vector<int> almost_sorted_;

public:
    ArrayGenerator(int maxN = 100000, int value_min = 0, int value_max = 10000, unsigned long long seed = 0)
        : maxN_(maxN), value_min_(value_min), value_max_(value_max)
    {
        if (seed == 0) {
            seed = static_cast<unsigned long long>(
                std::chrono::high_resolution_clock::now().time_since_epoch().count()
            );
        }
        gen_.seed(seed);
        build_random_base();
        build_reverse_sorted();
        build_almost_sorted();
    }

    std::vector<int> GetRandomSubarray(int n) const {
        return std::vector<int>(random_base_.begin(), random_base_.begin() + n);
    }

    std::vector<int> GetReversedSubarray(int n) const {
        return std::vector<int>(reverse_sorted_.begin(), reverse_sorted_.begin() + n);
    }

    std::vector<int> GetAlmostSortedSubarray(int n) const {
        return std::vector<int>(almost_sorted_.begin(), almost_sorted_.begin() + n);
    }

private:
    void build_random_base() {
        random_base_.resize(maxN_);
        std::uniform_int_distribution<int> dist(value_min_, value_max_);
        for (int i = 0; i < maxN_; ++i) random_base_[i] = dist(gen_);
    }

    void build_reverse_sorted() {
        reverse_sorted_ = random_base_;
        std::sort(reverse_sorted_.begin(), reverse_sorted_.end(), std::greater<int>());
    }

    void build_almost_sorted() {
        almost_sorted_ = random_base_;
        std::sort(almost_sorted_.begin(), almost_sorted_.end());

        int swaps = std::min(1000, std::max(1, maxN_ / 100));
        std::uniform_int_distribution<int> dist(0, maxN_ - 1);

        for (int k = 0; k < swaps; ++k) {
            int i = dist(gen_);
            int j = dist(gen_);
            if (i != j)
                std::swap(almost_sorted_[i], almost_sorted_[j]);
        }
    }
};