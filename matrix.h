#ifndef MATRIX_H
#define MATRIX_H

#include "matrixexception.h"

#include <cstring>
#include <cmath>
#include <stdint.h>
#include <initializer_list>

template <typename T = double> class Matrix
{
private:
    T **matrix = nullptr;
    uint8_t rowCount, columnCount;

public:
    Matrix(const std::initializer_list<std::initializer_list<T>> &argList);
    Matrix(uint8_t rowCount, uint8_t columnCount);
    Matrix(const Matrix<T> &matrix);
    Matrix(Matrix<T> &&matrix);
    virtual ~Matrix();

    Matrix<T> getTransposed() const;
    Matrix<T> getInversed() const;
    T determinant() const;

    Matrix<T> &normalizeValues(int prec = 9);
    Matrix<T> &operator=(const Matrix<T> &matrix);
    Matrix<T> &operator=(Matrix<T> &&matrix);

    Matrix<T> operator+(const Matrix<T> &matrix) const;
    Matrix<T> operator-(const Matrix<T> &matrix) const;
    Matrix<T> operator*(const Matrix<T> &matrix) const;
    Matrix<T> operator*(const T& value) const;
    Matrix<T> operator-() const;
    bool operator==(const Matrix<T> &matrix) const;

    inline void set(uint8_t row, uint8_t column, const T &value)
    {
        matrix[row][column] = value;
    }

    inline T get(uint8_t row, uint8_t column) const {
        return matrix[row][column];
    }

    inline uint8_t getRowCount() const {
        return rowCount;
    }

    inline uint8_t getColumnCount() const {
        return columnCount;
    }

    inline bool hasDeterminant() const {
        return rowCount == columnCount;
    }

    inline bool isInvertible() const {
        if(hasDeterminant())
            return determinant() != 0;
        return false;
    }

    inline bool canBeMultiplied(const Matrix<T> &matrix) const {
        return this->getColumnCount() == matrix.getRowCount();
    }

    inline bool canBeMultiplied(const T &) const {
        return true;
    }

    inline friend Matrix<T> operator*(const T &value, const Matrix<T> &matrix) {
        return matrix * value;
    }
private:
    void freeMemory();
    void allocMemory();

    Matrix<T> removeRowAndColumn(uint8_t row, uint8_t column) const;
    inline T getAlgebraicComplement(uint8_t row, uint8_t column) const;

    inline bool hasTheSameSize(const Matrix<T> &matrix) const {
        return this->getRowCount() == matrix.getRowCount() &&
                this->getColumnCount() == matrix.getColumnCount();
    }
};

template <typename T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>> &argList)
{
    int i = 0, j;

    matrix = new T*[argList.size()];
    rowCount = argList.size();

    for(const auto &columns : argList)
    {
        matrix[i] = new T[columns.size()];
        columnCount = columns.size();

        j = 0;
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
    memcpy(this->matrix, matrix.matrix, rowCount*columnCount*sizeof(T));
}

template <typename T>
void Matrix<T>::allocMemory()
{
    matrix = new T*[rowCount];
    for(int i = 0; i < rowCount; ++i)
        matrix[i] = new T[columnCount];
}

template <typename T>
Matrix<T>::Matrix(Matrix<T> &&matrix) :
    matrix(matrix.matrix),
    rowCount(matrix.rowCount),
    columnCount(matrix.columnCount)
{
    matrix.matrix = nullptr;
    matrix.rowCount = 0;
}

template <typename T>
Matrix<T>::~Matrix()
{
    freeMemory();
}

template <typename T>
void Matrix<T>::freeMemory()
{
    if(matrix != nullptr)
    {
        for(int i = 0; i < rowCount; ++i)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix = nullptr;
    }
}

template<typename T>
Matrix<T> Matrix<T>::getTransposed() const
{
    Matrix<T> result(columnCount, rowCount);

    for(int i = 0; i < rowCount; ++i)
        for(int j = 0; j < columnCount; ++j)
            result.set(j, i, this->get(i, j));

    return result;
}

template<typename T>
Matrix<T> Matrix<T>::getInversed() const
{
    Matrix<T> result(rowCount, columnCount);
    T det = determinant();

    for(int i = 0; i < rowCount; ++i)
        for(int j = 0; j < columnCount; ++j)
            result.set(i, j, getAlgebraicComplement(i,j));

    return (static_cast<T>(1.0)/det * result.getTransposed());
}

template <typename T>
inline T Matrix<T>::getAlgebraicComplement(uint8_t row, uint8_t column) const
{
    return pow(-1, row+column) * removeRowAndColumn(row, column).determinant();
}

template <typename T>
T Matrix<T>::determinant() const
{
    if(rowCount != columnCount)
        throw InvalidDeterminantException();

    if(rowCount == 1)
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

    for(int i = 0; i < result.getRowCount(); ++i) {
        rowOmmited = rowOmmited || (row == i);
        columnOmmited = 0;

        for(int j = 0; j < result.getColumnCount(); ++j) {
            columnOmmited = columnOmmited || (column == j);
            result.matrix[i][j] = matrix[i + rowOmmited][j + columnOmmited];
        }
    }

    return result;
}

template <typename T>
Matrix<T> &Matrix<T>::normalizeValues(int prec)
{
    const double treshold = std::pow(10, -prec);

    for(int i = 0; i < rowCount; ++i)
        for(int j = 0; j < columnCount; ++j)
            if(std::abs(this->get(i, j)) < treshold)
                set(i, j, 0);

    return (*this);
}

template <typename T>
Matrix<T> Matrix<T>::operator-() const
{
    Matrix<T> result(rowCount, columnCount);

    for(int i = 0; i < rowCount; ++i)
        for(int j = 0; j < columnCount; ++j)
            result.set(i, j, -get(i, j));
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &matrix) const
{
    if(!this->hasTheSameSize(matrix))
        throw InvalidMathOperationException();

    Matrix<T> result(rowCount, columnCount);

    for(int i = 0; i < rowCount; ++i)
        for(int j = 0; j < columnCount; ++j)
            result.set(i , j, get(i, j) - matrix.get(i, j));

    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &matrix) const
{
    if(!this->hasTheSameSize(matrix))
        throw InvalidMathOperationException();

    Matrix<T> result(rowCount, columnCount);

    for(int i = 0; i < rowCount; ++i)
        for(int j = 0; j < columnCount; ++j)
            result.set(i, j, get(i, j) + matrix.get(i, j));

    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &matrix) const
{
    if(this->getColumnCount() != matrix.getRowCount())
        throw InvalidMathOperationException();

    Matrix<T> result(getRowCount(), matrix.getColumnCount());

    T tmpSum;
    for(int row = 0; row < this->getRowCount(); ++row) {
        for(int column = 0; column < matrix.getColumnCount(); ++column) {
            tmpSum = 0;
            for(int i = 0; i < this->getColumnCount(); ++i) {
                tmpSum += this->get(row, i) * matrix.get(i, column);
            }
            result.set(row, column, tmpSum);
        }
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
   memcpy(this->matrix, matrix.matrix, rowCount*columnCount*sizeof(T));
   return *(this);
}

template <typename T>
Matrix<T> &Matrix<T>::operator=(Matrix &&matrix)
{
    freeMemory();

    columnCount = matrix.columnCount;
    rowCount =  matrix.columnCount;

    this->matrix = matrix.matrix;
    matrix.matrix = nullptr;

    return (*this);
}

template <typename T>
bool Matrix<T>::operator==(const Matrix<T> &matrix) const
{
    constexpr double MAX_CMP_DELTA = 0.0000000001; // = 10^(-10)

    if(!hasTheSameSize(matrix))
        return false;

    for(int i = 0; i < rowCount; ++i)
        for(int j = 0; j < columnCount; ++j)
            if(std::abs(this->get(i, j) - matrix.get(i, j)) > MAX_CMP_DELTA)
                return false;

    return true;
}


#endif // MATRIX_H
