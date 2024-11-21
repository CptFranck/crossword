#include "WordDefinition.h"

WordDefinition::WordDefinition(std::string word, std::string definition)
{
    this->word = word;
    this->definition = definition;
}

WordDefinition::~WordDefinition()
{
}

std::map<std::pair<char, size_t>, std::vector<size_t>> WordDefinition::findCommonLetterPosition(std::string futurWord) const
{
    std::map<std::pair<char, size_t>, std::vector<size_t>> potentialIntersection;
    int cIndex = 0;
    for (const char &c : futurWord)
    {
        size_t pos = word.find(c, 0);
        while (pos != std::string::npos)
        {
            std::pair<char, size_t> key(c, cIndex);
            potentialIntersection[key].push_back(pos);
            pos = word.find(c, pos + 1);
        }
        cIndex++;
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