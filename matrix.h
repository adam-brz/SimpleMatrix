#ifndef MATRIX_H
#define MATRIX_H

#include <cstring>
#include <stdint.h>
#include <initializer_list>

template <typename T> class Matrix
{
private:
    T **matrix;
    uint8_t rowCount, columnCount;

public:
    Matrix(std::initializer_list<std::initializer_list<T>> argList);
    Matrix(uint8_t rowCount, uint8_t columnCount);
    Matrix(const Matrix<T> &matrix);

    virtual ~Matrix();

    T determinant() const;
    Matrix removeRowAndColumn(uint8_t row, uint8_t column);

    T get(uint8_t row, uint8_t column) const;

    uint8_t getRowCount() const {
        return rowCount;
    }

    uint8_t getColumnCount() const {
        return columnCount;
    }
};

template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> argList)
{
    int i = 0;

    matrix = new T*[argList.size()];
    rowCount = argList.size();

    for(const auto &columns : argList)
    {
        matrix[i] = new T[columns.size()];
        columnCount = columns.size();

        int j = 0;
        for(const auto &value : columns)
        {
            matrix[i][j] = value;
            ++j;
        }
        ++i;
    }
}

template <typename T>
Matrix<T>::Matrix(uint8_t rowCount, uint8_t columnCount) :
    rowCount(rowCount),
    columnCount(columnCount)
{
    matrix = new T*[rowCount];
    for(int i = 0; i < rowCount; ++i)
    {
        matrix[i] = new T[columnCount];
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T> &matrix) :
    Matrix<T>(matrix.rowCount, matrix.columnCount)
{
    for(int i = 0; i < rowCount; ++i)
    {
        memcpy(this->matrix[i], matrix.matrix[i], columnCount);
    }
}

template <typename T>
Matrix<T>::~Matrix()
{
    if(matrix)
    {
        for(int i = 0; i < rowCount; ++i)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
}

template <typename T>
T Matrix<T>::determinant() const
{
    T sum = 0;

    for(int i = 0; i < columnCount; ++i)
    {
        sum += matrix[0][i];
    }
}

template <typename T>
Matrix<T> Matrix<T>::removeRowAndColumn(uint8_t row, uint8_t column)
{
    Matrix result(rowCount - 1, columnCount - 1);


}

template <typename T>
T Matrix<T>::get(uint8_t row, uint8_t column) const
{
    return matrix[row][column];
}

#endif // MATRIX_H
