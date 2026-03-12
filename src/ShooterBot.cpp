#include "ShooterBot.h"
#include <random>
#include <iostream>
#include <algorithm>

ShooterBot::ShooterBot()
    : targetMode(false)
{
    for (int y = 0; y < 12; ++y)
    {
        for (int x = 0; x < 12; ++x)
        {
            enemyShots[y][x] = '0';
        }
    }
}

bool ShooterBot::isInside(int x, int y) const
{
    return x >= 1 && x <= 10 && y >= 1 && y <= 10;
}

void ShooterBot::addTarget(int x, int y)
{
    if (!isInside(x, y))
    {
        return;
    }

    if (enemyShots[y][x] != '0')
    {
        return;
    }

    std::pair<int, int> target = {x, y};

    if (std::find(targetQueue.begin(), targetQueue.end(), target) == targetQueue.end())
    {
        targetQueue.push_back(target);
    }
}
void ShooterBot::addNeighbors(int x, int y)
{
    addTarget(x + 1, y);
    addTarget(x - 1, y);
    addTarget(x, y + 1);
    addTarget(x, y - 1);
}

