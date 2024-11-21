#ifndef POTENTIALCROSSWORDLINE_H
#define POTENTIALCROSSWORDLINE_H
#pragma once

#include "WordDefinition.h"
#include "Coordinate.h"

class PotentialCrosswordLine
{
public:
    PotentialCrosswordLine(Direction direction, WordDefinition *wordDefinition, Coordinate *intersectionCoordinate, size_t letterPosition);
    ~PotentialCrosswordLine();
    std::map<Coordinate *, char> getCoordinates() const;

private:
    Direction direction;
    WordDefinition *wordDefinition;
    std::map<Coordinate *, char> coordinates;
};

#endif