#include "PotentialCrosswordLine.h"

PotentialCrosswordLine::PotentialCrosswordLine(Direction direction, WordDefinition *wordDefinition, Coordinate *intersectionCoordinate, size_t letterPosition)
{
    this->direction = direction;
    this->wordDefinition = wordDefinition;
    std::string word = wordDefinition->getWord();
    for (size_t i = 0; word.size(); i++)
    {
        size_t cPosition = letterPosition - i;
        Coordinate *newPosition = intersectionCoordinate->getPositionFrom(cPosition, direction);
        coordinates[newPosition] = word[i];
    }
}

PotentialCrosswordLine::~PotentialCrosswordLine()
{
    delete wordDefinition;
    for (auto it = coordinates.begin(); it != coordinates.end(); ++it)
    {
        delete it->first;
    }
}

std::map<Coordinate *, char> PotentialCrosswordLine::getCoordinates() const
{
    return coordinates;
}