#ifndef FIELD_H
#define FIELD_H

#include "Ship.h"

class Field {
private:
    char field[12][12];
    char shipStates[12][12];
    bool checkIfCouldBePut(Ship ship);
public:
    Field() noexcept;

    Field& operator=(const Field& other);
    void printField();
    bool setShip(Ship ship);
    void setCurrentPlace(int y, int x, char c);
    char getCurrentPlace(int y, int x) const;
    void setShipState(int y, int x, int state);
    int getShipState(int y, int x) const;   
    bool isShipDamaged(int y, int x) const;
    bool isShipSunk(int y, int x) const;
    void markShipAsDamaged(int y, int x);
    void markShipAsSunk(int y, int x);

    ~Field() = default;
};

#endif