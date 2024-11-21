#ifndef CROSSWORDLINE_H
#define CROSSWORDLINE_H
#pragma once

#include <vector>
#include "Coordinate.h"
#include "Direction.h"
#include "WordDefinition.h"
#include "PotentialCrosswordLine.h"

class CrosswordLineIntersection;

class CrosswordLine : public PotentialCrosswordLine
{
public:
    CrosswordLine(Direction direction, WordDefinition *wordDefinition, Coordinate *coordinate);
    CrosswordLine(PotentialCrosswordLine *potentialCrosswordLine, std::vector<Coordinate *> crosswordLineIntersections);
    ~CrosswordLine();

    std::vector<PotentialCrosswordLine *> findPotentialCrosswordLine(WordDefinition *wordDefinition) const;
    std::vector<Coordinate *> getCrosswordLineIntersections() const;

private:
    bool hasIntersectionOn(Coordinate *coordinate) const;

    std::vector<Coordinate *> crosswordLineIntersections;
};

#endif