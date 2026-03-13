#include "Field.h"
#include <iostream>
#include <QDebug>

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
        if (shipX < 1 || shipX + shipSize - 1 > 10) return false;
        for (int i = shipX - 1; i <= shipX + shipSize; ++i) {
            if (i < 1 || i > 10) continue;

            if (field[shipY][i] == '.') return false;

            if (shipY - 1 >= 1 && field[shipY - 1][i] == '.') return false;
            if (shipY + 1 <= 10 && field[shipY + 1][i] == '.') return false;
        }
    } else {
        if (shipY < 1 || shipY + shipSize - 1 > 10) return false;
        for (int i = shipY - 1; i <= shipY + shipSize; ++i) {
            if (i < 1 || i > 10) continue;

            if (field[i][shipX] == '.') return false;

            if (shipX - 1 >= 1 && field[i][shipX - 1] == '.') return false;
            if (shipX + 1 <= 10 && field[i][shipX + 1] == '.') return false;
        }
    }
    return true;
}

bool Field::setShip(Ship ship) {
    if (ship.getX() < 1 || ship.getX() > 10 || 
        ship.getY() < 1 || ship.getY() > 10) {
        return false;
    }
    if (!checkIfCouldBePut(ship)) {
        return false;
    }
    const int shipX = ship.getX();
    const int shipY = ship.getY();
    const int shipSize = ship.getSize();

    if (ship.getRotation() == 0) {
        for (int i = shipX; i < shipX + shipSize; ++i) {
            if (i < 1 || i > 10) {
                return false;
            }
            field[shipY][i] = '.';
        }
    } else {
        for (int i = shipY; i < shipY + shipSize; ++i) {
            if (i < 1 || i > 10) {
                return false;
            }
            field[i][shipX] = '.';
        }
    }
    return true;
}
char Field::getCurrentPlace(int y, int x) const {
    return field[y][x];
}
void Field::setCurrentPlace(int y, int x, char c) {
    if (y >= 1 && y <= 10 && x >= 1 && x <= 10) {
        field[y][x] = c;
    }
}

void Field::setShipState(int y, int x, int state) {
    if (y >= 1 && y <= 10 && x >= 1 && x <= 10) {
        shipStates[y][x] = state;
    }
}

int Field::getShipState(int y, int x) const {
    return shipStates[y][x];
}

bool Field::isShipDamaged(int y, int x) const {
    if (y >= 1 && y <= 10 && x >= 1 && x <= 10) {
        return shipStates[y][x] == 1;
    }
    return false;
}

bool Field::isShipSunk(int y, int x) const {
    if (y >= 1 && y <= 10 && x >= 1 && x <= 10) {
        return shipStates[y][x] == 2;
    }
    return false;
}

void Field::markShipAsDamaged(int y, int x) {
    if (y >= 1 && y <= 10 && x >= 1 && x <= 10) {
        if (field[y][x] == '.') {
            shipStates[y][x] = 1;
        }
    }
}

void Field::markShipAsSunk(int y, int x) {
    if (y >= 1 && y <= 10 && x >= 1 && x <= 10) {
        if (field[y][x] == '.') {
            shipStates[y][x] = 2;
        }
    }
}
