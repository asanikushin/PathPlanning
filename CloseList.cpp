//
// Created by anton on 07.02.19.
//

#include "CloseList.h"


std::size_t CloseList::size() const {
    return _allNodes.size();
}

bool CloseList::empty() const {
    return _allNodes.empty();
}

void CloseList::insert(const Node &current) {
    Coords coord = current;
    _allNodes[coord] = current;
}


bool CloseList::contain(const Coords &coord) const {
    return _allNodes.count(coord) != 0;
}

bool CloseList::contain(const Node &node) const {
    return contain(node.i, node.j);
}

bool CloseList::contain(int i, int j) const {
    return contain({i, j});
}

Node *CloseList::operator[](const Coords &coord) {
    return &_allNodes[coord];
}

std::unordered_map<Coords, Node, CoordsHash>::const_iterator CloseList::begin() const {
    return _allNodes.begin();
}

std::unordered_map<Coords, Node, CoordsHash>::const_iterator CloseList::end() const {
    return _allNodes.end();
}