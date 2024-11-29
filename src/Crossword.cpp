#include "Crossword.h"

Crossword::Crossword(std::shared_ptr<Dictionary> dictionary, int wordNumber)
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
}

bool Crossword::findNewCrosswordLine(std::shared_ptr<Dictionary> dictionary)
{
    WordDefinition newWordDefinition = dictionary.get()->getRandomWord();

    if (this->crosswordLines.size() == 0)
    {
        std::cout << "Premier mot enregistrer : " << newWordDefinition.getWord() << std::endl;
        this->crosswordLines[newWordDefinition.getWord()] = std::make_shared<CrosswordLine>(randomDirection(), newWordDefinition, Coordinate(0, 0));
        return true;
    }

    if (isWordDefinitionUsed(newWordDefinition))
    {
        std::cout << "Mot déjà utilisé : " << newWordDefinition.getWord() << std::endl;
        return false;
    }

    std::vector<std::shared_ptr<CrosswordLine>> potentialsPlacement = findCrosswordLinePlacements(newWordDefinition);

    if (potentialsPlacement.size() == 0)
    {
        std::cout << "Aucune lettre en commun " << newWordDefinition.getWord() << std::endl;
        return false;
    }

    auto maxIntersectionCrosswordLine = std::max_element(potentialsPlacement.begin(),
                                                         potentialsPlacement.end(),
                                                         [](const std::shared_ptr<CrosswordLine> a, const std::shared_ptr<CrosswordLine> b)
                                                         { return a->getCrosswordLineIntersections().size() <=
                                                                  b->getCrosswordLineIntersections().size(); });

    if (maxIntersectionCrosswordLine == potentialsPlacement.end())
    {
        std::cout << "BUG" << std::endl;
        return false;
    }

    std::shared_ptr<CrosswordLine> newCrosswordLine = *maxIntersectionCrosswordLine;
    this->crosswordLines[newWordDefinition.getWord()] = newCrosswordLine;
    std::cout << "Mot ajouté : " << newWordDefinition.getWord() << std::endl;
    return true;
}

bool Crossword::isWordDefinitionUsed(WordDefinition wordDefinition) const
{
    return this->crosswordLines.find(wordDefinition.getWord()) != this->crosswordLines.end();
}

std::vector<std::shared_ptr<CrosswordLine>> Crossword::findCrosswordLinePlacements(WordDefinition wordDefinition)
{
    std::vector<std::shared_ptr<CrosswordLine>> allCrosswordLinePlacements;
    for (auto &clPaire : this->crosswordLines)
    {
        std::shared_ptr<CrosswordLine> cl = clPaire.second;
        std::vector<std::shared_ptr<PotentialCrosswordLine>> potentialCrosswordLines = cl->findPotentialCrosswordLine(wordDefinition);
        std::vector<std::shared_ptr<CrosswordLine>> crosswordLinePlacements = filterPotentialCrosswordLineConflicted(potentialCrosswordLines);
        allCrosswordLinePlacements.insert(allCrosswordLinePlacements.end(), crosswordLinePlacements.begin(), crosswordLinePlacements.end());
    }
    return allCrosswordLinePlacements;
}

std::vector<std::shared_ptr<CrosswordLine>> Crossword::filterPotentialCrosswordLineConflicted(std::vector<std::shared_ptr<PotentialCrosswordLine>> potentialCrosswordLines)
{
    bool hasNoConflict;
    std::map<Coordinate, std::shared_ptr<CrosswordLine>> intersection;
    std::vector<std::shared_ptr<CrosswordLine>> workingPotentialCrosswordLinesWithScore;

    for (auto &pcl : potentialCrosswordLines)
    {
        hasNoConflict = true;
        intersection.clear();
        std::map<Coordinate, char> futureCoordinates = pcl->getCoordinates();

        auto it_cl = this->crosswordLines.begin();
        while (it_cl != this->crosswordLines.end() && hasNoConflict)
        {
            int coordonneEnCommun = 0;
            std::shared_ptr<CrosswordLine> cl = (*it_cl).second;
            std::map<Coordinate, char> coordinateSet = cl->getCoordinates();
            for (auto it_fc = futureCoordinates.begin(); it_fc != futureCoordinates.end(); ++it_fc)
            {
                Coordinate oneFuturCoordinate = it_fc->first;
                char fc = it_fc->second;
                for (auto it_cs = coordinateSet.begin(); it_cs != coordinateSet.end(); ++it_cs)
                {
                    Coordinate oneCoordinateSet = it_cs->first;
                    char cs = it_cs->second;
                    if (oneCoordinateSet.isEqualTo(oneFuturCoordinate))
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
            workingPotentialCrosswordLinesWithScore.push_back(std::make_shared<CrosswordLine>(pcl, intersection));
        }
    }
    return workingPotentialCrosswordLinesWithScore;
}

void Crossword::printCrossword()
{
    Coordinate min = Coordinate(0, 0);
    Coordinate max = Coordinate(0, 0);
    std::vector<std::pair<Coordinate, char>> allCoordinates;
    for (auto &clPaire : this->crosswordLines)
    {
        const std::shared_ptr<CrosswordLine> cl = clPaire.second;
        std::map<Coordinate, char> clCoordinates = cl->getCoordinates();
        for (auto &c : clCoordinates)
        {
            Coordinate coordinate = c.first;
            min.ifMinUpdate(coordinate);
            max.ifMaxUpdate(coordinate);
        }
        allCoordinates.insert(allCoordinates.cend(), clCoordinates.begin(), clCoordinates.end());
    }
    size_t x = static_cast<size_t>(max.getX() - min.getX() + 1);
    size_t y = static_cast<size_t>(max.getY() - min.getY() + 1);

    std::vector<char> tableau(x * y, '.');

    for (auto &clPaire : this->crosswordLines)
    {
        const std::shared_ptr<CrosswordLine> cl = clPaire.second;
        std::map<Coordinate, char> clCoordinates = cl->getCoordinates();
        for (auto &clc : clCoordinates)
        {
            Coordinate c = clc.first;
            size_t newX = static_cast<size_t>(c.getX() - min.getX());
            size_t newY = static_cast<size_t>(c.getY() - min.getY());
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
