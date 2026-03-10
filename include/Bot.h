#ifndef STUPIDBOT_H
#define STUPIDBOT_H

#include <optional>
#include <array>
#include "Field.h"

class StupidBot {
public:
    ~StupidBot() = default;
    std::optional<Field> randomGenerator();
};

#endif