#include "PlacementShipsBot.h"
#include <random>
#include <iostream>

std::optional<Field>  PlacementShipsBot::randomGenerator()
{
    Field field;
    std::random_device rd;
    std::mt19937 gen(rd());
    Ship ship{};
    std::array<int, 10> ships = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};

        for (const int& currentShip : ships) {
            bool isSet = false;
            int countSettingAttempts = 0;

            while (!isSet) {
                ship.setSize(currentShip);

                std::uniform_int_distribution<> dist01(0, 1);
                int rotation = dist01(gen);
                ship.setRotation(rotation);

                if (rotation == 0) {
                    std::uniform_int_distribution<> distX(1, 11 - currentShip);
                    std::uniform_int_distribution<> distY(1, 10);

                    ship.setX(distX(gen));
                    ship.setY(distY(gen));
                } else {
                    std::uniform_int_distribution<> distX(1, 10);
                    std::uniform_int_distribution<> distY(1, 11 - currentShip);

                    ship.setX(distX(gen));
                    ship.setY(distY(gen));
                }

                isSet = field.setShip(ship);

                if (!isSet) {
                    ++countSettingAttempts;
                }

                if (countSettingAttempts > 100) {
                    std::cout << "generation failed\n";
                    return std::nullopt;
                }
            }
        }

        return field;
    }
