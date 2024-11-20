#include "Coordinate.h"

Coordinate::Coordinate(int x, int y)
{
    this->x = x;
    this->y = y;
}

Coordinate::~Coordinate()
{
}

Coordinate Coordinate::getPositionFrom(size_t position, Direction direction) const
{
    int x = this->x;
    int y = this->y;
    switch (direction)
    {
    case Direction::UP:
        x += position;
        break;
    case Direction::DOWN:
        y -= position;
        break;
    case Direction::LEFT:
        x -= position;
        break;
    case Direction::RIGHT:
        x += position;
        break;
    }
    return Coordinate(x, y);
}

bool Coordinate::isEqualTo(Coordinate coordinate) const
{
    return this->x == coordinate.x && this->y == coordinate.y;
}