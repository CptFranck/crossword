#ifndef CROSSWORD_H
#define CROSSWORD_H
#pragma once

#include <algorithm>
#include "Dictionary.h"
#include "CrosswordLine.h"

class Crossword
{
public:
    Crossword(std::shared_ptr<Dictionary> dictionary, int wordNumber);
    ~Crossword();
    bool findNewCrosswordLine(std::shared_ptr<Dictionary> dictionary);
    bool isWordDefinitionUsed(WordDefinition wordDefinition) const;
    std::vector<CrosswordLine> findCrosswordLinePlacements(WordDefinition wordDefinition);
    std::vector<CrosswordLine> filterPotentialCrosswordLineConflicted(std::vector<PotentialCrosswordLine> potentialCrosswordLines);

    void printCrossword();

private:
    bool checkConflicts(const std::map<Coordinate, wchar_t> futureCoordinates,
                        const std::map<Coordinate, wchar_t> coordinateSet,
                        std::map<Coordinate, CrosswordLine> &intersection,
                        const CrosswordLine cl);

    std::map<std::string, CrosswordLine> crosswordLines;
};

#endif