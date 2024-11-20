#ifndef POTENTIALCROSSWORDLINE_H
#define POTENTIALCROSSWORDLINE_H
#pragma once

#include "WordDefinition.h"
#include "Coordinate.h"

class PotentialCrosswordLine
{
public:
    PotentialCrosswordLine(WordDefinition *wordDefinition, Coordinate *coordinate);
    ~PotentialCrosswordLine();

private:
    WordDefinition *wordDefinition;
    Coordinate *coordinate;
};

#endif