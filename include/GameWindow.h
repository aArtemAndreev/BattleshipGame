#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QVector>
#include "Field.h"
#include "MyWidget.h"
#include "ShipItem.h"

class GameWindow : public QWidget {  
public:
    GameWindow(QWidget *parent = nullptr);
    void onShipSelected(ShipItem* ship);
    void onCellClicked(int x, int y);
private:
    Field field;
    MyWidget* mapWidget;
    QVector<ShipItem*> ships;
    ShipItem* selectedShip;
    bool currentOrientation;
    QLabel* infoLabel;
    int shipsPlaced;
    QPushButton* startButton;
private slots:
    void goToBattlefield();
    void rotateShips();
};

#endif