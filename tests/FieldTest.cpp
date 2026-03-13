#include <gtest/gtest.h>
#include "Field.h"
#include "Ship.h"

TEST(FieldTest, SetShip) {
    Field field;
    Ship ship(3, 2, 2, 0);
    
    bool result = field.setShip(ship);
    EXPECT_TRUE(result);
    
    EXPECT_EQ(field.getCurrentPlace(2, 2), '.');
    EXPECT_EQ(field.getCurrentPlace(2, 3), '.');
    EXPECT_EQ(field.getCurrentPlace(2, 4), '.');
}

TEST(FieldTest, ShipOutOfBounds) {
    Field field;
    
    Ship ship1(4, 8, 2, 0);
    EXPECT_FALSE(field.setShip(ship1));
    
    Ship ship2(4, 7, 2, 0);
    EXPECT_TRUE(field.setShip(ship2));
}

TEST(FieldTest, ShipsDoNotTouch) {
    Field field;
    
    Ship ship1(3, 2, 2, 0);
    field.setShip(ship1);
    
    Ship ship2(2, 2, 3, 0);
    EXPECT_FALSE(field.setShip(ship2));
    
    Ship ship3(2, 2, 5, 0);
    EXPECT_TRUE(field.setShip(ship3));
}

TEST(FieldTest, ShipStates) {
    Field field;
    
    Ship ship(2, 3, 3, 1);
    field.setShip(ship);
    
    EXPECT_FALSE(field.isShipDamaged(3, 3));
    EXPECT_FALSE(field.isShipSunk(3, 3));
    
    field.markShipAsDamaged(3, 3);
    EXPECT_TRUE(field.isShipDamaged(3, 3));
    EXPECT_FALSE(field.isShipSunk(3, 3));
    
    field.markShipAsSunk(3, 3);
    EXPECT_TRUE(field.isShipSunk(3, 3));
}
