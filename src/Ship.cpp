#include "Ship.h"

Ship::Ship(int s, int x, int y, bool r) : size(s), x(x), y(y), rotation(r) {}

int Ship::getSize() const {
    return size;
}

void Ship::setSize(int v) {
    size = v;
}

int Ship::getX() const {
    return x;
}

void Ship::setX(int v) {
    x = v;
}

int Ship::getY() const {
    return y;
}

void Ship::setY(int v) {
    y = v;
}

bool Ship::getRotation() const {
    return rotation;
}

void Ship::setRotation(int v) {
    rotation = v;
}