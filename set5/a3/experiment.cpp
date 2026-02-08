#include <bits/stdc++.h>
using namespace std;

#include "hash_func.cpp"
#include "hyper_loglog.cpp"
#include "random_stream_gen.cpp"

int main() {
    const size_t STREAM_SIZE = 200000;
    const size_t STEP = 5000;
    const size_t RUNS = 20;
    const uint32_t B = 10; // 1024 registers 

    RandomStreamGen gen;
    HashFuncGen hasher;

    vector<double> meanEstimate;
    vector<double> stdEstimate;
    vector<double> trueValues;

    size_t steps = STREAM_SIZE / STEP;
    meanEstimate.resize(steps, 0.0);
    stdEstimate.resize(steps, 0.0);
    trueValues.resize(steps, 0.0);

    for (size_t run = 0; run < RUNS; ++run) {
        HyperLogLog hll(B);
        unordered_set<string> exact;

        for (size_t i = 0; i < steps; ++i) {
            for (size_t j = 0; j < STEP; ++j) {
                string s = gen.next();
                exact.insert(s);
                hll.add(hasher(s));
            }

            double est = hll.estimate();
            double exactCnt = exact.size();

            meanEstimate[i] += est;
            stdEstimate[i] += est * est;
            trueValues[i] = exactCnt;
        }
    }

    for (size_t i = 0; i < steps; ++i) {
        meanEstimate[i] /= RUNS;
        stdEstimate[i] = sqrt(
            stdEstimate[i] / RUNS - meanEstimate[i] * meanEstimate[i]
        );
    }

    ofstream out("hll_results.csv");
    out << "step,true,mean_estimate,std\n";
    for (size_t i = 0; i < steps; ++i) {
        out << (i + 1) * STEP << ","
            << trueValues[i] << ","
            << meanEstimate[i] << ","
            << stdEstimate[i] << "\n";
    }
    out.close();

    cout << "Experiment finished. Results saved to hll_results.csv\n";
}