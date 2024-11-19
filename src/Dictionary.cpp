#include "Dictionary.h"

Dictionary::Dictionary(std::string filename)
{
    std::fstream definitionFile;
    definitionFile.open(filename, std::ios::in); // open a file to perform read operation using file object

    if (definitionFile.is_open()) // checking whether the file is open
    {
        std::string line;
        while (getline(definitionFile, line)) // read data from file object and put it into string.
        {
            std::size_t simlicon = line.find(" : ");
            WordDefinition *wd = new WordDefinition(line.substr(0, simlicon), line.substr(simlicon, line.find(".")));
            wordsDefinition.push_back(wd);
        }
        definitionFile.close(); // close the file object.

        std::cout << "nombre de mot : " << wordsDefinition.size() << "\n"; // print the data of the string
    }
}

Dictionary::~Dictionary()
{
}

WordDefinition *Dictionary::getRandomWord()
{
    std::random_device rd;                                              // obtient une graine aléatoire
    std::mt19937 gen(rd());                                             // initialise le générateur avec la graine
    std::uniform_int_distribution<> dis(0, wordsDefinition.size() - 1); // distribution uniforme

    // Sélection aléatoire d'un index
    int randomIndex = dis(gen);
    return wordsDefinition[randomIndex];
}