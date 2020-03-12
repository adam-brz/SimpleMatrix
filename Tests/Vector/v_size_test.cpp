#include "Tests/catch.hpp"
#include "vector.h"

TEST_CASE("Vector get size", "[Vector]")
{
    CHECK(Vector<>({}).size() == 0);
    CHECK(Vector<>({1}).size() == 1);
    CHECK(Vector<>({1, 2, 3, 5}).size() == 4);
}
