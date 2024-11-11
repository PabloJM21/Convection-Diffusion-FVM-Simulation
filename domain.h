#ifndef DOMAIN_H
#define DOMAIN_H

#include "xtGrid.h"
#include "difference.h"
#include "utilities.h"

class domain {
    xtGrid<double> g;
    double Time;
    double Width;

public:
    domain(double T, double L, double accuracy)
        : g((int)(T / accuracy) + 1, (int)(L / accuracy) + 1), Time(T), Width(L) {}

    void solveConvDif() {
        marchFVM(g, Width / g.width(), Time / g.timeSteps());
    }
};

#endif
