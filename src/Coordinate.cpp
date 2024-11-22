#include "Coordinate.h"

Coordinate::Coordinate(int x, int y)
{
    this->x = x;
    this->y = y;
}

Coordinate::~Coordinate()
{
}

Coordinate *Coordinate::getPositionFrom(size_t position, Direction direction) const
{
    int x = this->x;
    int y = this->y;
    switch (direction)
    {
    case Direction::UP:
        y += position;
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
    return new Coordinate(x, y);
}

bool Coordinate::isEqualTo(Coordinate *coordinate) const
{
    return this->x == coordinate->x && this->y == coordinate->y;
}

void Coordinate::ifMinUpdate(Coordinate *c)
{
    if (c->x < this->x)
        this->x = c->x;
    if (c->y < this->y)
        this->y = c->y;
}
void Coordinate::ifMaxUpdate(Coordinate *c)
{
    if (c->x > this->x)
        this->x = c->x;
    if (c->y > this->y)
        this->y = c->y;
}

int Coordinate::getX() const
{
    return this->x;
}
int Coordinate::getY() const
{
    return this->y;
}