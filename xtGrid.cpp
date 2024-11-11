#include "xtGrid.h"

// Constructor: Initializes the grid as a list of dynamic vectors
template<class T>
xtGrid<T>::xtGrid(int m, int n, const T& a) {
    // Allocate `m` time levels, each containing a vector of `n` spatial points initialized to `a`
    number = m;  // Number of time levels
    item = m ? new dynamicVector<T>*[m] : nullptr;  // Allocate array of pointers
    for (int i = 0; i < m; i++) {
        item[i] = new dynamicVector<T>(n, a);  // Each time level holds a vector of `n` elements
    }
}

// Destructor: Cleans up allocated memory
template<class T>
xtGrid<T>::~xtGrid() {
    for (int i = 0; i < number; i++) {
        delete item[i];
    }
    delete[] item;
}

// Returns the number of time steps (i.e., the number of time levels)
template<class T>
int xtGrid<T>::timeSteps() const {
    return number;
}

// Returns the width of the grid in the x-direction (i.e., the number of spatial points)
template<class T>
int xtGrid<T>::width() const {
    return item[0]->dim();
}

// Access operator for time levels (read/write)
template<class T>
dynamicVector<T>& xtGrid<T>::operator()(int i) {
    if (i >= 0 && i < number) {
        return *item[i];
    }
    throw std::out_of_range("Invalid time level index.");
}

// Access operator for individual grid points (read/write)
template<class T>
T& xtGrid<T>::operator()(int i, int j) {
    if (i >= 0 && i < number && j >= 0 && j < item[i]->dim()) {
        return (*item[i])(j);
    }
    throw std::out_of_range("Invalid grid point index.");
}

// Print function to output the final time level values (for debugging or analysis)
template<class T>
void xtGrid<T>::printFinalTimeLevel() const {
    for (int j = 0; j < width(); j++) {
        std::cout << (*item[timeSteps() - 1])(j) << " ";
    }
    std::cout << std::endl;
}

