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
    std::shared_ptr<Coordinate> getPositionFrom(size_t position, Direction d) const;
    bool isEqualTo(std::shared_ptr<Coordinate> c) const;
    void ifMinUpdate(std::shared_ptr<Coordinate> c);
    void ifMaxUpdate(std::shared_ptr<Coordinate> c);
    void print();
    int getX() const;
    int getY() const;

private:
    int x, y;
};

#endif