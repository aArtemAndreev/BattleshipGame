#ifndef SHIPITEM_H
#define SHIPITEM_H

#include "Ship.h"
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class GameWindow;

class ShipItem : public QWidget {
    private:
        Ship ship;
        bool isSelected;
        int remaining;

    public:
        ShipItem(int size, int count, GameWindow* gameWindow, QWidget *parent = nullptr);

        void paintEvent(QPaintEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void setHorizontal(bool horiz);
        void setSelected(bool selected);
        void decrement();
        int getSize() const { return ship.getSize(); }
        bool isHorizontal() const { return ship.getRotation() == 0; }
        bool canPlace() const { return remaining > 0; }
        Ship getShipTemplate() const;
        void setRemaining(int count);

        ~ShipItem() override = default;
    private:
        GameWindow* gameWindow;
};

#endif