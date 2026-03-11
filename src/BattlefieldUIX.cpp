#include "BattlefieldUIX.h"
#include <QPainter>
#include <QMouseEvent>

BattlefieldUIX::BattlefieldUIX(Field f, QWidget *parent) : QWidget(parent), field(f) {}

QVector<QPoint> m_points;

void BattlefieldUIX::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(0, 0, 500, 500, QBrush{"#2980b9"});
    for (int i = 1; i <= 9; ++i) {
        painter.drawLine(50 * i, 0, 50 * i, 500);
        painter.drawLine(0, 50 * i, 500, 50 * i);
    }
    for (int i = 1; i < 12; ++i) {
        for (int j = 1; j < 12; ++j) {
            if (field.getCurrentPlace(i, j) == '.') {
                painter.fillRect(50 * (j - 1), 50 * (i - 1), 50, 50, QBrush{Qt::white});
            }
        }
    }
    painter.setPen(QPen(Qt::blue, 3));
    for (const QPoint &point : m_points) {
        int x = point.x();
        int y = point.y();
        painter.fillRect(x - x % 50, y - y % 50, 50, 50, QBrush{Qt::white});
    }
}

void BattlefieldUIX::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_points.append(event->pos());  // Store position
        update();  // Triggers paintEvent
    }
    QWidget::mousePressEvent(event);
}

