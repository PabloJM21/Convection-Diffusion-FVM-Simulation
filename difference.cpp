#include "difference.h"

// Compute flux for convection-diffusion at a control volume face
template<class T>
T difference<T>::flux(T phiL, T phiR, T D, T u) {
    T convectiveFlux = u * ((u > 0) ? phiL : phiR);
    T diffusiveFlux = D * (phiR - phiL);
    return convectiveFlux + diffusiveFlux;
}

// Implement other methods (constructor, operator overloads, etc.)

// Constructor: initializes tridiagonal matrix with specified values
template<class T>
difference<T>::difference(int n, const T& a, const T& b, const T& c) {
    number = 3; // number of diagonals in tridiagonal matrix
    item = new dynamicVector<T>*[number];
    item[0] = new dynamicVector<T>(n, a); // lower diagonal
    item[1] = new dynamicVector<T>(n, b); // main diagonal
    item[2] = new dynamicVector<T>(n, c); // upper diagonal
}

// Add a difference matrix to the current one
template<class T>
const difference<T>& difference<T>::operator+=(const difference<T>& d) {
    for (int i = 0; i < number; i++) {
        *item[i] += *d.item[i];
    }
    return *this;
}

// Subtract a difference matrix from the current one
template<class T>
const difference<T>& difference<T>::operator-=(const difference<T>& d) {
    for (int i = 0; i < number; i++) {
        *item[i] -= *d.item[i];
    }
    return *this;
}

// Multiply the difference matrix by a scalar
template<class T>
const difference<T>& difference<T>::operator*=(const T& scalar) {
    for (int i = 0; i < number; i++) {
        *item[i] *= scalar;
    }
    return *this;
}

// Add two difference matrices
template<class T>
const difference<T> operator+(const difference<T>& d1, const difference<T>& d2) {
    return difference<T>(d1) += d2;
}

// Subtract two difference matrices
template<class T>
const difference<T> operator-(const difference<T>& d1, const difference<T>& d2) {
    return difference<T>(d1) -= d2;
}

// Scalar multiplication
template<class T>
const difference<T> operator*(const T& scalar, const difference<T>& d) {
    return difference<T>(d) *= scalar;
}
template<class T>
const difference<T> operator*(const difference<T>& d, const T& scalar) {
    return difference<T>(d) *= scalar;
}

template<class T>
const dynamicVector<T> operator*(const difference<T>& d, const dynamicVector<T>& v) {
    dynamicVector<T> dv(v.dim(), 0.0);
    for (int i = 0; i < v.dim(); i++) {
        for (int j = std::max(0, i - 1); j <= std::min(v.dim() - 1, i + 1); j++) {
            dv(i) += d(i, j, "read") * v[j];
        }
    }
    return dv;
}

template<class T>
const dynamicVector<T> operator/(const dynamicVector<T>& f, const difference<T>& d) {
    dynamicVector<T> x(f);
    for (int iteration = 0; iteration < 100; iteration++) { // 100 iterations for approximate solution
        for (int i = 0; i < f.dim(); i++) {
            T residual = f[i];
            for (int j = std::max(0, i - 1); j <= std::min(f.dim() - 1, i + 1); j++) {
                if (i != j) {
                    residual -= d(i, j, "read") * x[j];
                }
            }
            x(i) += residual / d(i, i, "read");
        }
    }
    return x;
}

