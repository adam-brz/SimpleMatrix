#include "Tests/catch.hpp"
#include "vector.h"

TEST_CASE("Vector assign tests", "[Vector]")
{
    SECTION("copy by reference")
    {
        Vector<> v = {1, 2};
        Vector<> v2 = v;

        CHECK(v == v2);
    }
}
