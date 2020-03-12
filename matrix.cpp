#include "matrix.h"
#include "vector.h"
#include "matrixexception.h"

#include <cstring>
#include <cmath>

template <typename T>
Matrix<T> Matrix<T>::unitMatrix(uint8_t size)
{
    Matrix<T> result(size, size);

    for(int i = 0; i < size; ++i)
        result.set(i, i, 1);

    return result;
}

template<typename T>
Matrix<T> Matrix<T>::rotationMatrix(const Vector<T> &vector, double angle)
{
    Matrix<T> skew_symmetric = Matrix<T>::skewSymmetric(vector);

    return Matrix<T>::unitMatrix(3) +
            skew_symmetric*sin(angle) +
            skew_symmetric*skew_symmetric*(1-cos(angle));
}

template<typename T>
Matrix<T> Matrix<T>::skewSymmetric(const Vector<T> &vector)
{
    T x = vector[0];
    T y = vector[1];
    T z = vector[2];

    return {{0, -z, y},
            {z, 0, -x},
            {-y, x, 0}};
}

template<typename T>
Matrix<T> Matrix<T>::fromVector(const Vector<T> &vector)
{
    return Matrix<T>(vector);
}

template <typename T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>> &argList)
{
    rowCount = argList.size();
    matrix = new T*[rowCount];

    for(int i = 0; i < rowCount; ++i)
    {
        columnCount = argList.begin()[i].size();
        matrix[i] = new T[columnCount];

        for(int j = 0; j < columnCount; ++j)
            matrix[i][j] = argList.begin()[i].begin()[j];
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T> &matrix) :
    Matrix<T>(matrix.rowCount, matrix.columnCount)
{
    for(int i = 0; i < rowCount; ++i)
        memcpy(this->matrix[i], matrix.matrix[i], columnCount*sizeof(T));
}

template <typename T>
Matrix<T>::Matrix(uint8_t rowCount, uint8_t columnCount, const T &defaultValue) :
    rowCount(rowCount),
    columnCount(columnCount)
{
    allocMemory();
    initCells(defaultValue);
}

template <typename T>
void Matrix<T>::allocMemory()
{
    matrix = new T*[rowCount];
    for(int i = 0; i < rowCount; ++i)
        matrix[i] = new T[columnCount];
}

template<typename T>
void Matrix<T>::initCells(const T &value)
{
    for(int i = 0; i < rowCount; ++i)
        for(int j = 0; j < columnCount; ++j)
            matrix[i][j] = value;
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

template<typename T>
Matrix<T> &Matrix<T>::transpose()
{
    *this = Matrix<T>(*this).getTransposed();
    return *this;
}

template<typename T>
Matrix<T> &Matrix<T>::invert()
{
    *this =  Matrix<T>(*this).getInversed();
    return *this;
}

template <typename T>
void Matrix<T>::freeMemory()
{
    if(matrix == nullptr)
        return;

    for(int i = 0; i < rowCount; ++i)
        delete[] matrix[i];

    delete[] matrix;
    matrix = nullptr;
}

template<typename T>
Matrix<T> Matrix<T>::getTransposed() const
{
    Matrix<T> result(columnCount, rowCount);

    for(int i = 0; i < rowCount; ++i)
        for(int j = 0; j < columnCount; ++j)
            result.set(j, i, get(i, j));

    return result;
}

template<typename T>
Matrix<T> Matrix<T>::getInversed() const
{
    Matrix<T> result(rowCount, columnCount);
    T det = determinant();

    for(int i = 0; i < rowCount; ++i)
        for(int j = 0; j < columnCount; ++j)
            result.set(i, j, getAlgebraicComplement(i, j));

    return 1.0/det * result.getTransposed();
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

    for(int i = 0; i < rowCount; ++i)
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
Matrix<T> &Matrix<T>::roundToZeroIfNear(const T &maxDelta)
{
    for(int i = 0; i < rowCount; ++i)
        for(int j = 0; j < columnCount; ++j)
            if(almostEqual(get(i, j), 0, maxDelta))
                set(i, j, T());

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
    if(!canBeMultiplied(matrix))
        throw InvalidMathOperationException();

    Matrix<T> result(getRowCount(), matrix.getColumnCount());
    T quotientsSum = 0;

    for(int row = 0; row < getRowCount(); ++row)
    {
        for(int column = 0; column < matrix.getColumnCount(); ++column)
        {
            for(int i = 0; i < getColumnCount(); ++i)
                quotientsSum += get(row, i) * matrix.get(i, column);

            result.set(row, column, quotientsSum);
            quotientsSum = 0;
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
   rowCount = matrix.rowCount;

   allocMemory();

   for(int i = 0; i < rowCount; ++i)
       memcpy(this->matrix[i], matrix.matrix[i], columnCount*sizeof(T));

   return *(this);
}

template <typename T>
Matrix<T> &Matrix<T>::operator=(Matrix &&matrix)
{
    freeMemory();

    columnCount = matrix.columnCount;
    rowCount =  matrix.rowCount;

    this->matrix = matrix.matrix;
    matrix.matrix = nullptr;

    return (*this);
}

template <typename T>
bool Matrix<T>::operator==(const Matrix<T> &matrix) const
{
    constexpr double MAX_CMP_DELTA = 1E-9;

    if(!hasTheSameSize(matrix))
        return false;

    for(int i = 0; i < rowCount; ++i)
        for(int j = 0; j < columnCount; ++j)
            if(!almostEqual(get(i, j), matrix.get(i, j), MAX_CMP_DELTA))
                return false;

    return true;
}
