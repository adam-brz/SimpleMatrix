#ifdef RUN_TEST

#include "Tests/catch.hpp"
#include "matrix.h"

TEST_CASE("Multiplying matrixes", "[Matrix]")
{
    Matrix<> mat1 = {{0, -2},
                     {1, 3},
                     {2, -4}};

    Matrix<> mat2 = {{-2, 7},
                     {-1, 3}};

    Matrix<> expected1 = {{2, -6},
                          {-5, 16},
                          {0, 2}};

    Matrix<> mat3 = {{2, 0, 3},
                     {2, 0, 4},
                     {1, 3, 0}};

    Matrix<> expected2 = {{4, 0, 6},
                          {4, 0, 8},
                          {2, 6, 0}};

    SECTION("Invalid operand matrixes size") {
        REQUIRE_FALSE(mat1.canBeMultiplied(mat3));
        REQUIRE_FALSE(mat2.canBeMultiplied(mat3));

        REQUIRE_THROWS_AS(mat1 * mat3, InvalidMathOperationException);
        REQUIRE_THROWS_AS(mat2 * mat3, InvalidMathOperationException);
    }

    SECTION("Valid matrix * matrix") {
        REQUIRE(mat1.canBeMultiplied(mat2));
        REQUIRE(mat3.canBeMultiplied(expected1));

        REQUIRE(mat1 * mat2 == expected1);
        REQUIRE_NOTHROW(mat3 * expected1);
    }

    SECTION("Valid matrix*number") {
        REQUIRE(mat3.canBeMultiplied(2));
        REQUIRE(mat3 * 2 == expected2);
    }
}

#endif
