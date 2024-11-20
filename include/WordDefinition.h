#ifndef WORDDEFINITION_H
#define WORDDEFINITION_H
#pragma once

#include <string>
#include <vector>
#include <map>

class WordDefinition
{
public:
    WordDefinition(std::string word, std::string definition);
    ~WordDefinition();

    std::map<char, std::vector<size_t>> findPotentialIntersection(std::string word) const;

    std::string getWord() const;
    std::string getDefinition() const;

private:
    std::string word;
    std::string definition;
};

#endif