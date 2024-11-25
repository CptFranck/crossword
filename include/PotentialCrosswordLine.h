#ifndef POTENTIALCROSSWORDLINE_H
#define POTENTIALCROSSWORDLINE_H
#pragma once

#include "WordDefinition.h"
#include "Coordinate.h"

class PotentialCrosswordLine
{
public:
    PotentialCrosswordLine(Direction d, WordDefinition *wd, Coordinate *intersectionCoordinate, size_t letterPosition);
    ~PotentialCrosswordLine();

    Direction getDirection() const;
    WordDefinition *getWordDefinition() const;
    std::map<Coordinate *, char> getCoordinates() const;
    Coordinate *getFirstCoordinates() const;

protected:
    Direction direction;
    WordDefinition *wordDefinition;
    std::map<Coordinate *, char> coordinates;
};

#endif