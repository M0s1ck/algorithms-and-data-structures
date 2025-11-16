#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <random>
#include <chrono>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const double PI = std::acos(-1.0);

    double x[3] = {1.0, 1.5, 2.0};
    double y[3] = {1.0, 2.0, 1.5};
    double r[3] = {1.0, std::sqrt(5.0)/2.0, std::sqrt(5.0)/2.0};

    const double S_true = 0.25 * PI + 1.25 * std::asin(0.8) - 1.0;

    // wide rectangle
    double xmin_all = 1e9, ymin_all = 1e9, xmax_all = -1e9, ymax_all = -1e9;
    for (int i = 0; i < 3; ++i) {
        xmin_all = std::min(xmin_all, x[i] - r[i]);
        ymin_all = std::min(ymin_all, y[i] - r[i]);
        xmax_all = std::max(xmax_all, x[i] + r[i]);
        ymax_all = std::max(ymax_all, y[i] + r[i]);
    }
    const double Srect_wide = (xmax_all - xmin_all) * (ymax_all - ymin_all);

    // narrow rectangle
    double xmin_int = x[0] - r[0];
    double ymin_int = y[0] - r[0];
    double xmax_int = x[0] + r[0];
    double ymax_int = y[0] + r[0];
    for (int i = 1; i < 3; ++i) {
        xmin_int = std::max(xmin_int, x[i] - r[i]);
        ymin_int = std::max(ymin_int, y[i] - r[i]);
        xmax_int = std::min(xmax_int, x[i] + r[i]);
        ymax_int = std::min(ymax_int, y[i] + r[i]);
    }
    const double Srect_narrow = (xmax_int - xmin_int) * (ymax_int - ymin_int);

    std::mt19937_64 gen(
        static_cast<unsigned long long>(
            std::chrono::high_resolution_clock::now().time_since_epoch().count()
        )
    );
    std::uniform_real_distribution<double> ux_wide(xmin_all, xmax_all);
    std::uniform_real_distribution<double> uy_wide(ymin_all, ymax_all);
    std::uniform_real_distribution<double> ux_narrow(xmin_int, xmax_int);
    std::uniform_real_distribution<double> uy_narrow(ymin_int, ymax_int);

    std::ofstream fout("data.csv");
    fout << "N,S_est_wide,rel_err_wide,S_est_narrow,rel_err_narrow\n";
    fout << std::fixed << std::setprecision(12);

    for (int N = 100; N <= 100000; N += 500) {
        int M_wide = 0, M_narrow = 0;

        // wide
        for (int i = 0; i < N; ++i) {
            double xw = ux_wide(gen);
            double yw = uy_wide(gen);
            bool inside = true;
            for (int j = 0; j < 3; ++j) {
                double dx = xw - x[j];
                double dy = yw - y[j];
                if (dx*dx + dy*dy > r[j]*r[j]) {
                    inside = false;
                    break;
                }
            }
            if (inside) ++M_wide;
        }

        // narrow
        for (int i = 0; i < N; ++i) {
            double xn = ux_narrow(gen);
            double yn = uy_narrow(gen);
            bool inside = true;
            for (int j = 0; j < 3; ++j) {
                double dx = xn - x[j];
                double dy = yn - y[j];
                if (dx*dx + dy*dy > r[j]*r[j]) {
                    inside = false;
                    break;
                }
            }
            if (inside) ++M_narrow;
        }

        double S_est_wide = (static_cast<double>(M_wide) / N) * Srect_wide;
        double S_est_narrow = (static_cast<double>(M_narrow) / N) * Srect_narrow;

        double rel_err_wide = std::fabs(S_est_wide - S_true) / S_true;
        double rel_err_narrow = std::fabs(S_est_narrow - S_true) / S_true;

        fout << N << ","
             << S_est_wide << "," << rel_err_wide << ","
             << S_est_narrow << "," << rel_err_narrow << "\n";
    }

    fout.close();
    return 0;
}
