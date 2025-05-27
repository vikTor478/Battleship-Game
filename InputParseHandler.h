#ifndef INPUTPARSEHANDLER_H
#define INPUTPARSEHANDLER_H

#include <string>
#include <utility>

class InputParseHandler 
{
public:
    static std::pair<int, int> parseCoordinates(const std::string& input);
    static std::string parseToString(int x, int y);
};

#endif