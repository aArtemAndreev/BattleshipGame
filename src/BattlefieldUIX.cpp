#include "BattlefieldUIX.h"
#include <QPainter>
#include <QMouseEvent>

BattlefieldUIX::BattlefieldUIX(Field f, std::shared_ptr<bool> whoseStep, QWidget *parent) : QWidget(parent), field(f), whoseStep(whoseStep) {}

QVector<QPoint> m_points;

void BattlefieldUIX::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(0, 0, 500, 500, QBrush{"#2980b9"});
    for (int i = 1; i <= 9; ++i) {
        painter.drawLine(50 * i, 0, 50 * i, 500);
        painter.drawLine(0, 50 * i, 500, 50 * i);
    }
    painter.setPen(QPen(Qt::blue, 3));
    for (const QPoint &point : m_points) {
        int x = point.x();
        int y = point.y();
        x -= x % 50;
        y -= y % 50;
        if (field.getCurrentPlace(y / 50 + 1, x / 50 + 1) == '.') {
            painter.fillRect(x, y, 50, 50, QBrush{Qt::white});
            painter.drawLine(x, y, x + 50, y + 50);
        } else {
            painter.fillRect(x, y, 50, 50, QBrush{Qt::blue});
        }
    }
}

void BattlefieldUIX::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_points.append(event->pos());
        update();
    }
    QWidget::mousePressEvent(event);
    *whoseStep = true;
}

