#ifndef DEBUGTOOLBOX_H
#define DEBUGTOOLBOX_H

#include "matrix.h"
#include <iostream>

using namespace std;

template <typename T>
void printMatrix(const Matrix<T> &matrix)
{
    Matrix<T> cpy(matrix);
    cpy.roundToZeroIfNear();

    for(uint8_t i = 0; i < cpy.getRowCount(); ++i)
    {
        for(uint8_t j = 0; j < cpy.getColumnCount(); ++j)
            cout << cpy.get(i, j) << " ";
        cout << "\n";
    }
}

#endif // DEBUGTOOLBOX_H
