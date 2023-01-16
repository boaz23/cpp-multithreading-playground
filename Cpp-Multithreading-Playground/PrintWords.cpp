#include "PrintWords.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

namespace print_words
{
void run()
{
    char c;
    std::string input;

    std::cout << "Separator: ";
    std::cin.get(c);

    std::cout << "Word: ";
    std::cin >> input;

    bool value{ input == "ff" };
    std::cout << "Value: " << (value ? "true" : "false") << std::endl;

    std::ifstream ifs{ "Text.txt" };
    std::string line;
    while (std::getline(ifs, line))
    {
        std::string word;
        std::istringstream iss{ std::move(line) };
        while (std::getline(iss, word, c))
        {
            std::transform(word.begin(), word.end(), word.begin(), std::tolower);
            std::cout << word << std::endl;
        }
    }
}
}