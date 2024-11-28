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
    std::shared_ptr<WordDefinition> getRandomWord();

private:
    std::vector<std::shared_ptr<WordDefinition>> wordDefinitions;
};

#endif