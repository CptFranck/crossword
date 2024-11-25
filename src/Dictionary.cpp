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
            this->wordDefinitions.push_back(wd);
        }
        definitionFile.close(); // close the file object.

        std::cout << "nombre de mot : " << this->wordDefinitions.size() << "\n"; // print the data of the string
    }
}

Dictionary::~Dictionary()
{
    for (WordDefinition *wd : this->wordDefinitions)
    {
        delete wd;
    }
}

WordDefinition *Dictionary::getRandomWord()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, static_cast<int>(wordDefinitions.size() - 1));

    // Sélection aléatoire d'un index
    size_t randomIndex = static_cast<size_t>(dis(gen));
    return wordDefinitions[randomIndex];
}