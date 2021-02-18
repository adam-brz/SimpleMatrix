#include "Tests/catch.hpp"
#include "matrix.h"
#include "Axis.h"

#define _USE_MATH_DEFINES
#include <cmath>

TEST_CASE("Rotate matrix in x axis", "[Matrix]")
{
    Matrix<> expected = {{1, 0, 0},
                         {0, 0, -1},
                         {0, 1, 0}};

    CHECK(Matrix<>::rotationMatrix(Axis<>::X(), M_PI/2.0) == expected);
}

TEST_CASE("Rotate matrix in y axis", "[Matrix]")
{
    Matrix<> expected = {{0, 0, 1},
                         {0, 1, 0},
                         {-1, 0, 0}};

    CHECK(Matrix<>::rotationMatrix(Axis<>::Y(), M_PI/2.0) == expected);
}

TEST_CASE("Rotate matrix in z axis", "[Matrix]")
{
    Matrix<> expected = {{0, -1, 0},
                         {1, 0, 0},
                         {0, 0, 1}};

    CHECK(Matrix<>::rotationMatrix(Axis<>::Z(), M_PI/2.0) == expected);
}
