#ifndef COORDINATE_H
#define COORDINATE_H
#pragma once

#include <vector>
#include <memory>
#include "Direction.h"

class Coordinate
{
public:
    Coordinate(int x_, int y_);
    ~Coordinate();
    Coordinate getPositionFrom(size_t position, Direction d) const;
    bool operator<(const Coordinate &other) const;
    bool isEqualTo(Coordinate c) const;
    void ifMinUpdate(Coordinate c);
    void ifMaxUpdate(Coordinate c);
    void print();
    int getX() const;
    int getY() const;

private:
    int x, y;
};

#endif