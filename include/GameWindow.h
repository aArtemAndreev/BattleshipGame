#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVector>
#include "Field.h"
#include "ShipItem.h"

class GameWindow : public QWidget {  
public:
    GameWindow(QWidget *parent = nullptr);

    void onShipSelected(ShipItem* ship);
    void onCellClicked(int x, int y);

    ~GameWindow() override = default;

private:
    Field field;
    QVector<ShipItem*> ships;
    ShipItem* selectedShip;
    bool currentOrientation;
    int shipsPlaced;
    
    QPushButton* startButton;
    QPushButton* resetButton;
    QLabel* infoLabel;
    class MyWidget* mapWidget;

private slots: 
    void rotateShips();
    void resetPlacement();
    void goToBattlefield();
};

#endif