#include <iostream>
#include <chrono>
#include <cmath>
#include <tuple>

#include "matrix.h"

using namespace std;
using namespace std::chrono;

constexpr int NO_REPEATS = 10000;

void test_time_det()
{
    Matrix<> testMatrix = {{1, 5, 4},
                            {-2, 5, 6},
                            {1, -3, 9}};

    for(int i = 0; i < NO_REPEATS; ++i)
        testMatrix.determinant();
}
void test_time_inverse()
{
    Matrix<> testMatrix = {{1, 5, 4},
                            {-2, 5, 6},
                            {1, -3, 9}};

    for(int i = 0; i < NO_REPEATS; ++i)
        testMatrix.getInversed();
}
void test_time_add()
{
    Matrix<> testMatrix1 = {{1, 5, 4},
                            {-2, 5, 6},
                            {1, -3, 9}};

    Matrix<> testMatrix2 = {{1, 5, -4},
                            {-2, 1, 2},
                            {1, -3, -3}};

    for(int i = 0; i < NO_REPEATS; ++i)
        testMatrix1 + testMatrix2;
}
void test_time_sub()
{
    Matrix<> testMatrix1 = {{1, 5, 4},
                            {-2, 5, 6},
                            {1, -3, 9}};

    Matrix<> testMatrix2 = {{1, 5, -4},
                            {-2, 1, 2},
                            {1, -3, -3}};

    for(int i = 0; i < NO_REPEATS; ++i)
        testMatrix1 - testMatrix2;
}
void test_time_multiply()
{
    Matrix<> testMatrix1 = {{1, 5, 4},
                            {-2, 5, 6},
                            {1, -3, 9}};

    Matrix<> testMatrix2 = {{1, 5, -4},
                            {-2, 1, 2},
                            {1, -3, -3}};

    for(int i = 0; i < NO_REPEATS; ++i)
        testMatrix1 * testMatrix2;
}

template <typename FUNC>
double get_exec_time(FUNC func)
{
    auto start = system_clock::now();
    func();
    auto end = system_clock::now();

    duration<double> func_exec_time = end - start;
    return func_exec_time.count();
}

int main()
{
    auto funcTable = {make_pair(test_time_det, "determinant"),
                     make_pair(test_time_inverse, "inverse"),
                     make_pair(test_time_add, "operator+"),
                     make_pair(test_time_sub, "operator-"),
                     make_pair(test_time_multiply, "operator*")};

    auto mainStart = system_clock::now();

    for(auto func : funcTable)
    {
        double timeSum = 0;

        for(int i = 0; i < 10; ++i)
            timeSum += get_exec_time(func.first);

        cout << "> Function \"" << func.second << "\"" << endl
             << "Time averange: " << timeSum / 10.0 << endl << endl;
    }

    duration<double> elapsed_time = system_clock::now() - mainStart;
    cout << endl << "Total time: " << elapsed_time.count() << endl;

    return 0;
}

