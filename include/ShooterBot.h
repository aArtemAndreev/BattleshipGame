#ifndef BATTLESHIPGAME_SHOOTERBOT_H
#define BATTLESHIPGAME_SHOOTERBOT_H

#include <utility>
#include <vector>

enum ShotResult
{
    Miss,
    Hit,
    Kill
};

class ShooterBot
{
private:
    char enemyShots[12][12];
    std::vector<std::pair<int,int>> targetQueue;
    std::vector<std::pair<int,int>> currentHits;
    bool targetMode;

    bool isInside(int x, int y) const;


public:
    ShooterBot();
    void addTarget(int x, int y);
    std::pair<int,int> makeShot();
    void rememberShot(int x, int y, ShotResult result);
    void printMemory() const;
};

#endif