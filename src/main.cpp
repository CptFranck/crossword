#include "Dictionary.h"
#include "Crossword.h"
#include <memory>
int main()
{
    std::string inputFile = "./définitions.txt";
    std::shared_ptr<Dictionary> dictionary = std::make_shared<Dictionary>(inputFile);
    std::unique_ptr<Crossword> crossword = std::make_unique<Crossword>(dictionary, 10);
    return 0;
}
