#ifndef CROSSWORD_H
#define CROSSWORD_H
#pragma once

#include <cwctype>
#include <algorithm>
#include "Dictionary.h"
#include "CrosswordLine.h"

class Crossword
{
public:
    Crossword(std::shared_ptr<Dictionary> dictionary, int wordNumber);
    ~Crossword();
    void printCrossword();

private:
    bool findNewCrosswordLine(std::shared_ptr<Dictionary> dictionary);
    void addCrosswordLine(std::string wd, CrosswordLine cl);
    bool isWordDefinitionUsed(WordDefinition wordDefinition) const;
    std::vector<CrosswordLine> findCrosswordLinePlacements(WordDefinition wordDefinition);
    std::vector<CrosswordLine> filterPotentialCrosswordLineConflicted(std::vector<PotentialCrosswordLine> potentialCrosswordLines);
    bool DoNotRespectCrosswordDimension(PotentialCrosswordLine pcl);
    bool hasConflictsOnSameCoordinate(const PotentialCrosswordLine pcl,
                                      const CrosswordLine cl,
                                      std::map<Coordinate, CrosswordLine> &intersection) const;

    int dimension;
    Coordinate min, max;
    std::map<std::string, CrosswordLine> crosswordLines;
};

#endif