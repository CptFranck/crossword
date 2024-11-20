#ifndef COORDINATE_H
#define COORDINATE_H
#pragma once

#include "Direction.h"

class Coordinate
{
public:
    Coordinate(int x, int y);
    ~Coordinate();
    Coordinate getPositionFrom(size_t position, Direction direction) const;
    std::map<Coordinate, char> getCoordinates() const;
    bool isEqualTo(Coordinate coordinate) const;

private:
    int x, y;
};

#endif