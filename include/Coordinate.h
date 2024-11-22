#ifndef COORDINATE_H
#define COORDINATE_H
#pragma once

#include <vector>
#include "Direction.h"

class Coordinate
{
public:
    Coordinate(int x, int y);
    ~Coordinate();
    Coordinate *getPositionFrom(size_t position, Direction direction) const;
    bool isEqualTo(Coordinate *coordinate) const;
    void ifMinUpdate(Coordinate *c);
    void ifMaxUpdate(Coordinate *c);
    int getX() const;
    int getY() const;

private:
    int x, y;
};

#endif