#include <fstream>
#include <string>
#include <vector>

#include "Dictionary.h"
#include "Crossword.h"

int main()
{
    std::string inputFile = "./définitions.txt";
    Dictionary *dictionary = new Dictionary(inputFile);
    Crossword *crossword = new Crossword(dictionary, 10);
    return 0;
}
