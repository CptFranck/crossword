#include "CrosswordLineIntersection.h"
#include "CrosswordLine.h"

CrosswordLineIntersection::CrosswordLineIntersection(CrosswordLine *crosswordLine1,
                                                     CrosswordLine *crosswordLine2,
                                                     int crosswordLine1Intersection,
                                                     int crosswordLine2Intersection)
{
    this->CrosswordLine1 = crosswordLine1;
    this->CrosswordLine2 = crosswordLine2;
    this->crosswordLine1Intersection = crosswordLine1Intersection;
    this->crosswordLine2Intersection = crosswordLine2Intersection;
}

CrosswordLineIntersection::~CrosswordLineIntersection()
{
}