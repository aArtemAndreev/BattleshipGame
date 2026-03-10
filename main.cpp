#include <iostream>
#include <optional>
#include <QApplication>
#include "Bot.h"
#include "MyWidget.h"

int main(int argc, char *argv[]) {
    StupidBot bot;
    auto field = bot.randomGenerator();
    while (!field.has_value()) {
        field = bot.randomGenerator();
    }
    field->printField();
    
    QApplication app(argc, argv);
    MyWidget widget(*field);
    widget.setFixedSize(500, 500);
    widget.setWindowTitle("Field");

    widget.show();
    return app.exec();
}