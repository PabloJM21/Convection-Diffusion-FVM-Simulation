#ifndef XTGRID_H
#define XTGRID_H

#include "dynamicVector.h"
#include <list>

template <class T>
class xtGrid : public std::list<dynamicVector<T>> {
public:
    xtGrid(int m = 0, int n = 0, const T &a = 0) {
        this->resize(m);
        for (auto &vec : *this)
            vec = dynamicVector<T>(n, a);
    }

    int timeSteps() const { return this->size(); }
    int width() const { return this->front().dim(); }

    dynamicVector<T> &operator()(int i) { return (*this)[i]; }
    T &operator()(int i, int j) { return (*this)[i][j]; }
};

#endif
