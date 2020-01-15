#include "Tests/catch.hpp"
#include "vector.h"

TEST_CASE("Vector subtraction test", "[Vector]")
{
    SECTION("vector - vector")
    {
        Vector<> v1 = {1, 2, 3};
        Vector<> v2 = {3, 4, 1};

        Vector<> expected = {-2, -2, 2};
        CHECK(v1 - v2 == expected);
    }

    SECTION("vector - vector invalid")
    {
        Vector<> v1 = {1, 2, 3};
        Vector<> v2 = {3, 4};

        CHECK_THROWS_AS(v1 - v2, InvalidMathOperationException);
        CHECK_THROWS_AS(v2 - v1, InvalidMathOperationException);
    }

    SECTION("matrix - vector")
    {
        Vector<> v1({1, 2, 3}, true);
        Matrix<> v2 = {{1}, {5}, {3}};

        Vector<> expected({0, 3, 0}, true);
        CHECK(v2 - v1 == expected);
    }

    SECTION("vector - matrix")
    {
        Vector<> v1({1, 2, 3}, true);
        Matrix<> v2 = {{1}, {5}, {3}};

        Vector<> expected({0, -3, 0}, true);
        CHECK(v1 - v2 == expected);
    }
}
