#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Widgets/matrixinputwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    MatrixInputWidget *inputMatrix1;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createLayout();
};

#endif // MAINWINDOW_H
