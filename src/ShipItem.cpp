#include "ShipItem.h"
#include "GameWindow.h"
#include <QDebug>

ShipItem::ShipItem(int size, int count, GameWindow* gameWindow, QWidget *parent) : QWidget(parent), ship(size, 0, 0, 0), remaining(count), isSelected(false), gameWindow(gameWindow) {
    setFixedHeight(50);
    setMouseTracking(true);
}

void ShipItem::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    if (isSelected) {
        painter.fillRect(rect(), QColor(52, 152, 219, 50));
    } else {
        painter.fillRect(rect(), QColor(240, 240, 240));
    }

    painter.setPen(Qt::black);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));

    painter.setPen(Qt::black);
    painter.drawText(5, 20, QString("%1-палубный: %2").arg(ship.getSize()).arg(remaining));

    painter.setBrush(Qt::darkGray);
    int startX = 100;
    int startY = 15;

    if (ship.getRotation() == 0) {
        for (int i = 0; i < ship.getSize(); ++i) {
            painter.drawRect(startX + i * 12, startY, 10, 10);
        }
    } else {
        for (int i = 0; i < ship.getSize(); ++i) {
            painter.drawRect(startX, startY + i * 12, 10, 10);
        }
    }
}

void ShipItem::mousePressEvent(QMouseEvent *event) {
    if (remaining > 0) {
        isSelected = true;
        update();
        gameWindow->onShipSelected(this);
    }
}

void ShipItem::setHorizontal(bool horiz) {
    ship.setRotation(horiz ? 0 : 1);
    update();
}

void ShipItem::setSelected(bool selected) {
    isSelected = selected;
    update();
}

void ShipItem::decrement() {
    if (remaining > 0) {
        remaining--;
        update();
    }
}

void ShipItem::setRemaining(int count) {
    remaining = count;
    isSelected = false;
    update();
}

Ship ShipItem::getShipTemplate() const {
    return Ship(ship.getSize(), 0, 0, ship.getRotation());
}