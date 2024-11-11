# Convection-Diffusion Solver

This project implements a semi-implicit numerical solver for the convection-diffusion equation using the semi-implicit time-marching scheme.

## Features
- Customizable grid and accuracy settings
- Numerical solution output at final time `t=10`
- Modular structure with extensible classes for future enhancements

##Project Structure

convection-diffusion-solver
├── README.md               # Project overview, usage, and instructions
├── LICENSE                 # License file (e.g., MIT License)
├── src
│   ├── main.cpp            # Main program entry point
│   ├── domain.h            # Definition of the `domain` class
│   ├── domain.cpp          # Implementation of `domain` functions
│   ├── xtGrid.h            # Definition of `xtGrid` class
│   ├── xtGrid.cpp          # Implementation of `xtGrid` functions
│   ├── difference.h        # Definition of `difference` class
│   ├── difference.cpp      # Implementation of `difference` functions
│   ├── utilities.h         # Utility functions (e.g., F, G, C, Alpha, Initial)
│   └── utilities.cpp       # Implementation of utility functions
├── tests
│   └── test_domain.cpp     # Unit tests for the `domain` class
└── CMakeLists.txt          # Build configuration for CMake


## Getting Started

### Prerequisites
- C++17 or newer
- CMake 3.10 or newer

### Installation
```bash
git clone https://github.com/yourusername/convection-diffusion-solver.git
cd convection-diffusion-solver
mkdir build
cd build
cmake ..
make
