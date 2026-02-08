#include <bits/stdc++.h>
using namespace std;

class HyperLogLog {
public:
    explicit HyperLogLog(uint32_t B)
        : B(B), m(1u << B), registers(m, 0) {}

    void add(uint32_t hash) {
        uint32_t idx = hash >> (32 - B);
        uint32_t w = (hash << B);
        uint8_t rho = leadingZeros(w) + 1;
        registers[idx] = max(registers[idx], rho);
    }

    double estimate() const {
        double alpha;
        if (m == 16) alpha = 0.673;
        else if (m == 32) alpha = 0.697;
        else if (m == 64) alpha = 0.709;
        else alpha = 0.7213 / (1.0 + 1.079 / m);

        double sum = 0.0;
        for (uint8_t r : registers) {
            sum += pow(2.0, -static_cast<int>(r));
        }

        double raw = alpha * m * m / sum;

        // small range correction
        if (raw <= 2.5 * m) {
            int zeros = count(registers.begin(), registers.end(), 0);
            if (zeros > 0) {
                raw = m * log(static_cast<double>(m) / zeros);
            }
        }

        return raw;
    }

    void reset() {
        fill(registers.begin(), registers.end(), 0);
    }

private:
    uint32_t B;
    uint32_t m;
    vector<uint8_t> registers;

    static uint8_t leadingZeros(uint32_t x) {
        if (x == 0) return 32;
        return __builtin_clz(x);
    }
};