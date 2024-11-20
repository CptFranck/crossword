#include "CrosswordLine.h"

CrosswordLine::CrosswordLine(Direction direction, WordDefinition *wordDefinition, Coordinate *coordinate)
{
    this->direction = direction;
    this->coordinate = coordinate;
    this->wordDefinition = wordDefinition;
}

CrosswordLine::~CrosswordLine()
{
    delete this->coordinate;
    delete this->wordDefinition;
}

std::vector<PotentialCrosswordLine *> CrosswordLine::findPotentialCrosswordLine(WordDefinition *wordDefinition) const
{
    std::vector<PotentialCrosswordLine *> potentialCrosswordLine;
    std::map<char, std::vector<size_t>> commonLetterPositions;
    commonLetterPositions = this->wordDefinition->findCommonLetterPosition(wordDefinition->getWord());

    for (auto it = commonLetterPositions.begin(); it != commonLetterPositions.end(); ++it)
    {
        char key = it->first;
        std::vector<size_t> &positions = it->second;

        for (size_t pos : positions)
        {
            Coordinate *coordinate = this->coordinate->getIntersectionPosition(pos, direction);
            if (hasIntersectionOn(coordinate))
            {
                delete coordinate;
            }
            else
            {
                potentialCrosswordLine.push_back(new PotentialCrosswordLine(wordDefinition, coordinate));
            }
        }
    }
}

bool CrosswordLine::hasIntersectionOn(Coordinate *coordinate) const
{
    for (auto cli : crosswordLineIntersections)
    {
        if (cli->hasForCoordinate(coordinate))
        {
            return true;
        }
    }
    return false;
}

Direction CrosswordLine::getDirection() const
{
    return this->direction;
}

WordDefinition *CrosswordLine::getWordDefinition() const
{
    this->wordDefinition;
}

std::vector<CrosswordLineIntersection *> CrosswordLine::getCrosswordLineIntersections() const
{
    this->crosswordLineIntersections;
}