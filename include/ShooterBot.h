#ifndef BATTLESHIPGAME_SHOOTERBOT_H
#define BATTLESHIPGAME_SHOOTERBOT_H

#include <utility>

class ShooterBot
{
private:
    char enemyShots[12][12];
public:
    ShooterBot();

    std::pair<int,int> makeShot();
    void rememberShot(int x,int y,bool hit);
    void printMemory() const;
};

#endif //BATTLESHIPGAME_SHOOTERBOT_H