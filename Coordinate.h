#ifndef COORDINATE_H
#define COORDINATE_H
#pragma once

#include "Direction.h"

class Coordinate
{
public:
    Coordinate(int x, int y);
    ~Coordinate();

private:
    int x, y;
    Coordinate getIntersectionPosition(size_t position, Direction direction);
};

#endif