#ifndef COORDINATE_H
#define COORDINATE_H
#pragma once

#include "Direction.h"

class Coordinate
{
public:
    Coordinate(int x, int y);
    ~Coordinate();
    Coordinate *getIntersectionPosition(size_t position, Direction direction) const;
    bool isEqualTo(Coordinate *coordinate) const;

private:
    int x, y;
};

#endif