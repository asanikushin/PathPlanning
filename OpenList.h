//
// Created by anton on 06.12.18.
//

#ifndef PATHPLANNING_OPENCLOSELISTS_H
#define PATHPLANNING_OPENCLOSELISTS_H

#include "gl_const.h"
#include "Coords.h"
#include "node.h"
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <list>


class OpenList {
public:
    OpenList() = default;

    std::size_t size() const;

    bool empty() const;

    void insert(const Node &current);

    void erase(const Node &node);

    bool contain(const Coords &coord) const;

    bool contain(const Node &node) const;

    bool contain(int i, int j) const;

    Node getMinimum() const;

    Node *operator[](const Coords &coord);

    void setBreakingties(bool breakingties);

    std::unordered_map<Coords, Node, CoordsHash>::const_iterator begin() const;

    std::unordered_map<Coords, Node, CoordsHash>::const_iterator end() const;


private:
    void erase(Coords coord);

    double get_relevant_g(double g) const {
        if (breakingties_flag == CN_SP_BT_GMIN) {
            return g;
        } else {
            return -g;
        }
    }

    bool breakingties_flag = false;
    std::unordered_map<Coords, Node, CoordsHash> _allNodes;
    std::set<std::pair<std::pair<double, double>, Coords>> _sortedNodes; // <<node.f, node.g>, coords of node>
};


#endif //PATHPLANNING_OPENCLOSELISTS_H
