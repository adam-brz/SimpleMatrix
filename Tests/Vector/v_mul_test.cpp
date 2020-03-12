#include "Tests/catch.hpp"
#include "vector.h"

TEST_CASE("Vector multiplication test", "[Vector]")
{
    SECTION("vector * vector")
    {
        Vector<> v1 = {1, 2, 3};
        Vector<> v2({3, 4, 1}, VectorType::ColumnVector);

        Matrix<> expected = {{3, 6, 9},
                             {4, 8, 12},
                             {1, 2, 3}};

        CHECK(v2 * v1 == expected);
    }

    SECTION("vector * vector invalid")
    {
        Vector<> v1 = {1, 2, 3};
        Vector<> v2 = {3, 4};

        CHECK_THROWS_AS(v1 * v2, InvalidMathOperationException);
        CHECK_THROWS_AS(v2 * v1, InvalidMathOperationException);
    }

    SECTION("matrix * vector")
    {
        Matrix<> matrix = {{2, 1, 0},
                           {1, 1, 1},
                           {4, 4, 2}};

        Vector<> vector({1, 1, 1}, VectorType::ColumnVector);
        Vector<> expected({3, 3, 10}, VectorType::ColumnVector);

        CHECK(matrix * vector == expected);
    }

    SECTION("vector * matrix")
    {
        Matrix<> matrix = {{2, 1},
                           {1, 1}};

        Vector<> vector = {1, 2};
        Vector<> expected = {4, 3};

        CHECK(vector * matrix == expected);
    }

    SECTION("vector * value")
    {
        Vector<> vector = {1, 2, 4};
        CHECK(vector * 2 == Vector<>({2, 4, 8}));
    }

    SECTION("value * vector")
    {
        Vector<> vector = {1, 2, 4};
        CHECK(2 * vector == Vector<>({2, 4, 8}));
    }
}
