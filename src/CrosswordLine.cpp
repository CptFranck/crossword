#include "CrosswordLine.h"

CrosswordLine::CrosswordLine(Direction d, const WordDefinition wd, const Coordinate c)
    : PotentialCrosswordLine(d, wd, c, 0)
{
}

CrosswordLine::CrosswordLine(PotentialCrosswordLine pcl,
                             std::map<Coordinate, CrosswordLine> cli)
    : PotentialCrosswordLine(pcl.getDirection(),
                             pcl.getWordDefinition(),
                             pcl.getFirstCoordinates(), 0),
      crosswordLineIntersections(cli)
{
}

CrosswordLine::~CrosswordLine()
{
}

std::vector<PotentialCrosswordLine> CrosswordLine::findPotentialCrosswordLine(WordDefinition wd) const
{
    // // futur word letter and its position : list of common letter positions with the word of the current crosswordLine
    std::map<std::pair<wchar_t, size_t>, std::vector<size_t>> commonLetterPositions;
    commonLetterPositions = this->wordDefinition.findCommonLetterPosition(wd.getWord());

    std::vector<PotentialCrosswordLine> potentialCrosswordLines;
    // for each char and position associate to list of position working
    for (auto it = commonLetterPositions.begin(); it != commonLetterPositions.end(); ++it)
    {
        size_t futurWordLetterPosition = it->first.second;
        std::vector<size_t> currentWordPositions = it->second;

        for (size_t pos : currentWordPositions)
        {
            Coordinate intersectionCoordinate = getFirstCoordinates().getPositionFrom(static_cast<int>(pos), direction);
            if (!hasIntersectionOn(intersectionCoordinate))
            {
                if (direction == Direction::UP || direction == Direction::DOWN)
                {
                    potentialCrosswordLines.push_back(PotentialCrosswordLine(Direction::LEFT, wd, intersectionCoordinate, futurWordLetterPosition));
                    potentialCrosswordLines.push_back(PotentialCrosswordLine(Direction::RIGHT, wd, intersectionCoordinate, futurWordLetterPosition));
                }
                else
                {
                    potentialCrosswordLines.push_back(PotentialCrosswordLine(Direction::UP, wd, intersectionCoordinate, futurWordLetterPosition));
                    potentialCrosswordLines.push_back(PotentialCrosswordLine(Direction::DOWN, wd, intersectionCoordinate, futurWordLetterPosition));
                }
            }
        }
    }
    return potentialCrosswordLines;
}

bool CrosswordLine::hasIntersectionOn(Coordinate c) const
{
    for (auto cli : this->crosswordLineIntersections)
    {
        if (cli.first.isEqualTo(c))
        {
            return true;
        }
    }
    return false;
}

std::map<Coordinate, CrosswordLine> CrosswordLine::getCrosswordLineIntersections() const
{
    return this->crosswordLineIntersections;
}