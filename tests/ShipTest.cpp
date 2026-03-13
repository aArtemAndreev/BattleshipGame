#include <gtest/gtest.h>
#include "Ship.h"

TEST(ShipTest, ConstructorAndGetters) {
    Ship ship(4, 3, 5, 0);
    
    EXPECT_EQ(ship.getSize(), 4);
    EXPECT_EQ(ship.getX(), 3);
    EXPECT_EQ(ship.getY(), 5);
    EXPECT_EQ(ship.getRotation(), 0);
}

TEST(ShipTest, Setters) {
    Ship ship;
    
    ship.setSize(3);
    ship.setX(2);
    ship.setY(4);
    ship.setRotation(1);
    
    EXPECT_EQ(ship.getSize(), 3);
    EXPECT_EQ(ship.getX(), 2);
    EXPECT_EQ(ship.getY(), 4);
    EXPECT_EQ(ship.getRotation(), 1);
}