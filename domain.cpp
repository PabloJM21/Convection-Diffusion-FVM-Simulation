#include "domain.h"
#include "utilities.h"

domain::domain(double T, double L, double accuracy)
    : g(static_cast<int>(T/accuracy) + 1, static_cast<int>(L/accuracy) + 1), Time(T), Width(L) {}

void domain::solveConvDif() {
    march(g, Width / g.width(), Time / g.timeSteps());
}
