#ifndef MATRIXEXCEPTION_H
#define MATRIXEXCEPTION_H

#include <exception>

class InvalidDeterminantException : public std::exception
{
    virtual const char* what() const noexcept {
        return "Cannot calculate determinant from non square matrix.";
    }
};

#endif // MATRIXEXCEPTION_H
