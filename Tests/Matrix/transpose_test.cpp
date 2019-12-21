#ifdef RUN_TEST

#include "Tests/catch.hpp"
#include "matrix.h"

TEST_CASE("Transposing matrixes", "[Matrix]")
{
    Matrix<> mat1 = {{1}};
    Matrix<> mat1_expected = {{1}};

    Matrix<> mat2 = {{2, 3}};
    Matrix<> mat2_expected = {{2},
                              {3}};

    Matrix<> mat3 = {{1, 5},
                     {8, 3}};
    Matrix<> mat3_expected = {{1, 8},
                              {5, 3}};

    Matrix<> mat4 = {{1, 2},
                     {2, 3},
                     {4, 5}};

    Matrix<> mat4_expected = {{1, 2, 4},
                              {2, 3, 5}};

    REQUIRE(mat1.getTransposed() == mat1_expected);
    REQUIRE(mat2.getTransposed() == mat2_expected);
    REQUIRE(mat3.getTransposed() == mat3_expected);
    REQUIRE(mat4.getTransposed() == mat4_expected);
}
#endif
