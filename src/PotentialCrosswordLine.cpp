#include "PotentialCrosswordLine.h"

PotentialCrosswordLine::PotentialCrosswordLine(Direction d,
                                               const WordDefinition wd,
                                               const Coordinate intersectionCoordinate,
                                               size_t letterPosition)
    : direction(d), wordDefinition(wd)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring word = converter.from_bytes(wd.getWord());
    for (size_t i = 0; i < word.length(); i++)
    {
        Coordinate newPosition = intersectionCoordinate.getPositionFrom(i - letterPosition, d);
        this->coordinates[newPosition] = word[i];
    }
}

PotentialCrosswordLine::~PotentialCrosswordLine()
{
}

Direction PotentialCrosswordLine::getDirection() const
{
    return this->direction;
}

WordDefinition PotentialCrosswordLine::getWordDefinition() const
{
    return this->wordDefinition;
}

std::map<Coordinate, wchar_t> PotentialCrosswordLine::getCoordinates() const
{
    return this->coordinates;
}

Coordinate PotentialCrosswordLine::getFirstCoordinates() const
{
    Coordinate first = this->coordinates.begin()->first;
    for (auto co : this->coordinates)
    {
        Coordinate c = co.first;
        switch (direction)
        {
        case Direction::UP:
            if (first.getY() > c.getY())
                first = c;
            break;
        case Direction::DOWN:
            if (first.getY() < c.getY())
                first = c;
            break;
        case Direction::LEFT:
            if (first.getX() < c.getX())
                first = c;
            break;
        case Direction::RIGHT:
            if (first.getX() > c.getX())
                first = c;
            break;
        default:
            break;
        }
    }
    return first;
}