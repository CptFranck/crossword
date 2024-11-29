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
    CrosswordLine(Direction d, const WordDefinition wd, const Coordinate c);
    CrosswordLine(PotentialCrosswordLine pcl, std::map<Coordinate, CrosswordLine> cli);
    ~CrosswordLine();

    bool hasIntersectionOn(Coordinate c) const;
    std::map<Coordinate, CrosswordLine> getCrosswordLineIntersections() const;
    std::vector<PotentialCrosswordLine> findPotentialCrosswordLine(WordDefinition wd) const;

private:
    std::map<Coordinate, CrosswordLine> crosswordLineIntersections;
};

#endif