#ifdef RUN_TEST

#include "Tests/catch.hpp"
#include "matrix.h"

TEST_CASE("Matrix determinant calculations", "[matrix]") {
    SECTION("Possible to determine") {
        double det0 = Matrix<double>({{10}}).determinant();

        double det1 = Matrix<double>({{2, 4},
                                      {-1, 5}}).determinant();

        double det2 = Matrix<double>({{3, 0, -5},
                                      {2, 5, 1},
                                      {7, 4, -3}}).determinant();

        double det3 = Matrix<double>({{-1,  0,  2, -3},
                                      { 0,  1, -2,  1},
                                      { 1, -4,  0,  2},
                                      {-3,  1,  1,  0}}).determinant();

        double det4 = Matrix<double>({{3,  0,  0, 0, 0},
                                      {3,  1,  0, 0, 0},
                                      {2, 12,  3, 0, 0},
                                      {3, -6, 19, -2, 0},
                                      {3, 31,  3, 0, -5}}).determinant();

        REQUIRE(det0 == 10.0);
        REQUIRE(det1 == 14.0);
        REQUIRE(det2 == 78.0);
        REQUIRE(det3 == 39.0);
        REQUIRE(det4 == 90.0);

    }

    SECTION("Impossible to determine"){
        Matrix<double> matrix1 = {{1, 3}};

        Matrix<double> matrix2 = {{1, 3, 2},
                                  {2, 8, 1}};

        Matrix<double> matrix3 = {{1, 3},
                                  {2, 3},
                                  {0, 1}};

        Matrix<double> matrix4 = {{1, 3, 2}};

        REQUIRE_THROWS_AS(matrix1.determinant(), InvalidDeterminantException);
        REQUIRE_THROWS_AS(matrix2.determinant(), InvalidDeterminantException);
        REQUIRE_THROWS_AS(matrix3.determinant(), InvalidDeterminantException);
        REQUIRE_THROWS_AS(matrix4.determinant(), InvalidDeterminantException);
    }
}

TEST_CASE("Checking possibility of calculating determinant", "[matrix]")
{
    REQUIRE(Matrix<double>({{10}}).hasDeterminant());

    REQUIRE(Matrix<double>({{10 ,4},
                            {12, 6}}).hasDeterminant());

    REQUIRE(Matrix<double>({{10, 2, 1},
                            {0, 4, -1},
                            {0, -4, 1}}).hasDeterminant());


    REQUIRE_FALSE(Matrix<double>({{10, 3}}).hasDeterminant());

    REQUIRE_FALSE(Matrix<double>({{10, 1},
                                  {13, 2},
                                  {2, 5}}).hasDeterminant());

    REQUIRE_FALSE(Matrix<double>({{10, 1, 2},
                                  {19, 17, 1}}).hasDeterminant());

}

#endif
