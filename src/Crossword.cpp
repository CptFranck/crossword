#include "Crossword.h"

Crossword::Crossword(Dictionary *dictionary, int wordNumber)
{
    WordDefinition *randomWordDefinition;
    std::vector<CrosswordLine *> potentialsPlacement;

    std::cout << "Creation du mot croisé" << std::endl;

    for (int i = 0; i < wordNumber; i++)
    {
        std::cout << "Mot °" << i + 1 << std::endl;
        for (int tryNumber = 0; tryNumber < 5; tryNumber++)
        {
            std::cout << "Essaie N°" << tryNumber + 1 << std::endl;
            randomWordDefinition = dictionary->getRandomWord();

            if (this->crosswordLines.size() == 0)
            {
                std::cout << "Premier mot enregistrer : " << randomWordDefinition->getWord() << std::endl;
                crosswordLines.push_back(new CrosswordLine(randomDirection(), randomWordDefinition, new Coordinate(0, 0)));
                break;
            }

            if (this->isWordDefinitionUsed(randomWordDefinition))
            {
                std::cout << "Mot déjà utilisé : " << randomWordDefinition->getWord() << std::endl;
                continue;
            }

            potentialsPlacement = findCrosswordLinePlacements(randomWordDefinition);

            if (potentialsPlacement.size() == 0)
            {
                std::cout << "Aucune lettre en commun : " << randomWordDefinition->getWord() << std::endl;
                continue;
            }
            auto maxIntersectionCrosswordLine = std::max_element(potentialsPlacement.begin(), potentialsPlacement.end(),
                                                                 [](const CrosswordLine *a, const CrosswordLine *b)
                                                                 { return a->getCoordinates().size() <= b->getCoordinates().size(); });

            if (maxIntersectionCrosswordLine == potentialsPlacement.end())
            {
                std::cout << "BUG ??" << std::endl;
                for (CrosswordLine *pl : potentialsPlacement)
                    delete pl;
                continue;
            }

            CrosswordLine *newCrosswordLine = *maxIntersectionCrosswordLine;
            for (CrosswordLine *pl : potentialsPlacement)
            {
                if (pl != newCrosswordLine)
                {
                    delete pl;
                }
            }

            std::cout << "Mot ajouté : " << randomWordDefinition->getWord() << std::endl;

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
            tryNumber = 5;
        }
    }
    std::cout << "Mot croisé construit !" << std::endl;
    for (auto cl : this->crosswordLines)
    {
        std::cout << cl->getWordDefinition()->getWord() << std::endl;
        std::cout << cl->getCrosswordLineIntersections().size() << std::endl;
        for (auto cli : cl->getCrosswordLineIntersections())
        {
            cli.first->print();
            std::cout << cli.second->getWordDefinition()->getWord() << std::endl;
        }
    }
    std::cout << std::endl;
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
    return it != crosswordLines.end();
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

    // std::cout << "Nb potentialCrosswordLines :" << potentialCrosswordLines.size() << std::endl;

    for (PotentialCrosswordLine *pcl : potentialCrosswordLines)
    {
        hasNoConflict = true;
        intersection.clear();
        std::map<Coordinate *, char> futureCoordinates = pcl->getCoordinates();
        // std::cout << "----------" << std::endl;
        // std::cout << pcl->getWordDefinition()->getWord() << std::endl;
        // for (auto test : futureCoordinates)
        // {
        //     std::cout << test.second << std::endl;
        //     test.first->print();
        // }
        // std::cout << "----------" << std::endl;
        auto it_cl = crosswordLines.begin();
        while (it_cl != crosswordLines.end() && hasNoConflict)
        {
            CrosswordLine *cl = *it_cl;
            std::map<Coordinate *, char> coordinateSet = cl->getCoordinates();

            // std::cout << "__________" << std::endl;
            // for (auto testBis : coordinateSet)
            // {
            //     std::cout << testBis.second << std::endl;
            //     testBis.first->print();
            // }
            // std::cout << "__________" << std::endl;

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
            std::cout << "Nb intersection :" << intersection.size() << std::endl;
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
    for (const CrosswordLine *cl : crosswordLines)
    {
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

    std::cout << "Min :" << std::endl;
    min.print();
    std::cout << "Max :" << std::endl;
    max.print();
    std::cout << x << " " << y << std::endl;
    std::cout << std::endl;

    char tableau[x][y];
    for (int i = 0; i < x; ++i)
    {
        for (int j = 0; j < y; ++j)
        {
            tableau[i][j] = '.';
        }
    }

    //-----------------------------------------
    for (const CrosswordLine *cl : crosswordLines)
    {
        std::map<Coordinate *, char> clCoordinates = cl->getCoordinates();
        for (auto &clc : clCoordinates)
        {
            Coordinate *c = clc.first;
            int newX = c->getX() - min.getX();
            int newY = c->getY() - min.getY();
            char letter = clc.second;
            tableau[newX][newY] = letter;
            c->print();
            std::cout << "new x : " << newX << " new y : " << newY << "  " << letter << std::endl;
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
        // allCoordinates.insert(allCoordinates.cend(), clCoordinates.begin(), clCoordinates.end());
    }
    //-----------------------------------------

    // for (auto coordinateLetter : allCoordinates)
    // {
    //     Coordinate *c = coordinateLetter.first;
    //     int newX = c->getX() + x - 1;
    //     int newY = c->getY() + y - 1;
    //     // c->print();
    //     // std::cout << "new x : " << newX << " new y : " << newY << std::endl;
    //     char letter = coordinateLetter.second;
    //     tableau[newX][newY] = letter;
    // }

    // for (int i = 0; i < x; ++i)
    // {
    //     for (int j = 0; j < y; ++j)
    //     {
    //         std::cout << tableau[i][j];
    //     }
    //     std::cout << std::endl;
    // }
}
