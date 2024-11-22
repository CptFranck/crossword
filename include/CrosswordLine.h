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
    CrosswordLine(PotentialCrosswordLine *potentialCrosswordLine, std::map<Coordinate *, CrosswordLine *> crosswordLineIntersections);
    ~CrosswordLine();

    bool hasIntersectionOn(Coordinate *coordinate) const;
    void addCrosswordLineIntersections(Coordinate *c, CrosswordLine *cl);
    std::map<Coordinate *, CrosswordLine *> getCrosswordLineIntersections() const;
    std::vector<PotentialCrosswordLine *> findPotentialCrosswordLine(WordDefinition *wordDefinition) const;

private:
    std::map<Coordinate *, CrosswordLine *> crosswordLineIntersections;
};

#endif