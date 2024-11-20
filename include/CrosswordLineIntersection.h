#ifndef CROSSWORDLINEINTERSECTION_H
#define CROSSWORDLINEINTERSECTION_H
#pragma once

#include "CrosswordLine.h"

class CrosswordLine;

class CrosswordLineIntersection
{
public:
    CrosswordLineIntersection(Coordinate *coordinate,
                              CrosswordLine *crosswordLine1,
                              CrosswordLine *crosswordLine2,
                              size_t crosswordLine1Intersection,
                              size_t crosswordLine2Intersection);
    ~CrosswordLineIntersection();

private:
    Coordinate *coordinate;
    CrosswordLine *crosswordLine1;
    CrosswordLine *crosswordLine2;
    size_t crosswordLine1Intersection;
    size_t crosswordLine2Intersection;
};

#endif