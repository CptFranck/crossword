#include "Crossword.h"

Crossword::Crossword(std::shared_ptr<Dictionary> dictionary, int wordNumber, int dimension) : dimension(dimension), min(Coordinate(0, 0)), max(Coordinate(0, 0))
{
    std::cout << "Creation du mot croisé" << std::endl;

    bool wordFound;
    for (int i = 0; i < wordNumber; i++)
    {
        wordFound = false;
        std::cout << "Mot °" << i + 1 << std::endl;
        for (int trialNumber = 0; trialNumber < 5 && !wordFound; trialNumber++)
        {
            // std::cout << "Essaie N°" << trialNumber + 1 << std::endl;
            wordFound = this->findNewCrosswordLine(dictionary);
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
        this->addCrosswordLine(newWordDefinition.getWord(), CrosswordLine(randomDirection(), newWordDefinition, Coordinate(0, 0)));
        return true;
    }

    if (isWordDefinitionUsed(newWordDefinition))
    {
        // std::cout << "Mot déjà utilisé : " << newWordDefinition.getWord() << std::endl;
        return false;
    }

    std::vector<CrosswordLine> potentialsPlacement = this->findCrosswordLinePlacements(newWordDefinition);

    if (potentialsPlacement.size() == 0)
    {
        // std::cout << "Aucune lettre en commun " << newWordDefinition.getWord() << std::endl;
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
    this->addCrosswordLine(newWordDefinition.getWord(), newCrosswordLine);
    std::cout << "Mot ajouté : " << newWordDefinition.getWord() << std::endl;
    return true;
}

std::vector<CrosswordLine> Crossword::findCrosswordLinePlacements(WordDefinition wordDefinition)
{
    std::vector<CrosswordLine> allCrosswordLinePlacements;
    for (const auto &[_, cl] : this->crosswordLines)
    {
        std::vector<PotentialCrosswordLine> potentialCrosswordLines = cl.findPotentialCrosswordLine(wordDefinition);
        std::vector<CrosswordLine> crosswordLinePlacements = this->filterPotentialCrosswordLineConflicted(potentialCrosswordLines);
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
        for (const auto &[_, cl] : this->crosswordLines)
        {
            if (this->hasConflictsOnSameCoordinate(pcl, cl, intersection) ||
                this->DoNotRespectCrosswordDimension(pcl))
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

void Crossword::addCrosswordLine(std::string wd, CrosswordLine cl)
{
    this->crosswordLines.emplace(wd, cl);
    std::map<Coordinate, std::pair<wchar_t, size_t>> clCoordinates = cl.getCoordinates();
    for (auto &[coordinate, __] : clCoordinates)
    {
        min.ifMinUpdate(coordinate);
        max.ifMaxUpdate(coordinate);
    }
}

bool Crossword::isWordDefinitionUsed(WordDefinition wordDefinition) const
{
    return this->crosswordLines.find(wordDefinition.getWord()) != this->crosswordLines.end();
}

bool Crossword::hasConflictsOnSameCoordinate(const PotentialCrosswordLine pcl,
                                             const CrosswordLine cl,
                                             std::map<Coordinate, CrosswordLine> &intersection) const
{
    std::map<Coordinate, std::pair<wchar_t, size_t>> futureCoordinates = pcl.getCoordinates();
    std::map<Coordinate, std::pair<wchar_t, size_t>> coordinateSet = cl.getCoordinates();
    for (const auto &[coord, pair] : coordinateSet)
    {
        const auto &[character, position] = pair;
        if (position == 0)
        {
            auto it = futureCoordinates.find(coord.getPositionFrom(-1, cl.getDirection()));
            if (it != futureCoordinates.end())
            {
                return true;
            }
        }

        if (position == coordinateSet.size() - 1)
        {
            auto it = futureCoordinates.find(coord.getPositionFrom(1, cl.getDirection()));
            if (it != futureCoordinates.end())
            {
                return true;
            }
        }
        auto it = futureCoordinates.find(coord);
        if (it != futureCoordinates.end())
        {
            intersection.emplace(coord, cl);
            if (std::towlower(this->removeAccents(character)) != std::towlower(this->removeAccents(it->second.first)))
            {
                return true;
            }
        }
    }

    for (const auto &[coordBis, pairBis] : futureCoordinates)
    {
        const auto &[characterBis, positionBis] = pairBis;
        if (positionBis == 0)
        {
            auto it = coordinateSet.find(coordBis.getPositionFrom(-1, pcl.getDirection()));
            if (it != coordinateSet.end())
            {
                return true;
            }
        }

        if (positionBis == futureCoordinates.size() - 1)
        {
            auto it = coordinateSet.find(coordBis.getPositionFrom(1, pcl.getDirection()));
            if (it != coordinateSet.end())
            {
                return true;
            }
        }
    }
    return false;
}

wchar_t Crossword::removeAccents(const wchar_t input) const
{
    wchar_t output;
    switch (input)
    {
    // Lettres minuscules
    case L'á':
    case L'à':
    case L'â':
    case L'ä':
    case L'ã':
    case L'å':
    case L'ā':
        output = L'a';
        break;
    case L'é':
    case L'è':
    case L'ê':
    case L'ë':
    case L'ē':
    case L'ė':
    case L'ę':
        output = L'e';
        break;
    case L'í':
    case L'ì':
    case L'î':
    case L'ï':
    case L'ī':
    case L'į':
        output = L'i';
        break;
    case L'ó':
    case L'ò':
    case L'ô':
    case L'ö':
    case L'õ':
    case L'ø':
    case L'ō':
        output = L'o';
        break;
    case L'ú':
    case L'ù':
    case L'û':
    case L'ü':
    case L'ū':
        output = L'u';
        break;
    case L'ý':
    case L'ÿ':
        output = L'y';
        break;
    case L'ç':
        output = L'c';
        break;
    case L'ñ':
        output = L'n';
        break;

    // Lettres majuscules
    case L'Á':
    case L'À':
    case L'Â':
    case L'Ä':
    case L'Ã':
    case L'Å':
    case L'Ā':
        output = L'A';
        break;
    case L'É':
    case L'È':
    case L'Ê':
    case L'Ë':
    case L'Ē':
    case L'Ė':
    case L'Ę':
        output = L'E';
        break;
    case L'Í':
    case L'Î':
    case L'Ï':
    case L'Ī':
    case L'Į':
    case L'Ì':
        output = L'I';
        break;
    case L'Ó':
    case L'Ò':
    case L'Ô':
    case L'Ö':
    case L'Õ':
    case L'Ø':
    case L'Ō':
        output = L'O';
        break;
    case L'Ú':
    case L'Ù':
    case L'Û':
    case L'Ü':
    case L'Ū':
        output = L'U';
        break;
    case L'Ý':
        output = L'Y';
        break;
    case L'Ç':
        output = L'C';
        break;
    case L'Ñ':
        output = L'N';
        break;
    default:
        output = input;
        break; // Garde les caractères non accentués ou inconnus
    }
    return output;
}

bool Crossword::DoNotRespectCrosswordDimension(PotentialCrosswordLine pcl)
{
    Coordinate localMin = this->min;
    Coordinate localMax = this->max;
    std::map<Coordinate, std::pair<wchar_t, size_t>> pclCoordinates = pcl.getCoordinates();
    for (auto &[coordinate, __] : pclCoordinates)
    {
        localMin.ifMinUpdate(coordinate);
        localMax.ifMaxUpdate(coordinate);
    }
    int x = localMax.getX() - localMin.getX() + 1;
    int y = localMax.getY() - localMin.getY() + 1;

    if (this->dimension < x || this->dimension < y)
        return true;
    return false;
}

void Crossword::printCrossword()
{
    std::vector<std::pair<Coordinate, std::pair<wchar_t, size_t>>> allCoordinates;
    for (auto &[_, cl] : this->crosswordLines)
    {
        std::map<Coordinate, std::pair<wchar_t, size_t>> clCoordinates = cl.getCoordinates();
        for (auto &[coordinate, __] : clCoordinates)
        {
            this->min.ifMinUpdate(coordinate);
            this->max.ifMaxUpdate(coordinate);
        }
        allCoordinates.insert(allCoordinates.cend(), clCoordinates.begin(), clCoordinates.end());
    }
    size_t x = static_cast<size_t>(this->max.getX() - this->min.getX() + 1);
    size_t y = static_cast<size_t>(this->max.getY() - this->min.getY() + 1);

    std::vector<wchar_t> tableau(x * y, L'_');
    for (auto &[_, cl] : this->crosswordLines)
    {
        std::map<Coordinate, std::pair<wchar_t, size_t>> clCoordinates = cl.getCoordinates();
        for (auto &[c, pair] : clCoordinates)
        {
            const auto &[character, __] = pair;
            size_t newX = static_cast<size_t>(c.getX() - this->min.getX());
            size_t newY = static_cast<size_t>(c.getY() - this->min.getY());
            tableau[newX * y + newY] = character;
        }
    }
    for (size_t i = 0; i < x; i++)
    {
        for (size_t j = y; 0 < j; j--)
        {
            std::wcout << tableau[i * y + (j - 1)];
        }

        std::cout << std::endl;
    }
    std::cout << std::endl;
}
