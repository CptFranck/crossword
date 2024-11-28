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

std::shared_ptr<Coordinate> Coordinate::getPositionFrom(size_t position, Direction d) const
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
    return std::make_unique<Coordinate>(futur_x, futur_y);
}

bool Coordinate::isEqualTo(std::shared_ptr<Coordinate> c) const
{
    return this->x == c->x && this->y == c->y;
}

void Coordinate::ifMinUpdate(std::shared_ptr<Coordinate> c)
{
    if (c->x < this->x)
        this->x = c->x;
    if (c->y < this->y)
        this->y = c->y;
}
void Coordinate::ifMaxUpdate(std::shared_ptr<Coordinate> c)
{
    if (c->x > this->x)
        this->x = c->x;
    if (c->y > this->y)
        this->y = c->y;
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