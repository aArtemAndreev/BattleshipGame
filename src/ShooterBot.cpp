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



