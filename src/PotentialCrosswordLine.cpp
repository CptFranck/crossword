#include "PotentialCrosswordLine.h"

PotentialCrosswordLine::PotentialCrosswordLine(Direction d,
                                               const WordDefinition wd,
                                               const Coordinate intersectionCoordinate,
                                               size_t letterPosition)
    : direction(d), wordDefinition(wd)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring word = converter.from_bytes(wd.getWord());
    for (size_t i = 0; i < word.length(); i++)
    {
        Coordinate newPosition = intersectionCoordinate.getPositionFrom(static_cast<int>(i - letterPosition), d);
        this->coordinates[newPosition] = std::make_pair(word[i], i);
    }
}

PotentialCrosswordLine::~PotentialCrosswordLine()
{
}

Direction PotentialCrosswordLine::getDirection() const
{
    return this->direction;
}

WordDefinition PotentialCrosswordLine::getWordDefinition() const
{
    return this->wordDefinition;
}

std::map<Coordinate, std::pair<wchar_t, size_t>> PotentialCrosswordLine::getCoordinates() const
{
    return this->coordinates;
}

Coordinate PotentialCrosswordLine::getFirstCoordinates() const
{
    for (auto &[c, pair] : this->coordinates)
    {
        const auto &[character, position] = pair;
        if (position == 0)
            return c;
    }
    throw std::runtime_error("Une erreur s'est produite ! :: getFirstCoordinates");
}