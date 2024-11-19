#ifndef CROSSWORDLINE_H
#define CROSSWORDLINE_H
#pragma once

#include <vector>
#include "Direction.h"
#include "WordDefinition.h"
#include "CrosswordLineIntersection.h"

class CrosswordLine
{
public:
    CrosswordLine(Direction direction, WordDefinition *wordDefinition);
    ~CrosswordLine();
    void addCrosswordIntersection(CrosswordLineIntersection *crosswordLineIntersection);

private:
    Direction direction;
    WordDefinition *wordDefinition;
    std::vector<CrosswordLineIntersection *> crosswordLineIntersections;
};

#endif