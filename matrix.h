#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>
#include <initializer_list>

template <typename T>
class Vector;

template <typename T = double>
class Matrix
{
private:
    T *matrix = nullptr;
    uint8_t rowCount = 0;
    uint8_t columnCount = 0;

public:
    static Matrix<T> unitMatrix(uint8_t size);
    static Matrix<T> rotationMatrix(const Vector<T> &vector, double angle);
    static Matrix<T> skewSymmetric(const Vector<T> &vector);
    static Matrix<T> fromVector(const Vector<T> &vector);

    Matrix(const std::initializer_list<std::initializer_list<T>> &argList);
    Matrix(uint8_t rowCount = 3, uint8_t columnCount = 3, const T& defaultValue = T());
    Matrix(const Matrix<T> &matrix);
    Matrix(Matrix<T> &&matrix);
    virtual ~Matrix();

    Matrix<T> &transpose();
    Matrix<T> &invert();

    Matrix<T> getTransposed() const;
    Matrix<T> getInversed() const;
    T determinant() const;

    Matrix<T> &round(const T &minimal = 1E-9);
    Matrix<T> &roundToZeroIfNear(const T &maxDelta = 1E-9);
    Matrix<T> &operator=(const Matrix<T> &matrix);
    Matrix<T> &operator=(Matrix<T> &&matrix);

    Matrix<T> operator+(const Matrix<T> &matrix) const;
    Matrix<T> operator-(const Matrix<T> &matrix) const;
    Matrix<T> operator*(const Matrix<T> &matrix) const;
    Matrix<T> operator*(const T &value) const;
    Matrix<T> operator-() const;
    bool operator==(const Matrix<T> &matrix) const;

    inline Matrix<T> &operator+=(const Matrix<T> &matrix) {
        return *this = *this + matrix;
    }

    inline Matrix<T> &operator-=(const Matrix<T> &matrix) {
        return *this = *this - matrix;
    }

    inline Matrix<T> &operator*=(const Matrix<T> &matrix) {
        return *this = *this * matrix;
    }

    inline Matrix<T> &operator*=(const T &value) {
        return *this = *this * value;
    }

    inline void set(uint8_t row, uint8_t column, const T &value)
    {
        matrix[row*getColumnCount() + column] = value;
    }

    inline T &get(uint8_t row, uint8_t column) const {
        return matrix[row*getColumnCount() + column];
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
    void initCells(const T& value = T());

    Matrix<T> removeRowAndColumn(uint8_t row, uint8_t column) const;
    inline T getAlgebraicComplement(uint8_t row, uint8_t column) const;

    inline bool almostEqual(const T &val1, const T &val2, const T &maxDelta) const {
        return abs(val1 - val2) < maxDelta;
    }

    inline bool hasTheSameSize(const Matrix<T> &matrix) const {
        return this->getRowCount() == matrix.getRowCount() &&
                this->getColumnCount() == matrix.getColumnCount();
    }
};

#include "matrix.cpp"

#endif // MATRIX_H
