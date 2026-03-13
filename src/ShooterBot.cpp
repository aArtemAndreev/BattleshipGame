#include "ShooterBot.h"
#include <random>
#include <iostream>
#include <algorithm>
#include <QPainter>

ShooterBot::ShooterBot(Field f, std::shared_ptr<bool> whoseStep, QWidget *parent) : QWidget(parent), field(f), whoseStep(whoseStep) {}

void ShooterBot::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(0, 0, 500, 500, QBrush{"#2980b9"});
    for (int i = 1; i <= 9; ++i) {
        painter.drawLine(50 * i, 0, 50 * i, 500);
        painter.drawLine(0, 50 * i, 500, 50 * i);
    }

    painter.setPen(QPen(Qt::blue, 3));
    for (int i = 1; i < 12; ++i) {
        for (int j = 1; j < 12; ++j) {
            int x = 50 * (j - 1);
            int y = 50 * (i - 1);
            if (field.getCurrentPlace(i, j) == '.') {
                painter.fillRect(x, y, 50, 50, QBrush{Qt::white});
            } else if (field.getCurrentPlace(i, j) == '/') {
                painter.fillRect(x, y, 50, 50, QBrush{Qt::white});
                painter.drawLine(x, y, x + 50, y + 50);
            } else if (field.getCurrentPlace(i, j) == 'E') {
                painter.fillRect(x, y, 50, 50, QBrush{Qt::blue});
            }
        }
    }

    if (*whoseStep) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distX(1, 500);
        std::uniform_int_distribution<> distY(1, 500);
        int x = distX(gen);
        int y = distY(gen);
        x -= x % 50;
        y -= y % 50;
        if (field.getCurrentPlace(y / 50 + 1, x / 50 + 1) == '.') {
            field.setCurrentPlace(y / 50 + 1, x / 50 + 1, '/');
        } else if (field.getCurrentPlace(y / 50 + 1, x / 50 + 1) == '0') {
            field.setCurrentPlace(y / 50 + 1, x / 50 + 1, 'E');
        }
        *whoseStep = false;
    }
    update();
}

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
void ShooterBot::markAroundKilledShip()
{
    for (const auto& hit : currentHits)
    {
        int x = hit.first;
        int y = hit.second;

        for (int dy = -1; dy <= 1; ++dy)
        {
            for (int dx = -1; dx <= 1; ++dx)
            {
                int nx = x + dx;
                int ny = y + dy;

                if (!isInside(nx, ny))
                {
                    continue;
                }

                if (enemyShots[ny][nx] == '0')
                {
                    enemyShots[ny][nx] = '-';
                }
            }
        }
    }
}

std::pair<int, int> ShooterBot::makeShot()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    if (targetMode)
    {
        while (!targetQueue.empty())
        {
            std::pair<int, int> shot = targetQueue.front();
            targetQueue.erase(targetQueue.begin());

            int x = shot.first;
            int y = shot.second;

            if (enemyShots[y][x] == '0')
            {
                return shot;
            }
        }
    }

    std::uniform_int_distribution<> distX(1, 10);
    std::uniform_int_distribution<> distY(1, 10);

    int x;
    int y;

    do
    {
        x = distX(gen);
        y = distY(gen);
    }
    while (enemyShots[y][x] != '0');

    return {x, y};
}

void ShooterBot::rememberShot(int x, int y, ShotResult result)
{
    if (result == Miss)
    {
        enemyShots[y][x] = '*';
        return;
    }

    if (result == Hit)
    {
        enemyShots[y][x] = 'X';
        currentHits.push_back({x, y});
        targetMode = true;

        if (currentHits.size() == 1)
        {
            addNeighbors(x, y);
        }
        else
        {
            rekillTargetsByDirection();
        }

        return;
    }


if (result == Kill)
    {
        enemyShots[y][x] = 'X';
        currentHits.push_back({x, y});

        markAroundKilledShip();
        clearCurrentTarget();
    }
}


void ShooterBot::printMemory() const
{
    for (int y = 1; y <= 10; ++y)
    {
        for (int x = 1; x <= 10; ++x)
        {
            std::cout << enemyShots[y][x] << ' ';
        }
        std::cout << '\n';
    }
}


