#ifndef SHIP_H
#define SHIP_H

class Ship {
private:
    int size;
    int x;
    int y;
    bool rotation;
public:
    Ship() = default;
    Ship(int s, int x, int y, bool r);

    int getSize() const;
    void setSize(int v);
    int getX() const;
    void setX(int v);
    int getY() const;
    void setY(int v);
    bool getRotation() const;
    void setRotation(int v);

    ~Ship() = default;
};

#endif