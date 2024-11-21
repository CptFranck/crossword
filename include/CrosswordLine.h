#ifndef CROSSWORDLINE_H
#define CROSSWORDLINE_H
#pragma once

#include <vector>
#include "Coordinate.h"
#include "Direction.h"
#include "WordDefinition.h"
#include "PotentialCrosswordLine.h"
#include "CrosswordLineIntersection.h"

class CrosswordLineIntersection;

class CrosswordLine
{
public:
    CrosswordLine(Direction direction, WordDefinition *wordDefinition, Coordinate *coordinate);
    ~CrosswordLine();

    std::vector<PotentialCrosswordLine *> findPotentialCrosswordLine(WordDefinition *wordDefinition) const;

    Direction getDirection() const;
    WordDefinition *getWordDefinition() const;
    std::map<Coordinate *, char> getCoordinates() const;
    std::vector<CrosswordLineIntersection *> getCrosswordLineIntersections() const;

private:
    bool hasIntersectionOn(Coordinate *coordinate) const;

    Direction direction;
    WordDefinition *wordDefinition;
    std::map<Coordinate *, char> coordinates;
    std::vector<CrosswordLineIntersection *> crosswordLineIntersections;
};

#endif