#ifndef POTENTIALCROSSWORDLINE_H
#define POTENTIALCROSSWORDLINE_H
#pragma once

#include <memory>
#include "WordDefinition.h"
#include "Coordinate.h"

class PotentialCrosswordLine
{
public:
    PotentialCrosswordLine(Direction d,
                           WordDefinition wd,
                           std::shared_ptr<Coordinate> intersectionCoordinate,
                           size_t letterPosition);
    ~PotentialCrosswordLine();

    Direction getDirection() const;
    WordDefinition getWordDefinition() const;
    std::map<std::shared_ptr<Coordinate>, char> getCoordinates() const;
    std::shared_ptr<Coordinate> getFirstCoordinates() const;

protected:
    Direction direction;
    WordDefinition wordDefinition;
    std::map<std::shared_ptr<Coordinate>, char> coordinates;
};

#endif