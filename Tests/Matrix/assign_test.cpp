#include "Tests/catch.hpp"
#include "matrix.h"
#include "Tests/debugtoolbox.h"

TEST_CASE("Assign by reference")
{
    Matrix<> matrix(1, 1);
    Matrix<> matrix2 = {{1, 2, 0},
                       {2, 1, 1},
                       {0, 1, 0}};

    matrix = matrix2;
    CHECK(matrix == matrix2);
}

TEST_CASE("Assign by move schematic")
{
    Matrix<> matrix(1, 1);
    Matrix<> matrix2 = {{1, 2, 0},
                       {2, 1, 1},
                       {0, 1, 0}};

    matrix = {{1, 2, 0},
              {2, 1, 1},
              {0, 1, 0}};


    CHECK(matrix == matrix2);
}
