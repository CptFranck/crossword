#include "Crossword.h"

Crossword::Crossword(Dictionary *dictionary, int wordNumber)
{
    std::cout << "Creation du mot croisé" << std::endl;

    bool wordFound;
    for (int i = 0; i < wordNumber; i++)
    {
        wordFound = false;
        std::cout << "Mot °" << i + 1 << std::endl;
        for (int trialNumber = 0; trialNumber < 5 && !wordFound; trialNumber++)
        {
            std::cout << "Essaie N°" << trialNumber + 1 << std::endl;
            wordFound = findNewCrosswordLine(dictionary);
        }
        printCrossword();
    }

    std::cout << "Mot croisé construit !" << std::endl;
}

Crossword::~Crossword()
{
    for (auto cl : crosswordLines)
    {
        delete cl;
        // delete cl.second;
    }
}

bool Crossword::findNewCrosswordLine(Dictionary *dictionary)
{
    std::vector<CrosswordLine *> potentialsPlacement;
    WordDefinition *newWordDefinition = dictionary->getRandomWord();

    if (crosswordLines.size() == 0)
    {
        std::cout << "Premier mot enregistrer : " << newWordDefinition->getWord() << std::endl;
        crosswordLines.push_back(new CrosswordLine(randomDirection(), newWordDefinition, new Coordinate(0, 0)));
        std::cout << "--1--DEBUT" << std::endl;
        crosswordLinesBis[newWordDefinition->getWord()] = new CrosswordLine(randomDirection(), newWordDefinition, new Coordinate(0, 0));
        std::cout << "--1--FIN" << std::endl;
        return true;
    }

    if (isWordDefinitionUsed(newWordDefinition))
    {
        std::cout << "Mot déjà utilisé : " << newWordDefinition->getWord() << std::endl;
        return false;
    }

    potentialsPlacement = findCrosswordLinePlacements(newWordDefinition);

    if (potentialsPlacement.size() == 0)
    {
        std::cout << "Aucune lettre en commun " << newWordDefinition->getWord() << std::endl;
        return false;
    }

    // Mot le plus long ...
    auto maxIntersectionCrosswordLine = std::max_element(potentialsPlacement.begin(),
                                                         potentialsPlacement.end(),
                                                         [](const CrosswordLine *a, const CrosswordLine *b)
                                                         { return a->getCrosswordLineIntersections().size() <=
                                                                  b->getCrosswordLineIntersections().size(); });

    if (maxIntersectionCrosswordLine == potentialsPlacement.end())
    {
        std::cout << "BUG ??" << std::endl;
        for (CrosswordLine *pl : potentialsPlacement)
            delete pl;
        return false;
    }

    CrosswordLine *newCrosswordLine = *maxIntersectionCrosswordLine;
    for (auto &pl : potentialsPlacement)
    {
        if (pl != newCrosswordLine)
        {
            delete pl;
        }
    }
    std::cout << "Mot ajouté : " << newWordDefinition->getWord() << std::endl;
    crosswordLines.push_back(newCrosswordLine);
    std::cout << "--2--DEBUT" << std::endl;
    crosswordLinesBis[newWordDefinition->getWord()] = newCrosswordLine;
    std::cout << "--2--FIN" << std::endl;
    return true;
}

bool Crossword::isWordDefinitionUsed(WordDefinition *wordDefinition) const
{
    // auto isPresentInCrosswordLine = [&wordDefinition](const CrosswordLine *cl)
    // {
    //     return wordDefinition->getWord() == cl->getWordDefinition()->getWord();
    // };
    // auto it = find_if(crosswordLines.begin(), crosswordLines.end(), isPresentInCrosswordLine);
    // return it != crosswordLines.end();
    return crosswordLinesBis.find(wordDefinition->getWord()) != crosswordLinesBis.end();
}

std::vector<CrosswordLine *> Crossword::findCrosswordLinePlacements(WordDefinition *wordDefinition)
{
    std::vector<CrosswordLine *> allCrosswordLinePlacements;
    // for (auto cl : crosswordLines)
    for (auto clPaire : crosswordLinesBis)
    {
        CrosswordLine *cl = clPaire.second;
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

        auto it_cl = crosswordLinesBis.begin();
        while (it_cl != crosswordLinesBis.end() && hasNoConflict)
        {
            int coordonneEnCommun = 0;

            // CrosswordLine *cl = *it_cl;
            CrosswordLine *cl = (*it_cl).second;
            std::map<Coordinate *, char> coordinateSet = cl->getCoordinates();
            for (auto it_fc = futureCoordinates.begin(); it_fc != futureCoordinates.end(); ++it_fc)
            {
                Coordinate *oneFuturCoordinate = it_fc->first;
                char fc = it_fc->second;
                for (auto it_cs = coordinateSet.begin(); it_cs != coordinateSet.end(); ++it_cs)
                {
                    Coordinate *oneCoordinateSet = it_cs->first;
                    char cs = it_cs->second;
                    if (oneCoordinateSet->isEqualTo(oneFuturCoordinate))
                    {
                        coordonneEnCommun++;

                        intersection[oneFuturCoordinate] = cl;
                        if (fc != cs)
                        {
                            hasNoConflict = false;
                        }
                    }
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

void Crossword::printCrossword()
{
    Coordinate min = Coordinate(0, 0);
    Coordinate max = Coordinate(0, 0);
    std::vector<std::pair<Coordinate *, char>> allCoordinates;
    // for (auto cl : crosswordLines)
    for (auto clPaire : crosswordLinesBis)
    {
        const CrosswordLine *cl = clPaire.second;
        std::map<Coordinate *, char> clCoordinates = cl->getCoordinates();
        for (auto &c : clCoordinates)
        {
            Coordinate *coordinate = c.first;
            min.ifMinUpdate(coordinate);
            max.ifMaxUpdate(coordinate);
        }
        allCoordinates.insert(allCoordinates.cend(), clCoordinates.begin(), clCoordinates.end());
    }
    size_t x = static_cast<size_t>(max.getX() - min.getX() + 1);
    size_t y = static_cast<size_t>(max.getY() - min.getY() + 1);

    std::vector<char> tableau(x * y, '.');

    // for (auto cl : crosswordLines)
    for (auto clPaire : crosswordLinesBis)
    {
        const CrosswordLine *cl = clPaire.second;
        std::map<Coordinate *, char> clCoordinates = cl->getCoordinates();
        for (auto &clc : clCoordinates)
        {
            Coordinate *c = clc.first;
            size_t newX = static_cast<size_t>(c->getX() - min.getX());
            size_t newY = static_cast<size_t>(c->getY() - min.getY());
            char letter = clc.second;
            tableau[newX * y + newY] = letter;
        }
    }
    for (size_t i = 0; i < x; ++i)
    {
        for (size_t j = 0; j < y; ++j)
        {
            std::cout << tableau[i * y + j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
