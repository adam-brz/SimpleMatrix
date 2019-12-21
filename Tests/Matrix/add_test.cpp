#ifdef RUN_TEST

#include "Tests/catch.hpp"
#include "matrix.h"

TEST_CASE("Adding matrixes", "[Matrix]")
{
    Matrix<> mat1 = {{1, 2, 3},
                     {2, 3, 4}};

    Matrix<> mat2 = {{2, 0, 3},
                     {2, 0, 4}};

    Matrix<> mat3 = {{2, 0, 3},
                     {2, 0, 4},
                     {1, 3, 0}};

    Matrix<> mat4 = {{-4, 0, 3},
                     {1, -2, 4},
                     {1, 3, 0}};

    Matrix<> expected1 = {{3, 2, 6},
                          {4, 3, 8}};

    Matrix<> expected2 = {{-2, 0, 6},
                          {3, -2, 8},
                          {2, 6, 0}};

    SECTION("Invalid operand matrixes size") {
        REQUIRE_THROWS_AS(mat1 + mat3, InvalidMathOperationException);
        REQUIRE_THROWS_AS(mat1 + mat4, InvalidMathOperationException);
    }

    SECTION("Valid operations") {
        REQUIRE(mat1 + mat2 == expected1);
        REQUIRE(mat3 + mat4 == expected2);
    }
}

#endif
