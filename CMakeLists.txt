cmake_minimum_required(VERSION 3.10)
project(ConvectionDiffusionSolver)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(convection_diffusion_solver srcmain.cpp srcdomain.cpp srcxtGrid.cpp srcdifference.cpp srcutilities.cpp)
