#include "Tests/debugtoolbox.h"

#include "matrix.h"
#include "vector.h"

int main()
{
    Matrix<> matrix = {{1, 2, 3}};

    Vector<>::isVector(matrix);

    Vector<> vector = Vector<>::fromMatrix(matrix);

     printMatrix(Matrix<>::fromVector(vector));
}
