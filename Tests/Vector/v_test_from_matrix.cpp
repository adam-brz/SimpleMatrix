#include "Tests/catch.hpp"
#include "vector.h"

#include "matrix.h"
#include "matrixexception.h"

TEST_CASE("Vector from matrix", "[Vector]")
{
    SECTION("Column vector")
    {
        Matrix<> matrix = {{1}, {2}, {3}};
        REQUIRE(Vector<>::isVector(matrix));

        Vector<> vector = Vector<>::fromMatrix(matrix);

        CHECK(vector == Vector<>({1, 2, 3}, VectorType::ColumnVector));
        CHECK(vector.isColumn());
    }

    SECTION("Row vector")
    {
        Matrix<> matrix = {{1, 2, 3}};
        REQUIRE(Vector<>::isVector(matrix));

        Vector<> vector = Vector<>::fromMatrix(matrix);

        CHECK(vector == Vector<>({1, 2, 3}));
        CHECK(vector.isColumn() == false);
    }
}
