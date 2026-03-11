#include "GameWindow.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include "MyWidget.h"

GameWindow::GameWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Морской бой");
    setFixedSize(800, 600);
    
    QHBoxLayout* layout = new QHBoxLayout(this);
    
    QWidget* leftPanel = new QWidget(this);
    
    leftPanel->setFixedWidth(200);
    
    QVBoxLayout* leftLayout = new QVBoxLayout(leftPanel);
    
    QPushButton* startButton = new QPushButton("Начать игру", this);
    startButton->setFixedSize(150, 50);
    
    leftLayout->addWidget(startButton);
    leftLayout->addStretch();
    
    MyWidget* mapWidget = new MyWidget(field, this);
    mapWidget->setFixedSize(500, 500);
    
    layout->addWidget(leftPanel);
    layout->addWidget(mapWidget);
}