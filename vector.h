#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>

template <typename T>
class Matrix;

enum class VectorType : unsigned char {
    RowVector    = 0,
    ColumnVector = 1
};

template <typename T = double>
class Vector
{
    Matrix<T> *matrix = nullptr;
    int vector_size = 0;
    bool isColumnVector;

public:
    static bool isVector(const Matrix<T> &matrix);
    static Vector<T> fromMatrix(const Matrix<T> &matrix);

    Vector(const std::initializer_list<T> &argList,
           VectorType vectorType = VectorType::RowVector);

    Vector(int size = 3,
           const T& default_value = T(),
           VectorType vectorType = VectorType::RowVector);

    Vector(const Vector<T> &vector);
    Vector(Vector<T> &&vector);
    virtual ~Vector();

    int size() const;
    bool isColumn() const;
    T abs() const;

    Vector<T> &round(const T &minimum = 1E-9);
    Vector<T> &transpose();

    T &operator[](int i);
    const T &operator[](int i) const;

    Vector<T> &operator=(const Vector<T> &matrix);
    Vector<T> &operator=(Vector<T> &&vector);

    Vector<T> operator+(const Vector<T> &vector) const;
    Matrix<T> operator+(const Matrix<T> &matrix) const;

    Vector<T> operator-(const Vector<T> &vector) const;
    Matrix<T> operator-(const Matrix<T> &matrix) const;

    Matrix<T> operator*(const Matrix<T> &vector) const;
    Vector<T> operator*(const T &value) const;
    Vector<T> operator/(const T &value) const;
    Vector<T> operator-() const;

    Vector<T> &operator*=(const T &value);
    Vector<T> &operator/=(const T &value);
    Vector<T> &operator+=(const Vector<T> &vector);
    Vector<T> &operator-=(const Vector<T> &vector);

    bool operator==(const Vector<T> &matrix) const;
    operator const Matrix<T>&() const;

    friend Vector<T> operator*(const T &value,
                               const Vector<T> &vector)
    {
        return vector * value;
    }
};

#include "vector.cpp"

#endif // VECTOR_H
