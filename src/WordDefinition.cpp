#include "WordDefinition.h"

WordDefinition::WordDefinition(std::string word, std::string definition)
{
    this->word = word;
    this->definition = definition;
}

WordDefinition::~WordDefinition()
{
}

std::map<char, std::vector<size_t>> WordDefinition::findCommonLetterPosition(std::string futurWord) const
{
    std::map<char, std::vector<size_t>> potentialIntersection;
    for (const char &c : futurWord)
    {
        size_t pos = word.find(c, 0);
        while (pos != std::string::npos)
        {
            potentialIntersection[c].push_back(pos);
            pos = word.find(c, pos + 1);
        }
    }
    return potentialIntersection;
}

std::string WordDefinition::getWord() const
{
    return this->word;
}
std::string WordDefinition::getDefinition() const
{
    return this->definition;
}