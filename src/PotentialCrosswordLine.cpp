#include "PotentialCrosswordLine.h"

PotentialCrosswordLine::PotentialCrosswordLine(Direction direction,
                                               WordDefinition *wordDefinition,
                                               Coordinate *intersectionCoordinate,
                                               size_t letterPosition)
{
    intersectionCoordinate->print();
    this->direction = direction;
    this->wordDefinition = wordDefinition;
    std::string word = wordDefinition->getWord();
    for (size_t i = 0; i < word.length(); i++)
    {
        size_t cPosition = i - letterPosition;
        Coordinate *newPosition = intersectionCoordinate->getPositionFrom(cPosition, direction);
        newPosition->print();
        coordinates[newPosition] = word[i];
    }
}

PotentialCrosswordLine::~PotentialCrosswordLine()
{
    for (auto it = coordinates.begin(); it != coordinates.end(); ++it)
    {
        delete it->first;
    }
}

Direction PotentialCrosswordLine::getDirection() const
{
    return this->direction;
}

WordDefinition *PotentialCrosswordLine::getWordDefinition() const
{
    return this->wordDefinition;
}

std::map<Coordinate *, char> PotentialCrosswordLine::getCoordinates() const
{
    return coordinates;
}

Coordinate *PotentialCrosswordLine::getFirstCoordinates() const
{
    Coordinate *first = coordinates.begin()->first;
    for (auto co : coordinates)
    {
        Coordinate *c = co.first;
        switch (this->direction)
        {
        case Direction::UP:
            if (first->getY() > c->getY())
                first = c;
            break;
        case Direction::DOWN:
            if (first->getY() < c->getY())
                first = c;
            break;
        case Direction::LEFT:
            if (first->getX() < c->getX())
                first = c;
            break;
        case Direction::RIGHT:
            if (first->getX() > c->getX())
                first = c;
            break;
        default:
            break;
        }
    }
    return first;
}