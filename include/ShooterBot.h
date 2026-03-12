#ifndef BATTLESHIPGAME_SHOOTERBOT_H
#define BATTLESHIPGAME_SHOOTERBOT_H

#include <utility>
#include <vector>
#include <QWidget>
#include "Field.h"

enum ShotResult
{
    Miss,
    Hit,
    Kill
};

class ShooterBot: public QWidget{

private:
    Field field;
    char enemyShots[12][12];
    std::vector<std::pair<int,int>> targetQueue;
    std::vector<std::pair<int,int>> currentHits;
    bool targetMode;

    bool isInside(int x, int y) const;
    void addTarget(int x, int y);
    void addNeighbors(int x, int y);
    void rekillTargetsByDirection();
    void clearCurrentTarget();
    void markAroundKilledShip();

protected:
    void paintEvent(QPaintEvent *event) override;
public:
    ShooterBot(Field f, QWidget *parent = nullptr);
    ShooterBot();
    std::pair<int,int> makeShot();
    void rememberShot(int x, int y, ShotResult result);
    void printMemory() const;
};


#endif