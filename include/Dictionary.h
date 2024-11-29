#ifndef DICTIONARY_H
#define DICTIONARY_H
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <random>

#include "WordDefinition.h"

class Dictionary
{
public:
    Dictionary(std::string filename);
    ~Dictionary();
    WordDefinition getRandomWord() const;

private:
    std::vector<WordDefinition> wordDefinitions;
};

#endif