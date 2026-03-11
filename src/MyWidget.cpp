#include "MyWidget.h"
#include <QPainter>

MyWidget::MyWidget(Field f, QWidget *parent) : QWidget(parent), field(f) {}

void MyWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    
    painter.fillRect(0, 0, 500, 500, QBrush("#2980b9"));
    
    painter.setPen(Qt::black);
    for (int i = 1; i <= 9; i++) {
        painter.drawLine(50 * i, 0, 50 * i, 500);
        painter.drawLine(0, 50 * i, 500, 50 * i);
    }
}