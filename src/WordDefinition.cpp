#include "WordDefinition.h"
#include "iostream"

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
    // futur word letter and position : list of working positions in current crosswordLine
    std::map<std::pair<char, size_t>, std::vector<size_t>> potentialIntersection;
    int cIndex = 0;
    std::cout << "futur " << futurWord << std::endl;
    std::cout << "courant " << word << std::endl;
    for (const char &c : futurWord)
    {
        size_t pos = word.find(c, 0);
        while (pos != std::string::npos)
        {
            std::cout << "lettre trouvée " << futurWord << " |" << c << "| en commun à " << pos << std::endl;
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