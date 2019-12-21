#ifdef RUN_TEST

#include "Tests/catch.hpp"
#include "matrix.h"

TEST_CASE("Initializing empty matrix", "[Matrix]")
{
    Matrix<> matrix(0, 0);

    CHECK(matrix.getColumnCount() == 0);
    CHECK(matrix.getRowCount() == 0);

    CHECK(matrix.hasDeterminant() == true);
    CHECK(matrix.isInvertible() == false);
}


#endif //RUN_TEST
