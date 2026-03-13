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
    Field getPlayerField() const { 
        return field; 
    }
private:
    Field field;
    MyWidget* mapWidget;
    QVector<ShipItem*> ships;
    ShipItem* selectedShip;
    bool currentOrientation;
    QLabel* infoLabel;
    int shipsPlaced;
    QPushButton* startButton;
    QPushButton* resetButton;
private slots:
    void goToBattlefield();
    void rotateShips();
    void resetPlacement();
};

#endif