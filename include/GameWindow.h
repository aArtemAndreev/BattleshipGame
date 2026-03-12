#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QVector>
#include "Field.h"
#include "MyWidget.h"
#include "ShipItem.h"

class GameWindow : public QWidget {  
public:
    GameWindow(QWidget *parent = nullptr);
    void onShipSelected(ShipItem* ship);

private:
    Field field;
    MyWidget* mapWidget;
    QVector<ShipItem*> ships;
    ShipItem* selectedShip;
    bool currentOrientation;
private slots:
    void goToBattlefield();
    void rotateShips();
    void onCellClicked(int x, int y);
};

#endif