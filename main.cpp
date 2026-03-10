#include <iostream>
#include <optional>
#include <QApplication>
#include <QPushButton>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QDialog>
#include "Bot.h"
#include "MyWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    QDialog startDialog;
    startDialog.setWindowTitle("Морской бой");
    startDialog.setFixedSize(300, 150);
    
    QVBoxLayout layout(&startDialog);
    
    QPushButton startButton("Начать игру");
    QPushButton exitButton("Выход");
    
    layout.addWidget(&startButton);
    layout.addWidget(&exitButton);
    
    QObject::connect(&exitButton, &QPushButton::clicked, &startDialog, &QDialog::reject);
    QObject::connect(&startButton, &QPushButton::clicked, &startDialog, &QDialog::accept);
        
    if (startDialog.exec() == QDialog::Accepted) {
        StupidBot bot;
        auto field = bot.randomGenerator();
        while (!field.has_value()) {
            field = bot.randomGenerator();
        }
        field->printField();
        MyWidget widget(*field);
        widget.setFixedSize(500, 500);
        widget.setWindowTitle("Поле морского боя");
        widget.show();
        
        return app.exec();
    }
    return 0;
}