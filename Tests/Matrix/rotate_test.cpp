#include "Tests/catch.hpp"
#include "matrix.h"

TEST_CASE("Rotate matrix in x axis", "[Matrix]")
{
    Matrix<> matrix = Matrix<>::unitMatrix(3);
    Matrix<> expected = {{1, 0, 0},
                         {0, 0, -1},
                         {0, 1, 0}};

    CHECK(matrix.rotate(Axis::X, 3.1415/2) == expected);
}
