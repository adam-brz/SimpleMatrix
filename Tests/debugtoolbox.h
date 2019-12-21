#ifndef DEBUGTOOLBOX_H
#define DEBUGTOOLBOX_H

#include "matrix.h"
#include <iostream>

using namespace std;

template <typename T>
void printMatrix(const Matrix<T> &matrix)
{
    for(uint8_t i = 0; i < matrix.getRowCount(); ++i)
    {
        for(uint8_t j = 0; j < matrix.getColumnCount(); ++j)
        {
            cout << matrix.get(i, j) << " ";
        }
        cout << "\n";
    }
}

#endif // DEBUGTOOLBOX_H
