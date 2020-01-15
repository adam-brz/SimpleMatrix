#include "vector.h"
#include "matrix.h"
#include "matrixexception.h"

#include <algorithm>

template<typename T>
bool Vector<T>::isVector(const Matrix<T> &matrix)
{
    if(matrix.getRowCount() == 1 || matrix.getColumnCount() == 1)
        return true;
    return false;
}

template<typename T>
Vector<T> Vector<T>::fromMatrix(const Matrix<T> &matrix)
{
    Vector<T> vector(0);
    *(vector.matrix) = matrix;
    vector.vector_size = std::max(matrix.getRowCount(), matrix.getColumnCount());
    vector.isColumnVector = matrix.getRowCount() > matrix.getColumnCount();

    return vector;
}

template<typename T>
Vector<T>::Vector(const std::initializer_list<T> &argList, bool isColumnVector) :
    vector_size(argList.size()),
    isColumnVector(isColumnVector)
{
    matrix = new Matrix<T>(1, vector_size);

    for(int i = 0; i < vector_size; ++i)
        matrix->set(0, i, argList.begin()[i]);

    if(isColumnVector)
        matrix->transpose();
}

template<typename T>
Vector<T>::Vector(int size, const T &default_value, bool isColumnVector) :
    vector_size(size),
    isColumnVector(isColumnVector)
{
    int i = 1;
    int j = vector_size;

    if(isColumnVector)
        std::swap(i, j);

    matrix = new Matrix<T>(i, j, default_value);
}

template<typename T>
Vector<T>::Vector(const Vector<T> &vector) :
    vector_size(vector.size()),
    isColumnVector(vector.isColumn())
{
    matrix = new Matrix<>(*(vector.matrix));
}

template<typename T>
Vector<T>::Vector(Vector<T> &&vector) :
    matrix(vector.matrix),
    vector_size(vector.size()),
    isColumnVector(vector.isColumn())
{
    vector.matrix = nullptr;
    vector.vector_size = 0;
}

template<typename T>
Vector<T>::~Vector()
{
    delete matrix;
}

template<typename T>
int Vector<T>::size() const
{
    return vector_size;
}

template<typename T>
bool Vector<T>::isColumn() const
{
    return isColumnVector;
}

template<typename T>
T Vector<T>::abs() const
{
    T result = T();

    for(int i = 0; i < size(); ++i)
        result += std::pow((*this)[i], 2);

    return std::sqrt(result);
}

template<typename T>
T &Vector<T>::operator[](int i)
{
    int j = 0;

    if(isColumnVector)
        std::swap(i, j);

    return matrix->get(j, i);
}

template<typename T>
const T &Vector<T>::operator[](int i) const
{
    int j = 0;

    if(isColumnVector)
        std::swap(i, j);

    return matrix->get(j, i);
}

template<typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &vector)
{
    *matrix = *(vector.matrix);
    vector_size = vector.size();
    isColumnVector = vector.isColumn();
    return *this;
}

template<typename T>
Vector<T> &Vector<T>::operator=(Vector<T> &&vector)
{
    matrix = vector.matrix;
    vector_size = vector.size();
    isColumnVector = vector.isColumn();

    vector.matrix = nullptr;
    vector.vector_size = 0;

    return *this;
}

template<typename T>
Vector<T> Vector<T>::operator+(const Vector<T> &vector) const
{
    return Vector<T>::fromMatrix(static_cast<Matrix<T>>(*this) + vector);
}

template<typename T>
Matrix<T> Vector<T>::operator+(const Matrix<T> &matrix) const
{
    return static_cast<Matrix<T>>(*this) + matrix;
}

template<typename T>
Vector<T> Vector<T>::operator-(const Vector<T> &vector) const
{
    return fromMatrix(static_cast<Matrix<T>>(*this) - vector);
}

template<typename T>
Matrix<T> Vector<T>::operator-(const Matrix<T> &matrix) const
{
    return static_cast<Matrix<T>>(*this) - matrix;
}

template<typename T>
Matrix<T> Vector<T>::operator*(const Matrix<T> &vector) const
{
    return static_cast<Matrix<T>>(*this) * vector;
}

template<typename T>
Vector<T> Vector<T>::operator*(const T &value) const
{
    return fromMatrix(static_cast<Matrix<T>>(*this) * value);
}

template<typename T>
Vector<T> Vector<T>::operator-() const
{
    Vector<T> result(*this);
    *result.matrix = -(*result.matrix);
    return result;
}

template<typename T>
bool Vector<T>::operator==(const Vector<T> &vector) const
{
    if(vector_size != vector.size() || (isColumn() ^ vector.isColumn()))
        return false;

    for(int i = 0; i < vector_size; ++i)
        if((*this)[i] != vector[i])
            return false;

    return true;
}

template<typename T>
Vector<T>::operator const Matrix<T> &() const
{
    return *matrix;
}
