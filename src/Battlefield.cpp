#include "Battlefield.h"
#include <QWidget>
#include <QHBoxLayout>
#include "MyWidget.h"

BattlefieldWindow::BattlefieldWindow(QWidget* parent, Field playerField, Field botField) : playerField(playerField), botField(botField) {
    setWindowTitle("Морской бой");
    setFixedSize(1200, 600);

    QHBoxLayout* layout = new QHBoxLayout(this);


    MyWidget* mapPlayerWidget = new MyWidget(playerField, this);
    mapPlayerWidget->setFixedSize(500, 500);


    MyWidget* mapBotWidget = new MyWidget(botField, this);
    mapBotWidget->setFixedSize(500, 500);

    layout->addWidget(mapPlayerWidget);
    layout->addWidget(mapBotWidget);
}