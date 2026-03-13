#include "GameWindow.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>
#include "MyWidget.h"
#include "Battlefield.h"
#include "PlacementShipsBot.h"

GameWindow::GameWindow(QWidget *parent) : QWidget(parent), selectedShip(nullptr), currentOrientation(true), shipsPlaced(0) {
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

    resetButton = new QPushButton("Сброс", this);
    resetButton->setFixedSize(150, 30);
    connect(resetButton, &QPushButton::clicked, this, &GameWindow::resetPlacement);
    leftLayout->addWidget(resetButton);

    infoLabel = new QLabel("Выбери корабль", this);
    infoLabel->setWordWrap(true);
    infoLabel->setStyleSheet("color: #2c3e50; font-weight: bold;");
    leftLayout->addWidget(infoLabel);

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
    
    startButton = new QPushButton("Начать игру", this);
    startButton->setFixedSize(150, 50);
    startButton->setEnabled(false);

    connect(startButton, &QPushButton::clicked, this, &GameWindow::goToBattlefield);

    leftLayout->addWidget(startButton);
    leftLayout->addStretch();

    mapWidget = new MyWidget(field, this, this);
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

    if (selectedShip) {
        selectedShip->setSelected(false);
        selectedShip = nullptr;
        infoLabel->setText("Выберите корабль");
    }
}

void GameWindow::resetPlacement() {
    field = Field();
    for (ShipItem* ship : ships) {
        int originalCount;
        switch(ship->getSize()) {
            case 4: originalCount = 1; break;
            case 3: originalCount = 2; break;
            case 2: originalCount = 3; break;
            case 1: originalCount = 4; break;
            default: originalCount = 0;
        }
        ship->setRemaining(originalCount);
    }

    if (selectedShip) {
        selectedShip->setSelected(false);
        selectedShip = nullptr;
    }

    startButton->setEnabled(false);

    shipsPlaced = 0;

    infoLabel->setText("Выберите корабль");

    mapWidget->update();
}

void GameWindow::onShipSelected(ShipItem* ship) {
    if (selectedShip) {
        selectedShip->setSelected(false);
    }

    selectedShip = ship;
    infoLabel->setText(QString("Выбран %1-палубный корабль").arg(ship->getSize()));
}

void GameWindow::onCellClicked(int x, int y) {

    if (!selectedShip) {
        infoLabel->setText("Эуу корабль выбери да");
        return;
    }

    if (!selectedShip->canPlace()) {
        infoLabel->setText("Все корабль на поле");
        return;
    }

    Ship templateShip = selectedShip->getShipTemplate();

    Ship shipToPlace(templateShip.getSize(), x + 1, y + 1, templateShip.getRotation());
    if (field.setShip(shipToPlace)) {
        selectedShip->decrement();
        selectedShip->setSelected(false);
        selectedShip = nullptr;
        if (!mapWidget) {
            return;
        }
        mapWidget->update();
        infoLabel->setText("Корабль поставлен");
        shipsPlaced++;

        if (shipsPlaced >= 10) {
            infoLabel->setText("Все корабли поставлены");
            if (startButton) {
                startButton->setEnabled(true);
            }
        }
    } else {
        infoLabel->setText("Низзя сюда");
    }
}

void GameWindow::goToBattlefield() {
    auto a = PlacementShipsBot::randomGenerator();
    bool isok = false;
    while (!isok) {
        a = PlacementShipsBot::randomGenerator();
        if (a.has_value()) isok = true;
    }
    Field botField = *a;

    Field playerField = field;

    BattlefieldWindow* bw = new BattlefieldWindow(nullptr, playerField, botField);

    bw->show();
    this->close();
}