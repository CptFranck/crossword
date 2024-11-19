#ifndef CROSSWORD_H
#define CROSSWORD_H
#pragma once

#include <vector>
#include "Dictionary.h"
#include "CrosswordLine.h"

class Crossword
{
public:
    Crossword(Dictionary *dictionary);
    ~Crossword();
    void addCrosswordLine(CrosswordLine *crosswordLine);

private:
    Dictionary *dictionary;
    std::vector<CrosswordLine *> crosswordLines;
};

#endif