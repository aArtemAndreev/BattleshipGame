#include "Field.h"
#include <iostream>

Field::Field() noexcept {
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            field[i][j] = '0';
        }
    }
}

Field& Field::operator=(const Field& other) {
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            field[i][j] = other.getCurrentPlace(i, j);
        }
    }
    return *this;
}

void Field::printField() {
    for (int i = 1; i < 11; ++i) {
        for (int j = 1; j < 11; ++j) {
            std::cout << field[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

bool Field::checkIfCouldBePut(Ship ship) {
    const int shipX = ship.getX();
    const int shipY = ship.getY();
    const int shipSize = ship.getSize();
    if (ship.getRotation() == 0) {
        if (shipX < 1 || shipX + shipSize > 10) return false;
        for (int i = shipX - 1; i < shipX + shipSize + 1; ++i) {
            if (field[shipY][i] == '.' || field[shipY - 1][i] == '.' || field[shipY + 1][i] == '.') {
                return false;
            }
        }
    } else {
        if (shipY < 1 || shipY + shipSize > 10) return false;
        for (int i = shipY - 1; i < shipY + shipSize + 1; ++i) {
            if (field[i][shipX] == '.' || field[i][shipX - 1] == '.' || field[i][shipX + 1] == '.') {
                return false;
            }
        }
    }
    return true;
}

bool Field::setShip(Ship ship) {
    if (!checkIfCouldBePut(ship)) {
        return false;
    }
    const int shipX = ship.getX();
    const int shipY = ship.getY();
    const int shipSize = ship.getSize();
    if (ship.getRotation() == 0) {
        for (int i = shipX; i < shipX + shipSize; ++i) {
            field[shipY][i] = '.';
        }
    } else {
        for (int i = shipY; i < shipY + shipSize; ++i) {
            field[i][shipX] = '.';
        }
    }
    return true;
}

char Field::getCurrentPlace(int y, int x) const {
    return field[y][x];
}

void Field::setCurrentPlace(int y, int x, char c) {
    field[y][x] = c;
}
