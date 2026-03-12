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
void ShooterBot::rekillTargetsByDirection()
{
    if (currentHits.size() < 2)
    {
        return;
    }

    targetQueue.clear();

    bool sameX = true;
    bool sameY = true;

    int firstX = currentHits[0].first;
    int firstY = currentHits[0].second;

    for (const auto& hit : currentHits)
    {
        if (hit.first != firstX)
        {
            sameX = false;
        }

        if (hit.second != firstY)
        {
            sameY = false;
        }
    }

    if (sameY)
    {
        int y = firstY;
        int minX = currentHits[0].first;
        int maxX = currentHits[0].first;

        for (const auto& hit : currentHits)
        {
            minX = std::min(minX, hit.first);
            maxX = std::max(maxX, hit.first);
        }

        addTarget(minX - 1, y);
        addTarget(maxX + 1, y);
    }
    else if (sameX)
    {
        int x = firstX;
        int minY = currentHits[0].second;
        int maxY = currentHits[0].second;

        for (const auto& hit : currentHits)
        {
            minY = std::min(minY, hit.second);
            maxY = std::max(maxY, hit.second);
        }

        addTarget(x, minY - 1);
        addTarget(x, maxY + 1);
    }
}

void ShooterBot::clearCurrentTarget()
{
    targetQueue.clear();
    currentHits.clear();
    targetMode = false;
}



