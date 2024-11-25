#include "Direction.h"

Direction randomDirection()
{
    std::uniform_int_distribution<size_t> dis(0, ALL_DIRECTIONS.size() - 1);
    Direction randomDirection = ALL_DIRECTIONS[dis(gen)];
    return randomDirection;
}