#include "CrosswordLine.h"

CrosswordLine::CrosswordLine(Direction direction, WordDefinition *wordDefinition, Coordinate *coordinate)
{
    this->direction = direction;
    this->wordDefinition = wordDefinition;
    std::string word = wordDefinition->getWord();
    for (size_t i = 0; word.size(); i++)
    {
        Coordinate *newPosition = coordinate->getPositionFrom(i, direction);
        coordinates[newPosition] = word[i];
    }
}

CrosswordLine::~CrosswordLine()
{
    delete this->wordDefinition;
    for (auto it = coordinates.begin(); it != coordinates.end(); ++it)
    {
        delete it->first;
    }
}

std::vector<PotentialCrosswordLine *> CrosswordLine::findPotentialCrosswordLine(WordDefinition *wordDefinition) const
{
    // letter : list of working positions in current crosswordLine
    std::map<char, std::vector<size_t>> commonLetterPositions;
    commonLetterPositions = this->wordDefinition->findCommonLetterPosition(wordDefinition->getWord());

    std::vector<PotentialCrosswordLine *> potentialCrosswordLines;
    for (auto it = commonLetterPositions.begin(); it != commonLetterPositions.end(); ++it)
    {
        std::vector<size_t> &positions = it->second;

        for (size_t pos : positions)
        {
            Coordinate *intersectionCoordinate = coordinates.begin()->first->getPositionFrom(pos, direction);
            if (!hasIntersectionOn(intersectionCoordinate))
            {
                if (direction == Direction::UP || direction == Direction::DOWN)
                {
                    potentialCrosswordLines.push_back(new PotentialCrosswordLine(Direction::LEFT, wordDefinition, intersectionCoordinate, pos));
                    potentialCrosswordLines.push_back(new PotentialCrosswordLine(Direction::RIGHT, wordDefinition, intersectionCoordinate, pos));
                }
                else
                {
                    potentialCrosswordLines.push_back(new PotentialCrosswordLine(Direction::UP, wordDefinition, intersectionCoordinate, pos));
                    potentialCrosswordLines.push_back(new PotentialCrosswordLine(Direction::DOWN, wordDefinition, intersectionCoordinate, pos));
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

std::map<Coordinate *, char> CrosswordLine::getCoordinates() const
{
    return coordinates;
}

std::vector<CrosswordLineIntersection *> CrosswordLine::getCrosswordLineIntersections() const
{
    this->crosswordLineIntersections;
}