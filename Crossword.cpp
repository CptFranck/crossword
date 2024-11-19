#include "Crossword.h"

Crossword::Crossword(Dictionary *dictionary)
{
    this->dictionary = dictionary;
}

Crossword::~Crossword()
{
}

void Crossword::addCrosswordLine(CrosswordLine *crosswordLine)
{
    crosswordLines.push_back(crosswordLine);
}