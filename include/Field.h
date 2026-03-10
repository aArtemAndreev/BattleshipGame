#ifndef FIELD_H
#define FIELD_H

#include "Ship.h"

class Field {
private:
    char field[12][12];
    bool checkIfCouldBePut(Ship ship);
public:
    Field() noexcept;

    Field& operator=(const Field& other);
    void printField();
    bool setShip(Ship ship);
    char getCurrentPlace(int y, int x) const;

    ~Field() = default;
};

#endif