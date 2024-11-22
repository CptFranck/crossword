#ifndef CROSSWORD_H
#define CROSSWORD_H
#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include "Dictionary.h"
#include "CrosswordLine.h"

class Crossword
{
public:
    Crossword(Dictionary *dictionary, int wordNumber);
    ~Crossword();

    bool isWordDefinitionUsed(WordDefinition *wordDefinition) const;
    std::vector<const CrosswordLine *> findCrosswordLinePlacement(WordDefinition *wordDefinition);
    std::vector<CrosswordLine *> findCrosswordLinePlacements(WordDefinition *wordDefinition);
    std::vector<CrosswordLine *> filterPotentialCrosswordLineConflicted(std::vector<PotentialCrosswordLine *> potentialCrosswordLines);
    void printCrossword();

private:
    void deleteWrongPotentialCrosswordLine(std::vector<PotentialCrosswordLine *> &potentialCrosswordLines);

    std::vector<CrosswordLine *> crosswordLines;
};

#endif