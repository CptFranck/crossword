#include "Dictionary.h"

Dictionary::Dictionary(std::string filename)
{
    std::fstream definitionFile;
    definitionFile.open(filename, std::ios::in);

    if (definitionFile.is_open())
    {
        std::string line;
        while (getline(definitionFile, line))
        {
            std::size_t simlicon = line.find(" : ");
            WordDefinition wd = WordDefinition(line.substr(0, simlicon), line.substr(simlicon, line.find(".")));
            this->wordDefinitions.push_back(wd);
        }
        definitionFile.close();

        std::cout << "nombre de mot : " << this->wordDefinitions.size() << "\n";
    }
}

Dictionary::~Dictionary()
{
}

WordDefinition Dictionary::getRandomWord()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, static_cast<int>(wordDefinitions.size() - 1));

    size_t randomIndex = static_cast<size_t>(dis(gen));
    return wordDefinitions[randomIndex];
}