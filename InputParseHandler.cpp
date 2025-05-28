#include "InputParseHandler.h"
#include <cctype>
#include <iostream>

std::pair<int, int> InputParseHandler::parseCoordinates(const std::string& input) 
{
    if (input.length() < 2 || input.length() > 3)
    {
        std::cout << "1\n";
        return { -1, -1 };
    }

    char column = std::toupper(input[0]);
    int row = std::stoi(input.substr(1));

    int x = column - 'A';
    int y = row - 1;

    if (x < 0 || x >= 10 || y < 0 || y >= 10)
    {
        std::cout << "2\n";
        return { -1, -1 };
    }
    
    std::cout<< x << y << "3\n";
    return { x, y };
}