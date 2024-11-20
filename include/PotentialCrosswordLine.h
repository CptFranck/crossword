#ifndef POTENTIALCROSSWORDLINE_H
#define POTENTIALCROSSWORDLINE_H
#pragma once

#include "WordDefinition.h"
#include "Coordinate.h"

class PotentialCrosswordLine
{
public:
    PotentialCrosswordLine(WordDefinition *wordDefinition, Coordinate *coordinate, size_t letterPosition, Direction direction);
    ~PotentialCrosswordLine();
    std::map<Coordinate, char> getFutureCoordinates() const;

private:
    size_t letterPosition;
    Direction direction;
    Coordinate *coordinate;
    WordDefinition *wordDefinition;
};

#endif