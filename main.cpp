#include "mainwindow.h"
#include <QApplication>

#include "Tests/debugtoolbox.h"

#define PROGRAM_NAME "MatrixCalc"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(PROGRAM_NAME);
    w.show();

    return a.exec();
}
