#include "CrosswordLine.h"
#include "iostream"

CrosswordLine::CrosswordLine(Direction direction,
                             WordDefinition *wordDefinition,
                             Coordinate *coordinate)
    : PotentialCrosswordLine(direction, wordDefinition, coordinate, 0)
{
    std::cout << std::endl;
}

CrosswordLine::CrosswordLine(PotentialCrosswordLine *potentialCrosswordLine,
                             std::map<Coordinate *, CrosswordLine *> crosswordLineIntersections)
    : PotentialCrosswordLine(potentialCrosswordLine->getDirection(),
                             potentialCrosswordLine->getWordDefinition(),
                             potentialCrosswordLine->getFirstCoordinates(), 0)
{
    this->crosswordLineIntersections = crosswordLineIntersections;
}

CrosswordLine::~CrosswordLine()
{
    for (auto it = crosswordLineIntersections.begin(); it != crosswordLineIntersections.end(); ++it)
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
    // for each char and position associate to list of position working
    std::cout << "nb possibilité :" << commonLetterPositions.size() << std::endl;
    for (auto it = commonLetterPositions.begin(); it != commonLetterPositions.end(); ++it)
    {
        size_t futurWordPosition = it->first.second;
        std::vector<size_t> &currentWordPositions = it->second;

        for (size_t pos : currentWordPositions)
        {

            Coordinate *intersectionCoordinate = getFirstCoordinates()->getPositionFrom(pos, direction);
            if (!hasIntersectionOn(intersectionCoordinate))
            {
                if (direction == Direction::UP || direction == Direction::DOWN)
                {
                    potentialCrosswordLines.push_back(new PotentialCrosswordLine(Direction::LEFT, wordDefinition, intersectionCoordinate, futurWordPosition));
                    potentialCrosswordLines.push_back(new PotentialCrosswordLine(Direction::RIGHT, wordDefinition, intersectionCoordinate, futurWordPosition));
                }
                else
                {
                    potentialCrosswordLines.push_back(new PotentialCrosswordLine(Direction::UP, wordDefinition, intersectionCoordinate, futurWordPosition));
                    potentialCrosswordLines.push_back(new PotentialCrosswordLine(Direction::DOWN, wordDefinition, intersectionCoordinate, futurWordPosition));
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