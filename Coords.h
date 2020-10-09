//
// Created by anton on 06.12.18.
//

#ifndef PATHPLANNING_COORDS_H
#define PATHPLANNING_COORDS_H

#include "node.h"
#include <utility>

class Coords {
public:
    Coords() = default;

    Coords(const Coords &other) = default;

    Coords(const Node &node) : i(node.i), j(node.j) {}

    Coords(int i, int j) : i(i), j(j) {}

    bool operator==(const Coords &other) const;

    bool operator<(const Coords &other) const;

    int i;
    int j;
};

class CoordsHash {
public:
    std::size_t operator()(const Coords &obj) const;
};

#endif //PATHPLANNING_COORDS_H
