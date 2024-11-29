#include "CrosswordLine.h"

CrosswordLine::CrosswordLine(Direction d, WordDefinition wd, std::shared_ptr<Coordinate> c)
    : PotentialCrosswordLine(d, wd, c, 0)
{
}

CrosswordLine::CrosswordLine(std::shared_ptr<PotentialCrosswordLine> pcl,
                             std::map<std::shared_ptr<Coordinate>, std::shared_ptr<CrosswordLine>> cli)
    : PotentialCrosswordLine(pcl->getDirection(),
                             pcl->getWordDefinition(),
                             pcl->getFirstCoordinates(), 0)
{
    this->crosswordLineIntersections = cli;
}

CrosswordLine::~CrosswordLine()
{
}

std::vector<std::shared_ptr<PotentialCrosswordLine>> CrosswordLine::findPotentialCrosswordLine(WordDefinition wd) const
{
    // // futur word letter and its position : list of common letter positions with the word of the current crosswordLine
    std::map<std::pair<char, size_t>, std::vector<size_t>> commonLetterPositions;
    commonLetterPositions = this->wordDefinition.findCommonLetterPosition(wd.getWord());

    std::vector<std::shared_ptr<PotentialCrosswordLine>> potentialCrosswordLines;
    // for each char and position associate to list of position working
    for (auto it = commonLetterPositions.begin(); it != commonLetterPositions.end(); ++it)
    {
        size_t futurWordLetterPosition = it->first.second;
        std::vector<size_t> currentWordPositions = it->second;

        for (size_t pos : currentWordPositions)
        {
            std::shared_ptr<Coordinate> intersectionCoordinate = getFirstCoordinates()->getPositionFrom(pos, direction);
            if (!hasIntersectionOn(intersectionCoordinate))
            {
                if (direction == Direction::UP || direction == Direction::DOWN)
                {
                    potentialCrosswordLines.push_back(std::make_unique<PotentialCrosswordLine>(Direction::LEFT, wd, intersectionCoordinate, futurWordLetterPosition));
                    potentialCrosswordLines.push_back(std::make_unique<PotentialCrosswordLine>(Direction::RIGHT, wd, intersectionCoordinate, futurWordLetterPosition));
                }
                else
                {
                    potentialCrosswordLines.push_back(std::make_unique<PotentialCrosswordLine>(Direction::UP, wd, intersectionCoordinate, futurWordLetterPosition));
                    potentialCrosswordLines.push_back(std::make_unique<PotentialCrosswordLine>(Direction::DOWN, wd, intersectionCoordinate, futurWordLetterPosition));
                }
            }
        }
    }
    return potentialCrosswordLines;
}

bool CrosswordLine::hasIntersectionOn(std::shared_ptr<Coordinate> c) const
{
    for (auto cli : this->crosswordLineIntersections)
    {
        if (cli.first->isEqualTo(c))
        {
            return true;
        }
    }
    return false;
}

void CrosswordLine::addCrosswordLineIntersections(std::shared_ptr<Coordinate> c, std::shared_ptr<CrosswordLine> cl)
{
    this->crosswordLineIntersections[c] = cl;
}

std::map<std::shared_ptr<Coordinate>, std::shared_ptr<CrosswordLine>> CrosswordLine::getCrosswordLineIntersections() const
{
    return this->crosswordLineIntersections;
}