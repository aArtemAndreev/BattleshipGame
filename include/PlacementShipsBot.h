#ifndef  PlacementShipsBot_H
#define  PlacementShipsBot_H

#include <optional>
#include <array>
#include "Field.h"

class  PlacementShipsBot {
public:
     PlacementShipsBot() = default;
    static std::optional<Field> randomGenerator();
};

#endif