#include "Bot.h"
#include <random>
#include <iostream>

std::optional<Field> StupidBot::randomGenerator() {
        Field field;
        std::random_device rd;
        std::mt19937 gen(rd());
        bool isSet = false;
        Ship ship{};
        std::array<int, 10> ships = {0, 1, 2, 3, 1, 2, 3, 2, 3, 3};
        int countSettingAttempts = 0;
        for (const int& currentShip : ships) {
            isSet = false;
            while (!isSet) {
                ship.setSize(4 - currentShip);
                std::uniform_int_distribution<> distX(1, 7);
                std::uniform_int_distribution<> distY(1, 7);
                std::uniform_int_distribution<> dist01(0, 1);
                ship.setX(distX(gen) + currentShip);
                ship.setY(distY(gen) + currentShip);
                ship.setRotation(dist01(gen));
                isSet = field.setShip(ship);
                if (!isSet) ++countSettingAttempts;
                if (countSettingAttempts > 100) {
                    std::cout << "shit\n";
                    return std::nullopt;
                }
            }
        }
    return field;
}