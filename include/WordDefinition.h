#ifndef WORDDEFINITION_H
#define WORDDEFINITION_H
#include <string>

#pragma once

class WordDefinition
{
public:
    WordDefinition(std::string word, std::string definition);
    ~WordDefinition();

private:
    std::string word;
    std::string definition;
};

#endif