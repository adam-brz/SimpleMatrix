#include "mainwindow.h"
#include <QApplication>

#include <QDebug>
#include "matrix.h"

#define PROGRAM_NAME "MatrixCalc"

void printMatrix(const Matrix<int> &matrix)
{
    for(uint8_t i = 0; i < matrix.getRowCount(); ++i)
    {
        for(uint8_t j = 0; j < matrix.getColumnCount(); ++j)
        {
            qDebug() << matrix.get(i, j);
        }
        qDebug() << "\n";
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(PROGRAM_NAME);
    w.show();

    Matrix<int> matrix = {{1, 2, 3},
                          {4, 5, 6}};

    qDebug() << matrix.getColumnCount();
    qDebug() << matrix.getRowCount();
    qDebug() << matrix.get(1,0) << "\n";

    printMatrix(matrix);

    return 0;//a.exec();
}
