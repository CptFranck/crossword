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
    std::vector<PotentialCrosswordLine *> potentialCrosswordLines;
    std::map<char, std::vector<size_t>> commonLetterPositions;
    commonLetterPositions = this->wordDefinition->findCommonLetterPosition(wordDefinition->getWord());

    for (auto it = commonLetterPositions.begin(); it != commonLetterPositions.end(); ++it)
    {
        std::vector<size_t> &positions = it->second;

        for (size_t pos : positions)
        {
            Coordinate *intersectionCoordinate = coordinate->getPositionFrom(pos, direction);
            if (!hasIntersectionOn(intersectionCoordinate))
            {
                if (direction == Direction::UP || direction == Direction::DOWN)
                {
                    potentialCrosswordLines.push_back(new PotentialCrosswordLine(wordDefinition, intersectionCoordinate, pos, Direction::LEFT));
                    potentialCrosswordLines.push_back(new PotentialCrosswordLine(wordDefinition, intersectionCoordinate, pos, Direction::RIGHT));
                }
                else
                {
                    potentialCrosswordLines.push_back(new PotentialCrosswordLine(wordDefinition, intersectionCoordinate, pos, Direction::UP));
                    potentialCrosswordLines.push_back(new PotentialCrosswordLine(wordDefinition, intersectionCoordinate, pos, Direction::DOWN));
                }
            }
            delete intersectionCoordinate;
        }
    }
    return potentialCrosswordLines;
}

std::map<Coordinate *, char> CrosswordLine::getCoordinates() const
{
    std::map<Coordinate *, char> coordinates;
    std::string word = wordDefinition->getWord();
    for (size_t i = 0; word.size(); i++)
    {
        Coordinate *newPosition = coordinate->getPositionFrom(i, direction);
        coordinates[newPosition] = word[i];
    }
    return coordinates;
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