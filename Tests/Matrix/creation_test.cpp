#ifdef RUN_TEST

#include "Tests/catch.hpp"
#include "matrix.h"

TEST_CASE("Initializing empty matrix", "[Matrix]")
{
    SECTION("Matrix with 0 columns and rows")
    {
        Matrix<> matrix(0, 0);

        CHECK(matrix.getColumnCount() == 0);
        CHECK(matrix.getRowCount() == 0);

        CHECK(matrix.hasDeterminant() == true);
        CHECK(matrix.isInvertible() == false);
    }

    SECTION("Initialization with initializer list")
    {
        Matrix<> matrix = {};

        CHECK(matrix.getColumnCount() == 0);
        CHECK(matrix.getRowCount() == 0);

        CHECK(matrix.hasDeterminant() == true);
        CHECK(matrix.isInvertible() == false);
    }

    SECTION("Making copy of empty matrix")
    {
        Matrix<> original(0, 0);
        Matrix<> matrix = original;

        CHECK(matrix.getColumnCount() == 0);
        CHECK(matrix.getRowCount() == 0);

        CHECK(matrix.hasDeterminant() == true);
        CHECK(matrix.isInvertible() == false);
    }

    SECTION("Making copy of empty matrix")
    {
        Matrix<> original(0, 0);
        Matrix<> matrix = original;

        CHECK(matrix.getColumnCount() == 0);
        CHECK(matrix.getRowCount() == 0);

        CHECK(matrix.hasDeterminant() == true);
        CHECK(matrix.isInvertible() == false);
    }

    SECTION("Moving empty matrix")
    {
        Matrix<> origin = Matrix<>(0, 0);
        Matrix<> matrix = std::move(origin);

        CHECK(matrix.getColumnCount() == 0);
        CHECK(matrix.getRowCount() == 0);

        CHECK(matrix.hasDeterminant() == true);
        CHECK(matrix.isInvertible() == false);
    }
}


#endif //RUN_TEST
