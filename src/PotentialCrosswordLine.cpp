#include "PotentialCrosswordLine.h"

PotentialCrosswordLine::PotentialCrosswordLine(WordDefinition *wordDefinition, Coordinate *intersectionCoordinate, size_t letterPosition, Direction direction)
{
    this->direction = direction;
    this->intersectionCoordinate = intersectionCoordinate;
    this->letterPosition = letterPosition;
    this->wordDefinition = wordDefinition;
}

PotentialCrosswordLine::~PotentialCrosswordLine()
{
    delete intersectionCoordinate;
    delete wordDefinition;
}

std::map<Coordinate *, char> PotentialCrosswordLine::getFutureCoordinates() const
{
    std::map<Coordinate *, char> coordinates;
    std::string word = wordDefinition->getWord();
    for (size_t i = 0; word.size(); i++)
    {
        size_t cPosition = letterPosition - i;
        Coordinate *newPosition = intersectionCoordinate->getPositionFrom(cPosition, direction);
        coordinates[newPosition] = word[i];
    }
    return coordinates;
}