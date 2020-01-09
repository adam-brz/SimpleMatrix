#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>

template <typename T>
class Matrix;

template <typename T = double>
class Vector
{
    Matrix<T> *matrix = nullptr;
    int vector_size = 0;
    bool isColumnVector;

public:
    static bool isVector(const Matrix<T> &matrix);
    static Vector<T> fromMatrix(const Matrix<T> &matrix);

    Vector(const std::initializer_list<T> &argList, bool isColumnVector = false);
    Vector(int size, const T& default_value = T(), bool isColumnVector = false);
    Vector(const Vector<T> &vector);
    Vector(const Matrix<T> &matrix);
    Vector(Vector<T> &&vector);
    virtual ~Vector();

    int size() const;
    bool isColumn() const;

    T &operator[](int i);
    const T &operator[](int i) const;

    Vector<T> &operator=(const Vector<T> &matrix);
    Vector<T> &operator=(Vector<T> &&vector);

    Vector<T> operator+(const Vector<T> &matrix) const;
    Matrix<T> operator+(const Matrix<T> &matrix) const;
    /*Vector<T> operator-(const Vector<T> &matrix) const;
    Vector<T> operator*(const Vector<T> &matrix) const;
    Vector<T> operator*(const T &value) const;
    Vector<T> operator-() const;*/
    bool operator==(const Vector<T> &matrix) const;
    operator const Matrix<T>&() const;

    friend Matrix<T>;
};

#include "vector.cpp"

#endif // VECTOR_H
