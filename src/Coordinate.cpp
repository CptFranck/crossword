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

Coordinate Coordinate::getPositionFrom(size_t position, Direction d) const
{
    int p = static_cast<int>(position);
    int futur_x = this->x;
    int futur_y = this->y;
    switch (d)
    {
    case Direction::UP:
        futur_y += p;
        break;
    case Direction::DOWN:
        futur_y -= p;
        break;
    case Direction::LEFT:
        futur_x -= p;
        break;
    case Direction::RIGHT:
        futur_x += p;
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

void Coordinate::print()
{
    std::cout << "x: " << this->x << " y: " << this->y << std::endl;
}

int Coordinate::getX() const
{
    return this->x;
}
int Coordinate::getY() const
{
    return this->y;
}