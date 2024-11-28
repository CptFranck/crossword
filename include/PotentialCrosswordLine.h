#ifndef POTENTIALCROSSWORDLINE_H
#define POTENTIALCROSSWORDLINE_H
#pragma once

#include <memory>
#include "WordDefinition.h"
#include "Coordinate.h"

class PotentialCrosswordLine
{
public:
    PotentialCrosswordLine(Direction d, std::shared_ptr<WordDefinition>, std::shared_ptr<Coordinate> intersectionCoordinate, size_t letterPosition);
    ~PotentialCrosswordLine();

    Direction getDirection() const;
    std::shared_ptr<WordDefinition> getWordDefinition() const;
    std::map<std::shared_ptr<Coordinate>, char> getCoordinates() const;
    std::shared_ptr<Coordinate> getFirstCoordinates() const;

protected:
    Direction direction;
    std::shared_ptr<WordDefinition> wordDefinition;
    std::map<std::shared_ptr<Coordinate>, char> coordinates;
};

#endif