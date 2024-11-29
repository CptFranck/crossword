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
    CrosswordLine(std::shared_ptr<PotentialCrosswordLine> pcl, std::map<Coordinate, std::shared_ptr<CrosswordLine>> cli);
    ~CrosswordLine();

    bool hasIntersectionOn(Coordinate c) const;
    void addCrosswordLineIntersections(Coordinate c, std::shared_ptr<CrosswordLine> cl);
    std::map<Coordinate, std::shared_ptr<CrosswordLine>> getCrosswordLineIntersections() const;
    std::vector<std::shared_ptr<PotentialCrosswordLine>> findPotentialCrosswordLine(WordDefinition wd) const;

private:
    std::map<Coordinate, std::shared_ptr<CrosswordLine>> crosswordLineIntersections;
};

#endif