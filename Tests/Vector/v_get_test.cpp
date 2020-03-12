#include "Tests/catch.hpp"
#include "vector.h"

TEST_CASE("Vector get element test", "[Vector]")
{
    Vector<> vector({1, 2, 3});
    Vector<> vector2({1, 2, 3}, VectorType::ColumnVector);

    CHECK(vector[0] == Approx(1));
    CHECK(vector[1] == Approx(2));
    CHECK(vector2[2] == Approx(3));
    CHECK(vector2[2] == Approx(vector[2]));
}
