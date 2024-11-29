#ifndef WORDDEFINITION_H
#define WORDDEFINITION_H
#pragma once

#include <string>
#include <vector>
#include <map>

class WordDefinition
{
public:
    WordDefinition(std::string newWord, std::string newDefinition);
    WordDefinition(const WordDefinition &wd);
    ~WordDefinition();

    std::map<std::pair<char, size_t>, std::vector<size_t>> findCommonLetterPosition(std::string futurWord) const;

    std::string getWord() const;
    std::string getDefinition() const;

private:
    std::string word;
    std::string definition;
};

#endif