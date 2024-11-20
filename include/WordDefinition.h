#ifndef WORDDEFINITION_H
#define WORDDEFINITION_H
#include <string>

#pragma once

class WordDefinition
{
public:
    WordDefinition(std::string word, std::string definition);
    ~WordDefinition();

    bool hasLetterInCommon(std::string word) const;

    std::string getWord() const;
    std::string getDefinition() const;

private:
    std::string word;
    std::string definition;
};

#endif