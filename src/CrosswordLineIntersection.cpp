#include "CrosswordLineIntersection.h"

CrosswordLineIntersection::CrosswordLineIntersection(Coordinate *coordinate,
                                                     CrosswordLine *crosswordLine1,
                                                     CrosswordLine *crosswordLine2,
                                                     size_t crosswordLine1Intersection,
                                                     size_t crosswordLine2Intersection)
{
    this->coordinate = coordinate;
    this->crosswordLine1 = crosswordLine1;
    this->crosswordLine2 = crosswordLine2;
    this->crosswordLine1Intersection = crosswordLine1Intersection;
    this->crosswordLine2Intersection = crosswordLine2Intersection;
}

CrosswordLineIntersection::~CrosswordLineIntersection()
{
}

bool CrosswordLineIntersection::hasForCoordinate(Coordinate *coordinate) const
{
    return this->coordinate->isEqualTo(coordinate);
}