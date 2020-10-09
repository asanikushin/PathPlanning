//
// Created by anton on 21.01.19.
//

#include "theta.h"


namespace {
    double dist(Node *a, Node *b) {
        return sqrt((b->i - a->i) * (b->i - a->i) + (b->j - a->j) * (b->j - a->j));
    }
}


Theta::Theta(double HW, bool BT) : Astar(HW, BT) {}


bool Theta::isOnSight(Node *curNode, Node *neighbour, const Map &map, const EnvironmentOptions &options) const {
    Coords start(*curNode), end(*neighbour);
    int di = neighbour->i - curNode->i;
    int dj = neighbour->j - curNode->j;

    int si = 1;
    int sj = 1;

    if (di < 0) {
        di *= -1;
        si = -1;
    }
    if (dj < 0) {
        dj *= -1;
        sj = -1;
    }

    int f = 0;
    if (di > dj) {
        for (; start.i != end.i; start.i += si) {
            if (map.CellIsObstacle(start.i, start.j)) {
                return false;
            }
            f += dj;
            if (f > di) {
                start.j += sj;
                f -= di;
            }
        }
        if (map.CellIsObstacle(start.i, start.j)) {
            return false;
        }
    } else {
        for (; start.j != end.j; start.j += sj) {
            if (map.CellIsObstacle(start.i, start.j)) {
                return false;
            }
            f += di;
            if (f > dj) {
                start.i += si;
                f -= dj;
            }
        }
        if (map.CellIsObstacle(start.i, start.j)) {
            return false;
        }
    }

    return true;
}

void Theta::updateNodesParent(Node *curNode, Node *neighbour, const Map &map, const EnvironmentOptions &options) const {
    if (curNode->parent && neighbour != curNode->parent &&
        isOnSight(curNode->parent, neighbour, map, options)) {

        neighbour->g = curNode->parent->g + dist(curNode->parent, neighbour);
        neighbour->parent = curNode->parent;
    }
}


// First path use parents for nodes, in this case it is sections of one line
void Theta::makePrimaryPath(Node curNode) {
    Node current = curNode;
    while (current.parent) {
        hppath.push_front(current);
        current = *current.parent;
    }
    hppath.push_front(current);
}

// Second path contains all node on path
void Theta::makeSecondaryPath() {
    Node begin = *hppath.begin();
    Node end = *(hppath.begin()++);
    Node inBetween;

    // First to pre-last section
    for (auto iter = ++hppath.begin(), before = hppath.begin(); before != hppath.end(); ++iter, ++before) {
        int di = end.i - begin.i;
        int dj = end.j - begin.j;

        int si = 1;
        int sj = 1;

        if (di < 0) {
            di *= -1;
            si = -1;
        }
        if (dj < 0) {
            dj *= -1;
            sj = -1;
        }

        int f = 0;
        if (di > dj) {
            inBetween.j = begin.j;
            for (inBetween.i = begin.i; inBetween.i != end.i; inBetween.i += si) {
                lppath.push_back(inBetween);
                f += dj;
                if (f >= di) {
                    inBetween.j += sj;
                    f -= di;
                }
            }
        } else {
            inBetween.i = begin.i;
            for (inBetween.j = begin.j; inBetween.j != end.j; inBetween.j += sj) {
                lppath.push_back(inBetween);
                f += di;
                if (f >= dj) {
                    inBetween.i += si;
                    f -= dj;
                }
            }
        }
        begin = end;
        end = *iter;
    }
}
