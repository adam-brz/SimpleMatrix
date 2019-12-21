#ifdef RUN_TEST

#include "Tests/catch.hpp"
#include "matrix.h"

TEST_CASE("Comparing matrixes", "[Matrix]")
{
    Matrix<> mat1 = {{1, 2, 3},
                     {1, 3, 1}};

    Matrix<> mat2 = {{1, 2, 3},
                     {1, 3, 1}};

    Matrix<> mat3 = {{1, 6, 3},
                     {0, 3, -1},
                     {0, -2, -4}};

    Matrix<> mat4 = {{1, 6, 3},
                     {0, 3, -1},
                     {0, -2, -4}};

    REQUIRE(mat1 == mat2);
    REQUIRE(mat3 == mat4);

    REQUIRE_FALSE(mat1 == mat3);
    REQUIRE_FALSE(mat2 == mat4);
}

#endif
