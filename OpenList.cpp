//
// Created by anton on 06.12.18.
//

#include "OpenList.h"

std::size_t OpenList::size() const {
    return _allNodes.size();
}

bool OpenList::empty() const {
    return size() == 0;
}

void OpenList::insert(const Node &current) {
    Coords coord = current;

    if (contain(coord)) {
        Node old = _allNodes[coord];

        if (old.F < current.F) {
            return;
        }

        if (old.F == current.F && get_relevant_g(old.g) <= get_relevant_g(current.g)) {
            return;;
        }

        erase(current);
    }

    _allNodes[coord] = current;
    _sortedNodes.insert({{current.F, get_relevant_g(current.g)}, coord});
}

void OpenList::erase(Coords coord) {
    Node node = _allNodes[coord];
    _sortedNodes.erase({{node.F, get_relevant_g(node.g)}, coord});
    _allNodes.erase(coord);
}

void OpenList::erase(const Node &node) {
    if (contain(node)) {
        erase({node.i, node.j});
    }
}


bool OpenList::contain(const Coords &coord) const {
    return _allNodes.count(coord) != 0;
}

bool OpenList::contain(const Node &node) const {
    return contain(node.i, node.j);
}

bool OpenList::contain(int i, int j) const {
    return contain({i, j});
}

Node OpenList::getMinimum() const {
    return _allNodes.at(_sortedNodes.begin()->second);
}

void OpenList::setBreakingties(bool breakingties) {
    breakingties_flag = breakingties;
}

Node *OpenList::operator[](const Coords &coord) {
    return &_allNodes[coord];
}

std::unordered_map<Coords, Node, CoordsHash>::const_iterator OpenList::begin() const {
    return _allNodes.begin();
}

std::unordered_map<Coords, Node, CoordsHash>::const_iterator OpenList::end() const {
    return _allNodes.end();
}