#include "Tests/catch.hpp"
#include "vector.h"

#include "matrix.h"
#include "matrixexception.h"

TEST_CASE("Vector from matrix", "[Vector]")
{
    Matrix<> m = {{1}, {2}, {3}};

    REQUIRE(Vector<>::isVector(m));
    CHECK(Vector<>::fromMatrix(m) == Vector<>({1, 2, 3}, true));
}
