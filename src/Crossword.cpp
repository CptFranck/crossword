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

    // for (auto clPaire : crosswordLines)
    // {
    //     CrosswordLine *cl = clPaire.second;
    //     std::cout << cl->getWordDefinition()->getWord() << std::endl;
    //     std::cout << cl->getCrosswordLineIntersections().size() << std::endl;
    // }
    // std::cout << std::endl;
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
        // crosswordLines[newWordDefinition->getWord()] = new CrosswordLine(randomDirection(), newWordDefinition, new Coordinate(0, 0));
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
    auto maxIntersectionCrosswordLine = std::max_element(potentialsPlacement.begin(), potentialsPlacement.end(),
                                                         [](const CrosswordLine *a, const CrosswordLine *b)
                                                         { return a->getCoordinates().size() <= b->getCoordinates().size(); });

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
    // crosswordLines[newWordDefinition->getWord()] = newCrosswordLine;
    return true;
    // std::cout << "-------------" << std::endl;
    // std::cout << newCrosswordLine->getWordDefinition()->getWord() << " a " << newCrosswordLine->getCrosswordLineIntersections().size() << " relation(s) :" << std::endl;
    // for (auto intersection : newCrosswordLine->getCrosswordLineIntersections())
    // {
    //     Coordinate *c = intersection.first;
    //     CrosswordLine *cl = intersection.second;

    //     if (!cl->hasIntersectionOn(c))
    //     {
    //         cl->addCrosswordLineIntersections(c, newCrosswordLine);
    //         std::cout << "- " << cl->getWordDefinition()->getWord() << std::endl;
    //     }
    // }
    // std::cout << "-------------" << std::endl;
    // std::cout << std::endl;
    // for (auto clPaire : crosswordLines)
    // {
    //     CrosswordLine *cl = clPaire.second;
    //     std::cout << cl->getWordDefinition()->getWord() << std::endl;
    //     std::cout << cl->getCrosswordLineIntersections().size() << std::endl;
    // }
    // std::cout << std::endl;
    // std::cout << std::endl;
}

bool Crossword::isWordDefinitionUsed(WordDefinition *wordDefinition) const
{
    auto isPresentInCrosswordLine = [&wordDefinition](const CrosswordLine *cl)
    {
        return wordDefinition->getWord() == cl->getWordDefinition()->getWord();
    };
    auto it = find_if(crosswordLines.begin(), crosswordLines.end(), isPresentInCrosswordLine);
    return it != crosswordLines.end();
    // return crosswordLines.find(wordDefinition->getWord()) != crosswordLines.end();
}

std::vector<CrosswordLine *> Crossword::findCrosswordLinePlacements(WordDefinition *wordDefinition)
{
    std::vector<CrosswordLine *> allCrosswordLinePlacements;
    for (auto cl : crosswordLines)
    // for (auto clPaire : crosswordLines)
    {
        // CrosswordLine *cl = clPaire.second;
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

        // std::cout << pcl->getWordDefinition()->getWord() << std::endl;

        auto it_cl = crosswordLines.begin();
        while (it_cl != crosswordLines.end() && hasNoConflict)
        {
            int coordonneEnCommun = 0;
            CrosswordLine *cl = *it_cl;
            // CrosswordLine *cl = (*it_cl).second;
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
            // std::cout << "coordonneEnCommun" << std::endl;
            // std::cout << coordonneEnCommun << std::endl;
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
    for (auto cl : crosswordLines)
    // for (auto clPaire : crosswordLines)
    {
        // const CrosswordLine *cl = clPaire.second;
        std::map<Coordinate *, char> clCoordinates = cl->getCoordinates();
        for (auto &c : clCoordinates)
        {
            Coordinate *coordinate = c.first;
            min.ifMinUpdate(coordinate);
            max.ifMaxUpdate(coordinate);
        }
        allCoordinates.insert(allCoordinates.cend(), clCoordinates.begin(), clCoordinates.end());
    }
    int x = max.getX() - min.getX() + 1;
    int y = max.getY() - min.getY() + 1;

    char tableau[x][y];
    for (int i = 0; i < x; ++i)
    {
        for (int j = 0; j < y; ++j)
        {
            tableau[i][j] = '.';
        }
    }

    for (auto cl : crosswordLines)
    // for (auto clPaire : crosswordLines)
    {
        // const CrosswordLine *cl = clPaire.second;
        std::map<Coordinate *, char> clCoordinates = cl->getCoordinates();
        for (auto &clc : clCoordinates)
        {
            Coordinate *c = clc.first;
            int newX = c->getX() - min.getX();
            int newY = c->getY() - min.getY();
            char letter = clc.second;
            tableau[newX][newY] = letter;
        }
    }
    for (int i = 0; i < x; ++i)
    {
        for (int j = 0; j < y; ++j)
        {
            std::cout << tableau[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
