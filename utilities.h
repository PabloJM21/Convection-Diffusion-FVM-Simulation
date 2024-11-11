#ifndef UTILITIES_H
#define UTILITIES_H

#include "difference.h"
#include "dynamicVector.h"

// Global functions
double F(double, double) { return 0.0; }
double C(double, double) { return 0.0; }
double Alpha(double, double) { return 0.0; }
double G(double, double) { return 0.0; }
double Initial(double x) { return 1.0 - x * x; }
const double Epsilon = 1.0;

// convDif for FVM
template <class T>
void convDifFVM(difference<T> &d, dynamicVector<T> &f, double h, double deltaT, double t) {
    for (int j = 0; j < d.width(); j++) {
        double fluxConv = C(j * h, t);
        double fluxDiff = Epsilon / h;

        // Set convection term based on FVM upwind scheme
        if (fluxConv > 0) {
            d(j, j) += fluxConv / h;
            d(j, j - 1) -= fluxConv / h;
        } else {
            d(j, j) -= fluxConv / h;
            d(j, j + 1) += fluxConv / h;
        }

        // Set diffusion term (central differencing)
        d(j, j) += 2.0 * fluxDiff;
        if (j > 0)
            d(j, j - 1) -= fluxDiff;
        if (j < d.width() - 1)
            d(j, j + 1) -= fluxDiff;
    }
}

// march function for FVM
template <class T>
void marchFVM(xtGrid<T> &g, double h, double deltaT) {
    difference<T> I(g.width(), 0., 1., 0.);
    for (int j = 0; j < g.width(); j++)
        g(0, j) = Initial(j * h);

    dynamicVector<T> f(g.width());
    difference<T> previous(g.width());
    convDifFVM(previous, f, h, deltaT, 0);

    for (int time = 1; time < g.timeSteps(); time++) {
        difference<T> current(g.width());
        convDifFVM(current, f, h, deltaT, time * deltaT);
        g(time) = ((I - 0.5 * deltaT * previous) * g[time - 1] + deltaT * f) / (I + 0.5 * deltaT * current);
        previous = current;
    }

    print(g[g.timeSteps() - 1]);
}

#endif

