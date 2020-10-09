//
// Created by anton on 11.03.19.
//

#include "jps.h"

namespace {
    constexpr int moveDx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
    constexpr int moveDy[] = {0, -1, -1, -1, 0, 1, 1, 1};
    constexpr int DIR_CNT = sizeof(moveDx) / sizeof(int);

    double dist(Node *a, Node *b) {
        return sqrt((b->i - a->i) * (b->i - a->i) + (b->j - a->j) * (b->j - a->j));
    }

    int direction(int from, int to) {
        return ((from < to) ? 1 : ((from > to) ? -1 : 0));
    }

    Node jump(Node neighbor, Node *curNode, const Map &map, const EnvironmentOptions &options) {
        int dx = direction(neighbor.parent->i, neighbor.i); // run direction
        int dy = direction(neighbor.parent->j, neighbor.j);

        while (true) {
            int x = neighbor.i;
            int y = neighbor.j;


            if (!map.CellIsTraversable(x, y)) {
                return {-1, -1, nullptr};
            }

            if ((Coords) neighbor == map.getGoalCoords()) {
                return neighbor;
            }


            if (dx != 0 && dy != 0) { // forced from diagonal
                if ((map.CellIsTraversable(x - dx, y + dy) && map.CellIsObstacle(x - dx, y)) ||
                    (map.CellIsTraversable(x + dx, y - dy) && map.CellIsObstacle(x, y - dy))) {
                    return neighbor;
                }
                auto jumper = jump(Node(x + dx, y, &neighbor), curNode, map, options);
                if (map.CellIsTraversable(jumper.i, jumper.j)) { // horizontal
                    return neighbor;
                }
                jumper = jump(Node(x, y + dy, &neighbor), curNode, map, options);
                if (map.CellIsTraversable(jumper.i, jumper.j)) { // vertical
                    return neighbor;
                }

            } else if (dy == 0) { // forced from horizontal
                if ((map.CellIsTraversable(x + dx, y + 1) && map.CellIsObstacle(x, y + 1)) ||
                    (map.CellIsTraversable(x + dx, y - 1) && map.CellIsObstacle(x, y - 1))) {
                    return neighbor;
                }
            } else if (dx == 0) { // forced from vertical
                if ((map.CellIsTraversable(x + 1, y + dy) && map.CellIsObstacle(x + 1, y)) ||
                    (map.CellIsTraversable(x - 1, y + dy) && map.CellIsObstacle(x - 1, y))) {
                    return neighbor;
                }
            }

            neighbor.i += dx;
            neighbor.j += dy;
            neighbor.g += sqrt(dx * dx + dy * dy);
        }
    }

    std::list<Node> pruneNeighbors(Node *curNode, const Map &map, const EnvironmentOptions &options) {
        std::list<Node> neighbors;
        if ((Coords) *curNode == map.getStartCoords()) { // has no parent, start node
            for (int i = 0; i < DIR_CNT; ++i) {
                neighbors.emplace_back(curNode->i + moveDx[i], curNode->j + moveDy[i], curNode);
            }
        } else { // has parent and previous direction
            int x = curNode->i;
            int y = curNode->j;

            int dx = direction(curNode->parent->i, curNode->i); // previous direction
            int dy = direction(curNode->parent->j, curNode->j);

            if (dx != 0 && map.CellIsTraversable(x + dx, y)) { // horizontal
                neighbors.emplace_back(x + dx, y, curNode);
            }
            if (dy != 0 && map.CellIsTraversable(x, y + dy)) { // vertical
                neighbors.emplace_back(x, y + dy, curNode);
            }

            if (dx != 0 && dy != 0) { // diagonal
                if (map.CellIsTraversable(x + dx, y + dy)) {
                    neighbors.emplace_back(x + dx, y + dy, curNode);
                }

                if (map.CellIsObstacle(x - dx, y)) { // forced from horizontal
                    neighbors.emplace_back(x - dx, y + dy, curNode);
                }
                if (map.CellIsObstacle(x, y - dy)) { // forced from vertical
                    neighbors.emplace_back(x + dx, y - dy, curNode);
                }
            } else if (dy == 0) { // horizontal move
                if (map.CellIsObstacle(x, y + 1)) { // forced
                    neighbors.emplace_back(x + dx, y + 1, curNode);
                }
                if (map.CellIsObstacle(x, y - 1)) { // forced
                    neighbors.emplace_back(x + dx, y - 1, curNode);
                }
            } else { // if (dx == 0) { // vertical move
                if (map.CellIsObstacle(x + 1, y)) { // forced
                    neighbors.emplace_back(x + 1, y + dy, curNode);
                }
                if (map.CellIsObstacle(x - 1, y)) { // forced
                    neighbors.emplace_back(x - 1, y + dy, curNode);
                }
            }
        }
        return neighbors;
    }
}


JP_Search::JP_Search(double HW, bool BT) : Astar(HW, BT) {}


std::list<Node> JP_Search::findSuccessors(Node *curNode, const Map &map, const EnvironmentOptions &options) const {
    std::list<Node> successors;

    auto neighbors = pruneNeighbors(curNode, map, options);

    for (const auto run : neighbors) {
        auto jumper = jump(run, curNode, map, options);
        int x = jumper.i, y = jumper.j;

        if (!map.CellOnGrid(x, y) || !map.CellIsTraversable(x, y) || close.contain(jumper)) {
            continue;
        }

        auto goal = map.getGoal();
        jumper.H = computeHFromCellToCell(jumper.i, jumper.j, goal.first, goal.second, options);
        jumper.F = jumper.H * hweight + jumper.g;

        successors.push_back(jumper);
    }

    return successors;
}

// First path use parents for nodes, in this case it is sections of one line
void JP_Search::makePrimaryPath(Node curNode) {
    Node current = curNode;
    while (current.parent) {
        hppath.push_front(current);
        current = *current.parent;
    }
    hppath.push_front(current);
}

// Second path contains all node on path
void JP_Search::makeSecondaryPath() {
    Node begin = *hppath.begin();
    Node end = *(++hppath.begin());
    Node inBetween;

    // First to pre-last section
    for (auto iter = ++hppath.begin(), before = hppath.begin(); before!= hppath.end(); ++iter, ++before) {
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
