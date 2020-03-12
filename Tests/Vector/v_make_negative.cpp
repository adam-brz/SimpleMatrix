#include "Tests/catch.hpp"
#include "vector.h"

TEST_CASE("Vector creating negative", "[Vector]")
{
    Vector<> vector = {1, 2, 3};

    CHECK(-vector == Vector<>({-1, -2, -3}));
}
