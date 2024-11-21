#include <algorithm>
#include "Crossword.h"

Crossword::Crossword(Dictionary *dictionary, int wordNumber)
{
    WordDefinition *randomWordDefinition;
    std::vector<CrosswordLine *> potentialsPlacement;

    for (int i = 0; i < wordNumber; i++)
    {
        for (int tryNumber = 5; i != 0; i--)
        {
            randomWordDefinition = dictionary->getRandomWord();

            if (this->isWordDefinitionUsed(randomWordDefinition))
            {
                continue;
            }

            if (this->crosswordLines.size() == 0)
            {
                crosswordLines.push_back(new CrosswordLine(randomDirection(), randomWordDefinition, new Coordinate(0, 0)));
                break;
            }

            potentialsPlacement = findCrosswordLinePlacements(randomWordDefinition);
            if (potentialsPlacement.size() == 0)
            {
                continue;
            }
            auto maxIntersectionCrosswordLine = std::max_element(potentialsPlacement.begin(), potentialsPlacement.end(),
                                                                 [](const CrosswordLine *a, const CrosswordLine *b)
                                                                 { return a->getCoordinates().size() <= b->getCoordinates().size(); });

            if (maxIntersectionCrosswordLine == potentialsPlacement.end())
            {
                for (CrosswordLine *pl : potentialsPlacement)
                    delete pl;
                continue;
            }

            CrosswordLine *newCrosswordLine = *maxIntersectionCrosswordLine;

            for (CrosswordLine *pl : potentialsPlacement)
            {
                if (pl != newCrosswordLine)
                    delete pl;
            }

            crosswordLines.push_back(newCrosswordLine);
            for (auto intersection : newCrosswordLine->getCrosswordLineIntersections())
            {
                Coordinate *c = intersection.first;
                CrosswordLine *cl = intersection.second;
                if (!cl->hasIntersectionOn(c))
                {
                    cl->getCrosswordLineIntersections()[c] = newCrosswordLine;
                }
            }
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
    std::vector<CrosswordLine *> allCrosswordLinePlacements;
    for (const CrosswordLine *cl : crosswordLines)
    {
        std::vector<PotentialCrosswordLine *> potentialCrosswordLines = cl->findPotentialCrosswordLine(wordDefinition);
        std::vector<CrosswordLine *> crosswordLinePlacements = filterPotentialCrosswordLineConflicted(potentialCrosswordLines);
        allCrosswordLinePlacements.insert(allCrosswordLinePlacements.end(), crosswordLinePlacements.begin(), crosswordLinePlacements.end());
        for (PotentialCrosswordLine *pcl : potentialCrosswordLines)
            delete pcl;
    }
    return allCrosswordLinePlacements;
}

std::vector<CrosswordLine *> Crossword::filterPotentialCrosswordLineConflicted(std::vector<PotentialCrosswordLine *> potentialCrosswordLines)
{
    bool hasNoConflict;
    std::map<Coordinate *, CrosswordLine *> intersection;
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
                    intersection[oneFuturCoordinate] = cl;
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