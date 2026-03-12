#include "GameWindow.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>
#include "MyWidget.h"
#include "Battlefield.h"
#include "PlacementShipsBot.h"

GameWindow::GameWindow(QWidget *parent) : QWidget(parent), selectedShip(nullptr), currentOrientation(true) {
    setWindowTitle("Морской бой");
    setFixedSize(800, 600);
    
    QHBoxLayout* layout = new QHBoxLayout(this);
    
    QWidget* leftPanel = new QWidget(this);
    
    leftPanel->setFixedWidth(200);

    QVBoxLayout* leftLayout = new QVBoxLayout(leftPanel);

    QPushButton* rotateButton = new QPushButton("Повернуть", this);
    rotateButton->setFixedSize(150, 30);
    connect(rotateButton, &QPushButton::clicked, this, &GameWindow::rotateShips);
    leftLayout->addWidget(rotateButton);

    ShipItem* ship4 = new ShipItem(4, 1, this, this);
    ships.append(ship4);
    leftLayout->addWidget(ship4);

    ShipItem* ship3 = new ShipItem(3, 2, this, this);
    ships.append(ship3);
    leftLayout->addWidget(ship3);

    ShipItem* ship2 = new ShipItem(2, 3, this, this);
    ships.append(ship2);
    leftLayout->addWidget(ship2);

    ShipItem* ship1 = new ShipItem(1, 4, this, this);
    ships.append(ship1);
    leftLayout->addWidget(ship1);

    leftLayout->addStretch();
    
    QPushButton* startButton = new QPushButton("Начать игру", this);
    startButton->setFixedSize(150, 50);

    connect(startButton, &QPushButton::clicked, this, &GameWindow::goToBattlefield);

    leftLayout->addWidget(startButton);
    leftLayout->addStretch();

    MyWidget* mapWidget = new MyWidget(field, this, this);
    mapWidget->setFixedSize(500, 500);

    layout->addWidget(leftPanel);
    layout->addWidget(mapWidget);
}

void GameWindow::rotateShips() {
    currentOrientation = !currentOrientation;
    for (ShipItem* ship : ships) {
        ship->setHorizontal(currentOrientation);
    }
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (btn) {
        btn->setText(currentOrientation ? "Гориз" : "Верт");
    }
}

void GameWindow::onShipSelected(ShipItem* ship) {
    if (selectedShip) {
        selectedShip->setSelected(false);
    }

    selectedShip = ship;
}

void GameWindow::onCellClicked(int x, int y) {
    qDebug() << "Клик по клетке:" << x << y;
}

void GameWindow::goToBattlefield() {
    // временно
    auto a = PlacementShipsBot::randomGenerator();
    bool isok = false;
    while (!isok) {
        a = PlacementShipsBot::randomGenerator();
        if (a.has_value()) isok = true;
    }
    auto b = PlacementShipsBot::randomGenerator();
    isok = false;
    while (!isok) {
        b = PlacementShipsBot::randomGenerator();
        if (b.has_value()) isok = true;
    }
    // временно
    BattlefieldWindow* bw = new BattlefieldWindow(this, *a, *b);

    bw->show();
    this->close();
}