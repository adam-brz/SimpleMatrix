#include "Tests/catch.hpp"
#include "vector.h"

TEST_CASE("Vector check if is column vector", "[Vector]")
{
    Vector<> vector({1, 2, 3});
    Vector<> vector2({1, 2, 3}, true);

    CHECK(vector.isColumn() == false);
    CHECK(vector2.isColumn() == true);
}
