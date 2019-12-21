#ifndef MATRIXINPUTWIDGET_H
#define MATRIXINPUTWIDGET_H

#include <QWidget>
#include <QDoubleSpinBox>

class MatrixInputWidget : public QWidget
{
    Q_OBJECT

private:
    QDoubleSpinBox *spinBox;

public:
    explicit MatrixInputWidget(QWidget *parent = nullptr);

private:
    void createLayout();
};

#endif // MATRIXINPUTWIDGET_H
