#include "WordDefinition.h"

WordDefinition::WordDefinition(std::string newWord, std::string newDefinition)
{
    this->word = newWord;
    this->definition = newDefinition;
}

WordDefinition::~WordDefinition()
{
}

std::map<std::pair<wchar_t, size_t>, std::vector<size_t>> WordDefinition::findCommonLetterPosition(std::string futurWord) const
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring UTF8_futurWord = converter.from_bytes(futurWord);
    std::wstring UTF8_word = converter.from_bytes(this->word);
    // futur word letter and its position : list of common letter positions with current word
    std::map<std::pair<wchar_t, size_t>, std::vector<size_t>> potentialIntersection;
    int cIndex = 0;
    for (const wchar_t &wc : UTF8_futurWord)
    {
        size_t pos = UTF8_word.find(wc, 0);
        while (pos != std::string::npos)
        {
            std::pair<wchar_t, size_t> key(wc, cIndex);
            potentialIntersection[key].push_back(pos);
            pos = UTF8_word.find(wc, pos + 1);
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