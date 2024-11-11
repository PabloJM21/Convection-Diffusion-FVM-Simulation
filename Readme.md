# Convection-Diffusion Solver

This project implements a semi-implicit numerical solver for the convection-diffusion equation using the semi-implicit time-marching scheme.

## Features
- Customizable grid and accuracy settings
- Numerical solution output at final time `t=10`
- Modular structure with extensible classes for future enhancements

## Project Structure

convection-diffusion-solver ├── README.md # Project overview, usage, and instructions ├── LICENSE # License file (e.g., MIT License) ├── src │ ├── main.cpp # Main program entry point │ ├── domain.h # Definition of the domain class │ ├── domain.cpp # Implementation of domain functions │ ├── xtGrid.h # Definition of xtGrid class │ ├── xtGrid.cpp # Implementation of xtGrid functions │ ├── difference.h # Definition of difference class │ ├── difference.cpp # Implementation of difference functions │ ├── utilities.h # Utility functions (e.g., F, G, C, Alpha, Initial) │ └── utilities.cpp # Implementation of utility functions ├── tests │ └── test_domain.cpp # Unit tests for the domain class └── CMakeLists.txt # Build configuration for CMake



# Derivation of the Finite Volume Method Equation from the Convection-Diffusion PDE

This file explains the step-by-step process of obtaining the Finite Volume Method (FVM) equation for a convection-diffusion problem starting from the partial differential equation (PDE) form.

## Step 1: Start with the Convection-Diffusion PDE

Consider the general form of the **convection-diffusion equation** in 1D:

$$
\frac{\partial u}{\partial t} + \frac{\partial}{\partial x} (c u) = \frac{\partial}{\partial x} \left( D \frac{\partial u}{\partial x} \right)
$$

where:
- \( u(x, t) \) is the unknown field variable (e.g., concentration),
- \( c \) is the convection coefficient,
- \( D \) is the diffusion coefficient.

This equation describes the combined effects of convection (movement of \( u \) with velocity \( c \)) and diffusion (spreading of \( u \) with diffusivity \( D \)).

## Step 2: Divide the Domain into Control Volumes

To apply the **Finite Volume Method**, divide the spatial domain into discrete, non-overlapping control volumes, each centered at points \( x_i \). Let the control volume around \( x_i \) span from \( x_{i-1/2} \) to \( x_{i+1/2} \), with \( x_{i-1/2} \) and \( x_{i+1/2} \) representing the left and right faces of the control volume.

## Step 3: Integrate the PDE over a Control Volume

Integrate the convection-diffusion PDE over the control volume \([x_{i-1/2}, x_{i+1/2}]\):

$$
\int_{x_{i-1/2}}^{x_{i+1/2}} \left( \frac{\partial u}{\partial t} + \frac{\partial}{\partial x} (c u) - \frac{\partial}{\partial x} \left( D \frac{\partial u}{\partial x} \right) \right) \, dx = 0
$$

Expanding this gives three integral terms:

$$
\int_{x_{i-1/2}}^{x_{i+1/2}} \frac{\partial u}{\partial t} \, dx + \int_{x_{i-1/2}}^{x_{i+1/2}} \frac{\partial}{\partial x} (c u) \, dx - \int_{x_{i-1/2}}^{x_{i+1/2}} \frac{\partial}{\partial x} \left( D \frac{\partial u}{\partial x} \right) \, dx = 0
$$

## Step 4: Simplify Using the Divergence Theorem

Using the **divergence theorem** (or fundamental theorem of calculus in 1D) to convert spatial derivatives into flux terms across control volume faces:

1. For the **convection term**:

   $$
   \int_{x_{i-1/2}}^{x_{i+1/2}} \frac{\partial}{\partial x} (c u) \, dx = (c u)_{i+1/2} - (c u)_{i-1/2}
   $$

2. For the **diffusion term**:

   $$
   \int_{x_{i-1/2}}^{x_{i+1/2}} \frac{\partial}{\partial x} \left( D \frac{\partial u}{\partial x} \right) \, dx = \left( D \frac{\partial u}{\partial x} \right)_{i+1/2} - \left( D \frac{\partial u}{\partial x} \right)_{i-1/2}
   $$

Now the integrated PDE becomes:

$$
\int_{x_{i-1/2}}^{x_{i+1/2}} \frac{\partial u}{\partial t} \, dx + (c u)_{i+1/2} - (c u)_{i-1/2} - \left( D \frac{\partial u}{\partial x} \right)_{i+1/2} + \left( D \frac{\partial u}{\partial x} \right)_{i-1/2} = 0
$$

## Step 5: Approximate the Terms in the Discretized Equation

### Time Derivative Term

Assuming a uniform grid spacing \( \Delta x = x_{i+1/2} - x_{i-1/2} \), the average time derivative over the control volume is:

$$
\int_{x_{i-1/2}}^{x_{i+1/2}} \frac{\partial u}{\partial t} \, dx \approx \Delta x \frac{\partial u_i}{\partial t}
$$

### Convection Flux Term

The convection fluxes at the control volume faces are approximated as:

$$
(c u)_{i+1/2} \text{ and } (c u)_{i-1/2}
$$

These can be further discretized depending on the upwind or central differencing scheme used.

### Diffusion Flux Term

The diffusion fluxes at the faces are:

$$
\left( D \frac{\partial u}{\partial x} \right)_{i+1/2} \text{ and } \left( D \frac{\partial u}{\partial x} \right)_{i-1/2}
$$

Using finite differences, approximate these by:

$$
\left( D \frac{\partial u}{\partial x} \right)_{i+1/2} \approx D \frac{u_{i+1} - u_i}{\Delta x}
$$

$$
\left( D \frac{\partial u}{\partial x} \right)_{i-1/2} \approx D \frac{u_i - u_{i-1}}{\Delta x}
$$

## Step 6: Combine Terms to Obtain the FVM Discretized Equation

Substitute the approximations back into the integrated equation:

$$
\Delta x \frac{\partial u_i}{\partial t} + (c u)_{i+1/2} - (c u)_{i-1/2} - D \frac{u_{i+1} - 2 u_i + u_{i-1}}{\Delta x} = 0
$$

Dividing by \( \Delta x \), the final **Finite Volume Method

