#include "GameWindow.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include "MyWidget.h"
#include "Battlefield.h"
#include "PlacementShipsBot.h"

GameWindow::GameWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Морской бой");
    setFixedSize(800, 600);
    
    QHBoxLayout* layout = new QHBoxLayout(this);
    
    QWidget* leftPanel = new QWidget(this);
    
    leftPanel->setFixedWidth(200);

    QVBoxLayout* leftLayout = new QVBoxLayout(leftPanel);
    
    QPushButton* startButton = new QPushButton("Начать игру", this);
    startButton->setFixedSize(150, 50);

    connect(startButton, &QPushButton::clicked, this, &GameWindow::goToBattlefield);

    leftLayout->addWidget(startButton);
    leftLayout->addStretch();

    MyWidget* mapWidget = new MyWidget(field, this);
    mapWidget->setFixedSize(500, 500);

    layout->addWidget(leftPanel);
    layout->addWidget(mapWidget);
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