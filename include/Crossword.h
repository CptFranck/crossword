#ifndef CROSSWORD_H
#define CROSSWORD_H
#pragma once

#include <vector>
#include "CrosswordLine.h"
#include "Dictionary.h"

class Crossword
{
public:
    Crossword(Dictionary *dictionary, int wordNumber);
    ~Crossword();

    bool isWordDefinitionUsed(WordDefinition *wordDefinition) const;
    std::vector<const CrosswordLine *> findCrosswordLinePlacement(WordDefinition *wordDefinition);

private:
    void deleteWrongPotentialCrosswordLine(std::vector<PotentialCrosswordLine *> &potentialCrosswordLines);

    std::vector<CrosswordLine *> crosswordLines;
};

#endif