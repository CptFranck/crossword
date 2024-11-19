#include "CrosswordLine.h"

CrosswordLine::CrosswordLine(Direction direction, WordDefinition *wordDefinition)
{
    this->direction = direction;
    this->wordDefinition = wordDefinition;
}

CrosswordLine::~CrosswordLine()
{
}

void CrosswordLine::addCrosswordIntersection(CrosswordLineIntersection *crosswordLineIntersection)
{
    this->crosswordLineIntersections.push_back(crosswordLineIntersection);
}