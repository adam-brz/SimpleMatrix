#ifndef MATRIX_H
#define MATRIX_H

#include <cstring>
#include <cmath>
#include <stdint.h>
#include <initializer_list>

template <typename T> class Matrix
{
private:
    T **matrix = nullptr;
    uint8_t rowCount, columnCount;

public:
    Matrix(std::initializer_list<std::initializer_list<T>> argList);
    Matrix(uint8_t rowCount, uint8_t columnCount);
    Matrix(const Matrix<T> &matrix);
    Matrix(Matrix<T> &&matrix);
    virtual ~Matrix();

    T determinant() const;
    Matrix removeRowAndColumn(uint8_t row, uint8_t column) const;

    void set(uint8_t row, uint8_t column, const T &value)
    {
        matrix[row][column] = value;
    }

    T get(uint8_t row, uint8_t column) const {
        return matrix[row][column];
    }

    uint8_t getRowCount() const {
        return rowCount;
    }

    uint8_t getColumnCount() const {
        return columnCount;
    }

    Matrix &operator=(const Matrix &matrix);
    Matrix &operator=(Matrix &&matrix);
    Matrix &operator-();

    Matrix operator+(const Matrix &matrix) const;
    Matrix operator-(const Matrix &matrix) const;
    Matrix operator*(const Matrix &Matrix) const;
    Matrix operator*(const T& value) const;

private:
    void freeMemory();
    void allocMemory();
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
    allocMemory();
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
void Matrix<T>::allocMemory()
{
    matrix = new T*[rowCount];
    for(int i = 0; i < rowCount; ++i)
    {
        matrix[i] = new T[columnCount];
    }
}

template <typename T>
Matrix<T>::Matrix(Matrix<T> &&matrix)
{
    this->operator=(matrix);
}

template <typename T>
Matrix<T>::~Matrix()
{
    freeMemory();
}

template <typename T>
void Matrix<T>::freeMemory()
{
    if(matrix)
    {
        for(int i = 0; i < rowCount; ++i)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix = nullptr;
    }
}

template <typename T>
T Matrix<T>::determinant() const
{
    if(rowCount == 1 && columnCount == 1)
        return matrix[0][0];

    T sum = 0;   

    for(int i = 0; i < columnCount; ++i)
        sum += matrix[0][i] * pow(-1, i) * removeRowAndColumn(0, i).determinant();

    return sum;
}

template <typename T>
Matrix<T> Matrix<T>::removeRowAndColumn(uint8_t row, uint8_t column) const
{
    Matrix result(rowCount - 1, columnCount - 1);
    uint8_t rowOmmited, columnOmmited;

    rowOmmited = 0;
    for(int i = 0; i < result.getRowCount(); ++i)
    {
        rowOmmited = rowOmmited || (row == i);
        columnOmmited = 0;

        for(int j = 0; j < result.getColumnCount(); ++j)
        {
            columnOmmited = columnOmmited || (column == j);
            result.matrix[i][j] = matrix[i + rowOmmited][j + columnOmmited];
        }
    }

    return result;
}

template <typename T>
Matrix<T> &Matrix<T>::operator-()
{
    for(int i = 0; i < rowCount; ++i)
        for(int j = 0; j < columnCount; ++j)
            set(i , j, -get(i, j));
    return *(this);
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &matrix) const
{
    Matrix<T> result(rowCount, columnCount);

    for(int i = 0; i < rowCount; ++i)
        for(int j = 0; j < columnCount; ++j)
            result.set(i , j, get(i, j) + matrix.get(i, j));

    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &matrix) const
{
    Matrix<T> result(rowCount, columnCount);

    for(int i = 0; i < rowCount; ++i)
        for(int j = 0; j < columnCount; ++j)
            result.set(i , j, get(i, j) - matrix.get(i, j));

    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &matrix) const
{
    Matrix<T> result(getRowCount(), matrix.getColumnCount());
    T sum;

    for(int i = 0; i < rowCount; ++i) {
        sum = 0;
        for(int j = 0; j < columnCount; ++j) {
            sum += get(i, j) * matrix.get(j, i);
        }
        result.set(i, i, sum);
    }

    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const T &value) const
{
    Matrix<T> result(rowCount, columnCount);

    for(int i = 0; i < rowCount; ++i)
        for(int j = 0; j < columnCount; ++j)
            result.set(i, j, get(i, j) * value);

    return result;
}

template <typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix &matrix)
{
   freeMemory();

   columnCount = matrix.columnCount;
   rowCount =  matrix.columnCount;

   allocMemory();
   for(int i = 0; i < rowCount; ++i)
   {
       memcpy(this->matrix[i], matrix.matrix[i], columnCount);
   }

   return *(this);
}

template <typename T>
Matrix<T> &Matrix<T>::operator=(Matrix &&matrix)
{
    freeMemory();

    columnCount = matrix.columnCount;
    rowCount =  matrix.columnCount;

    for(int i = 0; i < rowCount; ++i) {
        this->matrix[i] = matrix.matrix[i];
        for(int j = 0; j < columnCount; ++j) {
            this->matrix[i][j] = matrix.matrix[i][j];
        }
    }

    matrix.matrix = nullptr;
}

#endif // MATRIX_H
