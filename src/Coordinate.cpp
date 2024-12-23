#include "Coordinate.h"
#include <iostream>

Coordinate::Coordinate(int x_, int y_)
{
    this->x = x_;
    this->y = y_;
}

Coordinate::~Coordinate()
{
}

Coordinate Coordinate::getPositionFrom(int position, Direction d) const
{
    int futur_x = this->x;
    int futur_y = this->y;
    switch (d)
    {
    case Direction::VERTICAL:
        futur_y -= position;
        break;
    case Direction::HORIZONTAL:
        futur_x += position;
        break;
    }
    return Coordinate(futur_x, futur_y);
}

bool Coordinate::operator<(const Coordinate &other) const
{
    if (x != other.x)
        return x < other.x;
    return y < other.y;
}

bool Coordinate::isEqualTo(Coordinate c) const
{
    return this->x == c.x && this->y == c.y;
}

void Coordinate::ifMinUpdate(Coordinate c)
{
    if (c.x < this->x)
        this->x = c.x;
    if (c.y < this->y)
        this->y = c.y;
}
void Coordinate::ifMaxUpdate(Coordinate c)
{
    if (c.x > this->x)
        this->x = c.x;
    if (c.y > this->y)
        this->y = c.y;
}

int Coordinate::getX() const
{
    return this->x;
}
int Coordinate::getY() const
{
    return this->y;
}