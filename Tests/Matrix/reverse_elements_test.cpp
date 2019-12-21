#ifdef RUN_TEST

#include "Tests/catch.hpp"
#include "matrix.h"

TEST_CASE("Reverse matrix elements", "[Matrix]")
{
    Matrix<> mat1 = {{1}};
    Matrix<> mat1_expected = {{-1}};

    Matrix<> mat2 = {{1}, {2}, {3}};
    Matrix<> mat2_expected = {{-1}, {-2}, {-3}};

    Matrix<> mat3 = {{1, -2, 3},
                     {2, 3, 4},
                     {3, -4, 5}};

    Matrix<> mat3_expected = {{-1, 2, -3},
                              {-2, -3, -4},
                              {-3, 4, -5}};

    REQUIRE(-mat1 == mat1_expected);
    REQUIRE(-mat2 == mat2_expected);
    REQUIRE(-mat3 == mat3_expected);
}

#endif
