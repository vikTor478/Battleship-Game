#ifndef SHIPDATA_H
#define SHIPDATA_H

#include <vector>

struct ShipData 
{
    std::vector<std::pair<int, int>> coordinates;
    int hits = 0;

    ShipData(int startX, int startY, int length, bool isHorizontal) 
    {
        for (int i = 0; i < length; ++i) 
        {
            if (isHorizontal) 
            {
                coordinates.emplace_back(startX + i, startY);
            } 
            else 
            {
                coordinates.emplace_back(startX, startY + i);
            }
        }
    }

    bool isSunk() const 
    {
        return hits >= coordinates.size();
    }

    bool contains(int x, int y) const 
    {
        for (auto& coord : coordinates) 
        {
            if (coord.first == x && coord.second == y)
                return true;
        }
        return false;
    }
};


#endif