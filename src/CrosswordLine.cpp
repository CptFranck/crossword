#include "CrosswordLine.h"

CrosswordLine::CrosswordLine(Direction direction,
                             WordDefinition *wordDefinition,
                             Coordinate *coordinate)
    : PotentialCrosswordLine(direction, wordDefinition, coordinate, 0)
{
}

CrosswordLine::CrosswordLine(PotentialCrosswordLine *potentialCrosswordLine,
                             std::map<Coordinate *, CrosswordLine *> crosswordLineIntersections)
    : PotentialCrosswordLine(direction, wordDefinition, potentialCrosswordLine->getCoordinates().begin()->first, 0)
{
    this->crosswordLineIntersections = crosswordLineIntersections;
}

CrosswordLine::~CrosswordLine()
{
    for (auto it = coordinates.begin(); it != coordinates.end(); ++it)
    {
        delete it->first;
    }
}

std::vector<PotentialCrosswordLine *> CrosswordLine::findPotentialCrosswordLine(WordDefinition *wordDefinition) const
{
    // futur word letter and position : list of working positions in current crosswordLine
    std::map<std::pair<char, size_t>, std::vector<size_t>> commonLetterPositions;
    commonLetterPositions = this->wordDefinition->findCommonLetterPosition(wordDefinition->getWord());

    std::vector<PotentialCrosswordLine *> potentialCrosswordLines;
    for (auto it = commonLetterPositions.begin(); it != commonLetterPositions.end(); ++it)
    {
        size_t futurWordPotentialPosition = it->first.second;
        std::vector<size_t> &currentWordPotentialPositions = it->second;

        for (size_t pos : currentWordPotentialPositions)
        {
            Coordinate *intersectionCoordinate = coordinates.begin()->first->getPositionFrom(pos, direction);
            if (!hasIntersectionOn(intersectionCoordinate))
            {
                if (direction == Direction::UP || direction == Direction::DOWN)
                {
                    potentialCrosswordLines.push_back(new PotentialCrosswordLine(Direction::LEFT, wordDefinition, intersectionCoordinate, futurWordPotentialPosition));
                    potentialCrosswordLines.push_back(new PotentialCrosswordLine(Direction::RIGHT, wordDefinition, intersectionCoordinate, futurWordPotentialPosition));
                }
                else
                {
                    potentialCrosswordLines.push_back(new PotentialCrosswordLine(Direction::UP, wordDefinition, intersectionCoordinate, futurWordPotentialPosition));
                    potentialCrosswordLines.push_back(new PotentialCrosswordLine(Direction::DOWN, wordDefinition, intersectionCoordinate, futurWordPotentialPosition));
                }
            }
            delete intersectionCoordinate;
        }
    }
    return potentialCrosswordLines;
}

bool CrosswordLine::hasIntersectionOn(Coordinate *coordinate) const
{
    for (auto cli : crosswordLineIntersections)
    {
        if (cli.first->isEqualTo(coordinate))
        {
            return true;
        }
    }
    return false;
}

std::map<Coordinate *, CrosswordLine *> CrosswordLine::getCrosswordLineIntersections() const
{
    return this->crosswordLineIntersections;
}