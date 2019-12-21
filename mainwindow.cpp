#include "mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    inputMatrix1 = new MatrixInputWidget(this);
    createLayout();
}

MainWindow::~MainWindow()
{

}

void MainWindow::createLayout()
{
    QWidget *mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->addWidget(inputMatrix1);
}
