#include "Tests/catch.hpp"
#include "matrix.h"

TEST_CASE("Inversing matrixes", "[Matrix]")
{
    Matrix<> mat2x2 = {{2, -1},
                       {9, 2}};

    Matrix<> mat3x3 = {{2, -1, 0},
                       {1, 3, -2},
                       {1, 0, 7}};

    Matrix<> I_2x2 = {{1, 0},
                      {0, 1}};

    Matrix<> I_3x3 = {{1, 0, 0},
                      {0, 1, 0},
                      {0, 0, 1}};

    Matrix<> invalid = {{2, 3, 0},
                        {1, 0, 2}};

    SECTION("Check invert possibility") {
        REQUIRE(mat2x2.isInvertible());
        REQUIRE(mat3x3.isInvertible());
    }

    SECTION("Non square matrixes are not invertible") {
        REQUIRE_FALSE(invalid.isInvertible());
        REQUIRE_THROWS_AS(invalid.getInversed(), InvalidDeterminantException);
    }

    SECTION("Inverse matrix") {
        REQUIRE(mat2x2.getInversed() * mat2x2 == I_2x2);
        REQUIRE(mat3x3.getInversed() * mat3x3 == I_3x3);
    }
}

