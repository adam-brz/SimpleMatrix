#include "mainwindow.h"
#include <QApplication>

#include <QDebug>
#include <iostream>

using namespace std;

#include "matrix.h"

#define PROGRAM_NAME "MatrixCalc"

void printMatrix(const Matrix<int> &matrix)
{
    for(uint8_t i = 0; i < matrix.getRowCount(); ++i)
    {
        for(uint8_t j = 0; j < matrix.getColumnCount(); ++j)
        {
            cout << matrix.get(i, j) << " ";
        }
        cout << "\n";
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*MainWindow w;
    w.setWindowTitle(PROGRAM_NAME);
    w.show();*/

    Matrix<int> matrix = {{1, 3},
                          {2, 4}
                         };

    Matrix<int> mat2 = {{5, 7},
                        {6, 8}
                       };

    printMatrix( mat2 * matrix);

    //qDebug() << matrix.determinant();
    return 0;//a.exec();
}
