#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Dictionary.h"

int main()
{
    std::string inputFile = "./définitions.txt";
    Dictionary *dictionary = new Dictionary(inputFile);
}
