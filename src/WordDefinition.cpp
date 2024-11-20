#include "WordDefinition.h"

WordDefinition::WordDefinition(std::string word, std::string definition)
{
    this->word = word;
    this->definition = definition;
}

WordDefinition::~WordDefinition()
{
}

bool WordDefinition::hasLetterInCommon(std::string word) const
{
    for (const char &c : this->word)
    {
        if (word.find(c))
        {
            return true;
        }
    }
    return false;
}

std::string WordDefinition::getWord() const
{
    return this->word;
}
std::string WordDefinition::getDefinition() const
{
    return this->definition;
}