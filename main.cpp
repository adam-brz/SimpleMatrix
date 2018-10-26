#include "mainwindow.h"
#include <QApplication>

#include "Tests/debugtoolbox.h"

#define PROGRAM_NAME "MatrixCalc"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*MainWindow w;
    w.setWindowTitle(PROGRAM_NAME);
    w.show();*/

    Matrix<int> matrix = {{2,  1, 0},
                          {3, -2, 1}
                         };

    Matrix<int> mat2 = {{0, -2},
                        {1,  3},
                        {2, -4}
                       };

    printMatrix(matrix * mat2);

    return 0;//a.exec();
}
