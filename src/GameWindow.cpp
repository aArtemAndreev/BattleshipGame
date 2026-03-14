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
    setWindowTitle("Battleship");
    setFixedSize(800, 600);
    
    QHBoxLayout* layout = new QHBoxLayout(this);
    
    QWidget* leftPanel = new QWidget(this);
    
    leftPanel->setFixedWidth(200);

    QVBoxLayout* leftLayout = new QVBoxLayout(leftPanel);

    QPushButton* rotateButton = new QPushButton("Rotate", this);
    rotateButton->setFixedSize(150, 30);
    connect(rotateButton, &QPushButton::clicked, this, &GameWindow::rotateShips);
    leftLayout->addWidget(rotateButton);

    resetButton = new QPushButton("Clear", this);
    resetButton->setFixedSize(150, 30);
    connect(resetButton, &QPushButton::clicked, this, &GameWindow::resetPlacement);
    leftLayout->addWidget(resetButton);

    infoLabel = new QLabel("Choose ship", this);
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
    
    startButton = new QPushButton("Start", this);
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
        btn->setText(currentOrientation ? "Horizontal" : "Vertical");
    }

    if (selectedShip) {
        selectedShip->setSelected(false);
        selectedShip = nullptr;
        infoLabel->setText("Choose ship");
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

    infoLabel->setText("Choose ship");

    mapWidget->update();
}

void GameWindow::onShipSelected(ShipItem* ship) {
    if (selectedShip) {
        selectedShip->setSelected(false);
    }

    selectedShip = ship;
    infoLabel->setText(QString("Selected %1-deck ship").arg(ship->getSize()));
}

void GameWindow::onCellClicked(int x, int y) {
    if (!selectedShip) {
        infoLabel->setText("Ship is not selected");
        return;
    }

    if (!selectedShip->canPlace()) {
        infoLabel->setText("Placed all ships of this type");
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
        infoLabel->setText("Ship placed");
        shipsPlaced++;

        if (shipsPlaced >= 10) {
            infoLabel->setText("All ships are placed");
            if (startButton) {
                startButton->setEnabled(true);
            }
        }
    } else {
        infoLabel->setText("Can't place here");
    }
}

void GameWindow::goToBattlefield() {
    auto a = PlacementShipsBot::randomGenerator();
    bool isOk = false;
    while (!isOk) {
        a = PlacementShipsBot::randomGenerator();
        if (a.has_value()) isOk = true;
    }

    Field playerField = field;

    BattlefieldWindow* bw = new BattlefieldWindow(nullptr, playerField, *a);

    bw->show();
    this->close();
}