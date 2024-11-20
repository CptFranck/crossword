#include "PotentialCrosswordLine.h"

PotentialCrosswordLine::PotentialCrosswordLine(WordDefinition *wordDefinition, Coordinate *coordinate)
{
    this->coordinate = coordinate;
    this->wordDefinition = wordDefinition;
}

PotentialCrosswordLine::~PotentialCrosswordLine()
{
    delete wordDefinition;
    delete coordinate;
}