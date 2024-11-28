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
    CrosswordLine(Direction d, std::shared_ptr<WordDefinition> wd, std::shared_ptr<Coordinate> c);
    CrosswordLine(std::shared_ptr<PotentialCrosswordLine> pcl, std::map<std::shared_ptr<Coordinate>, std::shared_ptr<CrosswordLine>> cli);
    ~CrosswordLine();

    bool hasIntersectionOn(std::shared_ptr<Coordinate> c) const;
    void addCrosswordLineIntersections(std::shared_ptr<Coordinate> c, std::shared_ptr<CrosswordLine> cl);
    std::map<std::shared_ptr<Coordinate>, std::shared_ptr<CrosswordLine>> getCrosswordLineIntersections() const;
    std::vector<std::shared_ptr<PotentialCrosswordLine>> findPotentialCrosswordLine(std::shared_ptr<WordDefinition> wd) const;

private:
    std::map<std::shared_ptr<Coordinate>, std::shared_ptr<CrosswordLine>> crosswordLineIntersections;
};

#endif