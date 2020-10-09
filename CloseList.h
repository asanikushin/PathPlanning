//
// Created by anton on 07.02.19.
//

#ifndef PATHPLANNING_CLOSELIST_H
#define PATHPLANNING_CLOSELIST_H

#include "gl_const.h"
#include "Coords.h"
#include "node.h"
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <list>


class CloseList {
public:
    CloseList() = default;

    std::size_t size() const;

    bool empty() const;

    void insert(const Node &current);

    bool contain(const Coords &coord) const;

    bool contain(const Node &node) const;

    bool contain(int i, int j) const;

    Node *operator[](const Coords &coord);

    std::unordered_map<Coords, Node, CoordsHash>::const_iterator begin() const;

    std::unordered_map<Coords, Node, CoordsHash>::const_iterator end() const;


private:

    std::unordered_map<Coords, Node, CoordsHash> _allNodes;
};

#endif //PATHPLANNING_CLOSELIST_H
