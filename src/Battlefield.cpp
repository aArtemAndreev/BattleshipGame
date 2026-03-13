#include "Battlefield.h"
#include <QWidget>
#include <QHBoxLayout>
#include "BattlefieldUIX.h"
#include "ShooterBot.h"


BattlefieldWindow::BattlefieldWindow(QWidget* parent, Field playerField, Field botField) : playerField(playerField), botField(botField) {
    setWindowTitle("Морской бой");
    setFixedSize(1200, 600);

    QHBoxLayout* layout = new QHBoxLayout(this);

    std::shared_ptr<bool> whoseStep = std::make_shared<bool>(false);
    ShooterBot* mapPlayerWidget = new ShooterBot(playerField, whoseStep, this);
    mapPlayerWidget->setFixedSize(500, 500);

    BattlefieldUIX* mapBotWidget = new BattlefieldUIX(botField, whoseStep, this);
    mapBotWidget->setFixedSize(500, 500);

    layout->addWidget(mapPlayerWidget);
    layout->addWidget(mapBotWidget);
}