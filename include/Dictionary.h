#ifndef DICTIONARY_H
#define DICTIONARY_H
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>

#include "WordDefinition.h"

class Dictionary
{
public:
    Dictionary(std::string filename);
    ~Dictionary();
    WordDefinition *getRandomWord();

private:
    std::vector<WordDefinition *> wordDefinitions;
};

#endif