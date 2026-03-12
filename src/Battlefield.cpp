#include "Battlefield.h"
#include <QWidget>
#include <QHBoxLayout>
#include "BattlefieldUIX.h"
#include "ShooterBot.h"

BattlefieldWindow::BattlefieldWindow(QWidget* parent, Field playerField, Field botField) : playerField(playerField), botField(botField) {
    setWindowTitle("Морской бой");
    setFixedSize(1200, 600);

    QHBoxLayout* layout = new QHBoxLayout(this);


    ShooterBot* mapPlayerWidget = new ShooterBot(playerField, this);
    mapPlayerWidget->setFixedSize(500, 500);


    BattlefieldUIX* mapBotWidget = new BattlefieldUIX(botField, this);
    mapBotWidget->setFixedSize(500, 500);

    layout->addWidget(mapPlayerWidget);
    layout->addWidget(mapBotWidget);

//    int playerPoints = 0;
//    int botPoints = 0;
//    while (playerPoints < 10 && botPoints < 10) {
//
//    }
}