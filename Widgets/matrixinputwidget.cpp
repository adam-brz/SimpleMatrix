#include "matrixinputwidget.h"
#include <QGridLayout>

MatrixInputWidget::MatrixInputWidget(QWidget *parent) : QWidget(parent)
{
    spinBox = new QDoubleSpinBox(this);
    createLayout();
}

void MatrixInputWidget::createLayout()
{
    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(spinBox, 0, 0);
}
