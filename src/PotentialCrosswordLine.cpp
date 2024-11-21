#include "PotentialCrosswordLine.h"

PotentialCrosswordLine::PotentialCrosswordLine(Direction direction,
                                               WordDefinition *wordDefinition,
                                               Coordinate *intersectionCoordinate,
                                               size_t letterPosition)
{
    this->direction = direction;
    this->wordDefinition = wordDefinition;
    std::string word = wordDefinition->getWord();
    for (size_t i = 0; word.size(); i++)
    {
        size_t cPosition = i - letterPosition;
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

Direction PotentialCrosswordLine::getDirection() const
{
    return this->direction;
}

WordDefinition *PotentialCrosswordLine::getWordDefinition() const
{
    this->wordDefinition;
}

std::map<Coordinate *, char> PotentialCrosswordLine::getCoordinates() const
{
    return coordinates;
}