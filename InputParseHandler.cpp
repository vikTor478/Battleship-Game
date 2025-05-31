#include "InputParseHandler.h"
#include <cctype>
#include <iostream>

std::pair<int, int> InputParseHandler::parseCoordinates(const std::string& input, int boardSize) 
{
    if (input.length() < 2 || input.length() > 3)
    {
        return { -1, -1 };
    }

    char column = std::toupper(input[0]);
    int row = std::stoi(input.substr(1));

    int x = column - 'A';
    int y = row - 1;

    if (x < 0 || x >= boardSize || y < 0 || y >= boardSize)
    {
        return { -1, -1 };
    }
    
    return { x, y };
}

std::string InputParseHandler::parseToString(int x, int y, int boardSize)
{
    if (x < 0 || x >= boardSize || y < 0 || y >= boardSize) 
    {
        throw std::out_of_range("Coordinates out of board range");
    }

    char column = 'A' + x;
    int row = y + 1;

    return std::string(1, column) + std::to_string(row);
}