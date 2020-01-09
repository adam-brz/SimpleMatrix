#include "Tests/debugtoolbox.h"

#include "matrix.h"
#include "vector.h"

int main()
{
    Matrix<> m = {{1}, {2}, {3}};
    Vector<> v = Vector<>::fromMatrix(m);
    cout << v.isColumn() << endl;
    printMatrix(Matrix<>(m));
}
