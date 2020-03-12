#include "Tests/catch.hpp"
#include "vector.h"

TEST_CASE("Vector creation test", "[Vector]")
{
    Vector<> vector = {1, 2, 3};
    Vector<> vector2({1, 2, 3}, VectorType::ColumnVector);

    CHECK(vector.size() == 3);
    CHECK(vector2.size() == 3);
}
