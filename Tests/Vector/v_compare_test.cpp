#include "Tests/catch.hpp"
#include "vector.h"

TEST_CASE("Vector comparation", "[Vector]")
{
    CHECK(Vector<>({}) == Vector<>({}));
    CHECK(Vector<>({1}) == Vector<>({1}));
    CHECK(Vector<>({1, 2, 0}) == Vector<>({1, 2, 0}));
    CHECK_FALSE(Vector<>({1, 2, 0}) == Vector<>({1, 2}));
    CHECK_FALSE(Vector<>({1, 2, 0}) == Vector<>({1, 2, 1}));

    CHECK_FALSE(Vector<>({1, 2, 0}) == Vector<>({1, 2, 0}, VectorType::ColumnVector));
    CHECK(Vector<>({1, 2, 0}, VectorType::ColumnVector) == Vector<>({1, 2, 0}, VectorType::ColumnVector));
}
