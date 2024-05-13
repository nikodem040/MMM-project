#include <iostream>
#include <vector>
#include <cmath>
#include "gnuplot-iostream.h"

using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main() {
    // System parameters
    double R1 = 1.0;
    double R2 = 1.0;
    double C1 = 1.0;
    double C2 = 1.0;

    // Simulation parameters
    double T = 50.0;
    double h = 0.001;
    double L = 2.5;

    // Time vector
    vector<double> t;
    for (double i = 0; i <= T; i += h) {
        t.push_back(i);
    }

    // Input signal
    vector<double> u;
    for (double i : t) {
        u.push_back(sin(2 * M_PI * i / (T / L)));
    }

    // System simulation
    vector<double> y(t.size(), 0.0);
    for (size_t i = 0; i < t.size(); ++i) {
        double a1 = (C1 * (C1 * R1 + C1 * R2 + C2 * R1)) / (C1 * R1 * R2);
        double a0 = (C1 * C1 * C2) / (C1 * R1 * R2);

        double y_numerator = (C2 / C1) * R1 * R2;
        double y_denominator = 1 + a1 * t[i] + a0 * t[i] * t[i];

        y[i] = y_numerator / y_denominator;
    }

    // Plotting using Gnuplot
    Gnuplot gp;
    gp << "set title 'Input and Output Signals'\n";
    gp << "set xlabel 'Time'\n";
    gp << "set ylabel 'Amplitude'\n";
    gp << "plot '-' with lines title 'Input', '-' with lines title 'Output'\n";
    gp.send1d(make_tuple(t, u)); // Send input data
    gp.send1d(make_tuple(t, y)); // Send output data

    return 0;
}
