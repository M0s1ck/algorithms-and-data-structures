#include <iostream>
#include <iomanip>
#include <cmath>
#include <random>
#include <chrono>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    double x[3], y[3], r[3];
    for (int i = 0; i < 3; ++i) {
        std::cin >> x[i] >> y[i] >> r[i];
    }

    double xmin = 1e9, ymin = 1e9, xmax = -1e9, ymax = -1e9;
    for (int i = 0; i < 3; ++i) {
        xmin = std::min(xmin, x[i] - r[i]);
        ymin = std::min(ymin, y[i] - r[i]);
        xmax = std::max(xmax, x[i] + r[i]);
        ymax = std::max(ymax, y[i] + r[i]);
    }

    double Srect = (xmax - xmin) * (ymax - ymin);

    std::mt19937_64 gen;
    std::uniform_real_distribution<double> dist_x(xmin, xmax);
    std::uniform_real_distribution<double> dist_y(ymin, ymax);

    const int N = 1'000'000;
    int M = 0;

    for (int i = 0; i < N; ++i) {
        double px = dist_x(gen);
        double py = dist_y(gen);
        bool inside = true;
        for (int j = 0; j < 3; ++j) {
            double dx = px - x[j];
            double dy = py - y[j];
            if (dx * dx + dy * dy > r[j] * r[j]) {
                inside = false;
                break;
            }
        }
        if (inside) ++M;
    }

    double S_est = (static_cast<double>(M) / N) * Srect;

    std::cout << std::setprecision(20) << S_est << "\n";
    return 0;
}
