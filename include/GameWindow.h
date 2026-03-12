#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include "Field.h"

class GameWindow : public QWidget {  
public:
    GameWindow(QWidget *parent = nullptr);

private:
    Field field;
private slots:
    void goToBattlefield();
    void rotateShips();
};

#endif