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
        this->crosswordLines.emplace(newWordDefinition.getWord(), CrosswordLine(randomDirection(), newWordDefinition, Coordinate(0, 0)));
        return true;
    }

    if (isWordDefinitionUsed(newWordDefinition))
    {
        std::cout << "Mot déjà utilisé : " << newWordDefinition.getWord() << std::endl;
        return false;
    }

    std::vector<CrosswordLine> potentialsPlacement = findCrosswordLinePlacements(newWordDefinition);

    if (potentialsPlacement.size() == 0)
    {
        std::cout << "Aucune lettre en commun " << newWordDefinition.getWord() << std::endl;
        return false;
    }

    auto maxIntersectionCrosswordLine = std::max_element(potentialsPlacement.begin(),
                                                         potentialsPlacement.end(),
                                                         [](const CrosswordLine a, const CrosswordLine b)
                                                         { return a.getCrosswordLineIntersections().size() <=
                                                                  b.getCrosswordLineIntersections().size(); });

    if (maxIntersectionCrosswordLine == potentialsPlacement.end())
    {
        std::cout << "BUG" << std::endl;
        return false;
    }

    CrosswordLine newCrosswordLine = *maxIntersectionCrosswordLine;
    this->crosswordLines.emplace(newWordDefinition.getWord(), newCrosswordLine);
    std::cout << "Mot ajouté : " << newWordDefinition.getWord() << std::endl;
    return true;
}

bool Crossword::isWordDefinitionUsed(WordDefinition wordDefinition) const
{
    return this->crosswordLines.find(wordDefinition.getWord()) != this->crosswordLines.end();
}

std::vector<CrosswordLine> Crossword::findCrosswordLinePlacements(WordDefinition wordDefinition)
{
    std::vector<CrosswordLine> allCrosswordLinePlacements;
    for (auto &clPaire : this->crosswordLines)
    {
        std::vector<PotentialCrosswordLine> potentialCrosswordLines = clPaire.second.findPotentialCrosswordLine(wordDefinition);
        std::vector<CrosswordLine> crosswordLinePlacements = filterPotentialCrosswordLineConflicted(potentialCrosswordLines);
        allCrosswordLinePlacements.insert(allCrosswordLinePlacements.end(), crosswordLinePlacements.begin(), crosswordLinePlacements.end());
    }
    return allCrosswordLinePlacements;
}

std::vector<CrosswordLine> Crossword::filterPotentialCrosswordLineConflicted(std::vector<PotentialCrosswordLine> potentialCrosswordLines)
{
    bool hasNoConflict;
    std::map<Coordinate, CrosswordLine> intersection;
    std::vector<CrosswordLine> workingPotentialCrosswordLinesWithScore;

    for (auto &pcl : potentialCrosswordLines)
    {
        hasNoConflict = true;
        intersection.clear();
        std::map<Coordinate, wchar_t> futureCoordinates = pcl.getCoordinates();

        for (const auto &[_, cl] : crosswordLines)
        {
            std::map<Coordinate, wchar_t> coordinateSet = cl.getCoordinates();
            if (!checkConflicts(futureCoordinates, coordinateSet, intersection, cl))
            {
                hasNoConflict = false;
                break;
            }
        }
        if (hasNoConflict)
        {
            workingPotentialCrosswordLinesWithScore.push_back(CrosswordLine(pcl, intersection));
        }
    }
    return workingPotentialCrosswordLinesWithScore;
}

bool Crossword::checkConflicts(const std::map<Coordinate, wchar_t> futureCoordinates,
                               const std::map<Coordinate, wchar_t> coordinateSet,
                               std::map<Coordinate, CrosswordLine> &intersection,
                               const CrosswordLine cl)
{
    for (const auto &[futureCoord, futureChar] : futureCoordinates)
    {
        auto it = coordinateSet.find(futureCoord);
        if (it != coordinateSet.end())
        {
            intersection.emplace(futureCoord, cl);
            if (futureChar != it->second)
            {
                return false;
            }
        }
    }
    return true;
}

void Crossword::printCrossword()
{
    Coordinate min = Coordinate(0, 0);
    Coordinate max = Coordinate(0, 0);
    std::vector<std::pair<Coordinate, wchar_t>> allCoordinates;
    for (auto &clPaire : this->crosswordLines)
    {
        const CrosswordLine cl = clPaire.second;
        std::map<Coordinate, wchar_t> clCoordinates = cl.getCoordinates();
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

    std::vector<wchar_t> tableau(x * y, L'.');

    for (auto &clPaire : this->crosswordLines)
    {
        const CrosswordLine cl = clPaire.second;
        std::map<Coordinate, wchar_t> clCoordinates = cl.getCoordinates();
        for (auto &clc : clCoordinates)
        {
            Coordinate c = clc.first;
            size_t newX = static_cast<size_t>(c.getX() - min.getX());
            size_t newY = static_cast<size_t>(c.getY() - min.getY());
            wchar_t letter = clc.second;
            tableau[newX * y + newY] = letter;
        }
    }

    for (size_t i = 0; i < x; ++i)
    {
        for (size_t j = 0; j < y; ++j)
        {
            std::wcout << tableau[i * y + j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
