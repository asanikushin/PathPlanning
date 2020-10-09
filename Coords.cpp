//
// Created by anton on 06.12.18.
//

#include "Coords.h"

bool Coords::operator==(const Coords &obj) const {
    return obj.i == i && obj.j == j;
}

bool Coords::operator<(const Coords &obj) const {
    return std::pair<int, int>(i, j) < std::pair<int, int>(obj.i, obj.j);
}

std::size_t CoordsHash::operator()(const Coords &obj) const {
    auto hash = static_cast<std::size_t>(obj.i);
    hash <<= 32;
    hash |= static_cast<std::size_t>(obj.j);
    return hash;
}