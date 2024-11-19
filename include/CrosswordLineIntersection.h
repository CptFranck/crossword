#ifndef CROSSWORDLINEINTERSECTION_H
#define CROSSWORDLINEINTERSECTION_H

#pragma once

class CrosswordLineIntersection
{
public:
    CrosswordLineIntersection(CrosswordLine *CrosswordLine1,
                              CrosswordLine *CrosswordLine2,
                              int crosswordLine1Intersection,
                              int crosswordLine2Intersection);
    ~CrosswordLineIntersection();

private:
    CrosswordLine *CrosswordLine1;
    CrosswordLine *CrosswordLine2;
    int crosswordLine1Intersection;
    int crosswordLine2Intersection;
};

#endif