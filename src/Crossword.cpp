#include <algorithm>
#include "Crossword.h"

Crossword::Crossword(Dictionary *dictionary, int wordNumber)
{
    for (int i = 0; i < wordNumber; i++)
    {
        for (int tryNumber = 5; i != 0; i--)
        {
            WordDefinition *randomWordDefinition = dictionary->getRandomWord();

            if (this->isWordDefinitionUsed(randomWordDefinition))
            {
                continue;
            }

            if (this->crosswordLines.size() == 0)
            {
                crosswordLines.push_back(new CrosswordLine(randomDirection(), randomWordDefinition, new Coordinate(0, 0)));
                break;
            }

            std::vector<CrosswordLine *> potentialsPlacement = findCrosswordLinePlacements(randomWordDefinition);
            if (potentialsPlacement.size() == 0)
            {
                continue;
            }
            auto maxElementIter = std::max_element(potentialsPlacement.begin(),
                                                   potentialsPlacement.end(),
                                                   [](const CrosswordLine *a,
                                                      const CrosswordLine *b)
                                                   {
                                                       return a->getCoordinates().size() < b->getCoordinates().size();
                                                   });
            if (maxElementIter == potentialsPlacement.end())
            {
                continue;
            }
            CrosswordLine *newCrosswordLine;
            // reste du code
        }
    }
}

Crossword::~Crossword()
{
    for (CrosswordLine *cl : crosswordLines)
    {
        delete cl;
    }
}

bool Crossword::isWordDefinitionUsed(WordDefinition *wordDefinition) const
{
    auto isPresentInCrosswordLine = [&wordDefinition](const CrosswordLine *cl)
    {
        return wordDefinition->getWord() == cl->getWordDefinition()->getWord();
    };
    auto it = find_if(crosswordLines.begin(), crosswordLines.end(), isPresentInCrosswordLine);
    return it == crosswordLines.end();
}

std::vector<CrosswordLine *> Crossword::findCrosswordLinePlacements(WordDefinition *wordDefinition)
{
    std::vector<CrosswordLine *> crosswordLinePlacements;
    std::vector<CrosswordLine *> allCrosswordLinePlacements;
    for (const CrosswordLine *cl : crosswordLines)
    {
        std::vector<PotentialCrosswordLine *> potentialCrosswordLines = cl->findPotentialCrosswordLine(wordDefinition);

        crosswordLinePlacements = FilterConflictedPotentialCrosswordLine(potentialCrosswordLines);
        for (CrosswordLine *clp : crosswordLinePlacements)
        {
            allCrosswordLinePlacements.push_back(clp);
        }

        for (PotentialCrosswordLine *pcl : potentialCrosswordLines)
        {
            delete pcl;
        }
    }
    return allCrosswordLinePlacements;
}

std::vector<CrosswordLine *> Crossword::FilterConflictedPotentialCrosswordLine(std::vector<PotentialCrosswordLine *> potentialCrosswordLines)
{
    bool hasNoConflict = true;
    std::vector<std::pair<Coordinate *, CrosswordLine *>> intersection;
    std::vector<CrosswordLine *> workingPotentialCrosswordLinesWithScore;

    for (PotentialCrosswordLine *pcl : potentialCrosswordLines)
    {
        hasNoConflict = true;
        intersection.clear();
        std::map<Coordinate *, char> futureCoordinates = pcl->getCoordinates();
        auto it_cl = crosswordLines.begin();
        while (it_cl != crosswordLines.end() && hasNoConflict)
        {
            CrosswordLine *cl = *it_cl;
            std::map<Coordinate *, char> coordinateSet = cl->getCoordinates();
            for (auto it_fc = futureCoordinates.begin(); it_fc != futureCoordinates.end(); ++it_fc)
            {
                Coordinate *oneFuturCoordinate = it_fc->first;
                char c = it_fc->second;
                auto sameCoordinate = coordinateSet.find(oneFuturCoordinate);
                if (sameCoordinate != coordinateSet.end())
                {
                    intersection.push_back(std::make_pair(oneFuturCoordinate, cl));
                    if (sameCoordinate->second != c)
                        hasNoConflict = false;
                }
            }
            ++it_cl;
        }
        if (hasNoConflict)
        {
            workingPotentialCrosswordLinesWithScore.push_back(new CrosswordLine(pcl, intersection));
        }
    }
    return workingPotentialCrosswordLinesWithScore;
}