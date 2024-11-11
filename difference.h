#ifndef DIFFERENCE_H
#define DIFFERENCE_H

#include "dynamicVector.h"
#include <list>
#include <algorithm>

template <class T>
class difference : public std::list<dynamicVector<T>> {
public:
    difference(int n = 0, const T &a = 0, const T &b = 0, const T &c = 0) {
        this->resize(3);
        (*this)[0] = dynamicVector<T>(n, a);
        (*this)[1] = dynamicVector<T>(n, b);
        (*this)[2] = dynamicVector<T>(n, c);
    }

    const difference<T> &operator+=(const difference<T> &d) {
        for (int i = 0; i < 3; i++)
            (*this)[i] += d[i];
        return *this;
    }

    const difference<T> &operator-=(const difference<T> &d) {
        for (int i = 0; i < 3; i++)
            (*this)[i] -= d[i];
        return *this;
    }

    const difference<T> &operator*=(const T &t) {
        for (int i = 0; i < 3; i++)
            (*this)[i] *= t;
        return *this;
    }

    T &operator()(int i, int j) { return (*this)[j - i + 1][i]; }
    const T &operator()(int i, int j, char *) const { return (*this)[j - i + 1][i]; }

    int width() const { return (*this)[0].dim(); }
};

template <class T>
const difference<T> operator+(const difference<T> &d1, const difference<T> &d2) {
    return difference<T>(d1) += d2;
}

template <class T>
const difference<T> operator-(const difference<T> &d1, const difference<T> &d2) {
    return difference<T>(d1) -= d2;
}

template <class T>
const difference<T> operator*(const T &t, const difference<T> &d) {
    return difference<T>(d) *= t;
}

template <class T>
const difference<T> operator*(const difference<T> &d, const T &t) {
    return difference<T>(d) *= t;
}

template <class T>
const dynamicVector<T> operator*(const difference<T> &d, const dynamicVector<T> &v) {
    dynamicVector<T> dv(v.dim(), 0.);
    for (int i = 0; i < v.dim(); i++) {
        for (int j = std::max(0, i - 1); j <= std::min(v.dim() - 1, i + 1); j++) {
            dv(i) += d(i, j, "read") * v[j];
        }
    }
    return dv;
}

template <class T>
const dynamicVector<T> operator/(const dynamicVector<T> &f, const difference<T> &d) {
    dynamicVector<T> x(f);
    for (int iteration = 0; iteration < 100; iteration++) {
        for (int i = 0; i < f.dim(); i++) {
            double residual = f[i];
            for (int j = std::max(0, i - 1); j <= std::min(f.dim() - 1, i + 1); j++)
                residual -= d(i, j, "read") * x[j];
            x(i) += residual / d(i, i, "read");
        }
    }
    return x;
}

#endif
