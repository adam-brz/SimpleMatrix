#include "Tests/catch.hpp"
#include "vector.h"
#include <cmath>

TEST_CASE("Vector getting vector length", "[Vector]")
{
    Vector<> v = {1, 1, 1};
    Vector<> v2 = {0.5, 0.5};

    CHECK(v.abs() == Approx(std::sqrt(3)));
    CHECK(v2.abs() == Approx(1/std::sqrt(2)));
}
