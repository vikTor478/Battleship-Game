#ifndef SHIPDATA_H
#define SHIPDATA_H

struct ShipData{
    int length;
    int hits;

    ShipData(int len)
    : length(len), hits(0){}

    bool isSunk() const{
        return hits>=length;
    }
};

#endif