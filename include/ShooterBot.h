#ifndef BATTLESHIPGAME_SHOOTERBOT_H
#define BATTLESHIPGAME_SHOOTERBOT_H

#include <utility>
#include <QWidget>
#include "Field.h"

class ShooterBot : public QWidget{
public:
    ShooterBot(Field f, QWidget *parent = nullptr);

    std::pair<int,int> makeShot();
    void rememberShot(int x,int y,bool hit);
    void printMemory() const;
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    char enemyShots[12][12];
    Field field;
};

#endif //BATTLESHIPGAME_SHOOTERBOT_H