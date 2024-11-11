#include "domain.h"

int main(){
    domain D(10.0, 1.0, 0.1);  // Define the domain with T=10, L=1, accuracy=0.1
    D.solveConvDif();           // Solve and print the solution
    return 0;
}
