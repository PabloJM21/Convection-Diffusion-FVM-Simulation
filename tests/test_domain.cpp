#include "domain.h"
#include <cassert>

void test_domain_solveConvDif() {
    domain D(10.0, 1.0, 0.1);
    D.solveConvDif();  // Check output or functionality, or print solution
}

int main() {
    test_domain_solveConvDif();
    return 0;
}

