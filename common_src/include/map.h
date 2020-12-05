#ifndef MAP_H
#define MAP_H

#include <vector>

enum class Type {
    empty, door, wall, fakeDoor, keyDoor
};

class Map {
public:

    Map(unsigned rowSize, unsigned colSize);

    unsigned getRowSize() const;

    unsigned getColSize() const;

    Type &operator()(const unsigned rowNumber, const unsigned colNumber);

    ~Map();

private:
    unsigned rowSize;
    unsigned colSize;
    std::vector<std::vector<Type>> map;
};

#endif //MAP_H
