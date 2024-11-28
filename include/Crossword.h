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
    bool isWordDefinitionUsed(std::shared_ptr<WordDefinition> wordDefinition) const;
    std::vector<std::shared_ptr<CrosswordLine>> findCrosswordLinePlacements(std::shared_ptr<WordDefinition> wordDefinition);
    std::vector<std::shared_ptr<CrosswordLine>> filterPotentialCrosswordLineConflicted(std::vector<std::shared_ptr<PotentialCrosswordLine>> potentialCrosswordLines);
    void printCrossword();

private:
    void deleteWrongPotentialCrosswordLine(std::vector<PotentialCrosswordLine *> &potentialCrosswordLines);

    std::map<std::string, std::shared_ptr<CrosswordLine>> crosswordLines;
};

#endif