#include "isearch.h"

#include "usages.h"

namespace {
    constexpr int moveDx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
    constexpr int moveDy[] = {0, -1, -1, -1, 0, 1, 1, 1};
    constexpr int DIR_CNT = sizeof(moveDx) / sizeof(int);

    constexpr double toSeconds = 1000000000.0;
}

ISearch::ISearch() {

    hweight = 1;
    breakingties = CN_SP_BT_GMAX;
}


SearchResult ISearch::startSearch(ILogger *Logger, const Map &map, const EnvironmentOptions &options) {
    std::chrono::time_point<std::chrono::system_clock> start_time;
    std::chrono::time_point<std::chrono::system_clock> end_time;
    start_time = std::chrono::system_clock::now();
    sresult.pathfound = false;
    Node startNode;

    auto start = map.getStart();
    auto goal = map.getGoal();
    startNode.i = start.first;
    startNode.j = start.second;

    startNode.H = computeHFromCellToCell(startNode.i, startNode.j, goal.first, goal.second, options);
    startNode.g = 0;
    startNode.F = hweight * startNode.H;
    startNode.parent = nullptr;

    open.setBreakingties(breakingties);
    open.insert(startNode);


    Node curNode;
    while (!open.empty()) {
        curNode = open.getMinimum();
        Logger->writeToLogOpenClose(open, close, close.size(), false);

        open.erase(curNode);

        close.insert(curNode);
        if (curNode.i == goal.first && curNode.j == goal.second) {
            sresult.pathfound = true;
            break;
        }
        std::list<Node> successors = findSuccessors(close[curNode], map, options);

        for (auto successor : successors) {
            open.insert(successor);
        }
    }
    Logger->writeToLogOpenClose(open, close, close.size(), true);
    if (sresult.pathfound) {
        sresult.pathlength = curNode.g;
        makePrimaryPath(curNode);
        end_time = std::chrono::system_clock::now();
        sresult.time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() / toSeconds;
        //time after primary path only
        makeSecondaryPath();
    }
    sresult.nodescreated = close.size() + open.size();
    sresult.numberofsteps = close.size();


    sresult.lppath = &lppath;
    sresult.hppath = &hppath;

    return sresult;
}


std::list<Node> ISearch::findSuccessors(Node *curNode, const Map &map, const EnvironmentOptions &options) const {
    std::list<Node> successors;
    for (int i = 0; i < DIR_CNT; ++i) {
        int x = curNode->i + moveDx[i], y = curNode->j + moveDy[i];

        if (!map.CellIsTraversable(x, y)) {
            continue;
        }

        if (!options.allowdiagonal && moveDx[i] != 0 && moveDy[i] != 0) {
            continue;
        }

        int cornersCnt = 0;
        if (map.CellIsObstacle(curNode->i, y)) {
            cornersCnt++;
        }

        if (map.CellIsObstacle(x, curNode->j)) {
            cornersCnt++;
        }

        if (!options.cutcorners && cornersCnt >= 1) {
            continue;
        }

        if (!options.allowsqueeze && cornersCnt == 2) {
            continue;
        }

        if (!close.contain(x, y)) {
            Node neighbour(x, y, curNode);
            updateNodesParent(curNode, &neighbour, map, options);

            auto goal = map.getGoal();
            neighbour.H = computeHFromCellToCell(neighbour.i, neighbour.j, goal.first, goal.second, options);
            neighbour.F = neighbour.H * hweight + neighbour.g;

            successors.push_back(neighbour);
        }
    }
    return successors;
}

void ISearch::makePrimaryPath(Node pathTo) {
    Node *start = &pathTo;
    for (Node *curNode = start; curNode != nullptr; curNode = curNode->parent) {
        lppath.push_front(*curNode);
    }
}

void ISearch::makeSecondaryPath() {
    hppath.push_back(lppath.front());

    Node prev = *lppath.begin();
    auto cur = ++lppath.begin();
    int prevDi = cur->i - prev.i, prevDj = cur->j - prev.j;

    while (cur != lppath.end()) {
        int di = cur->i - prev.i;
        int dj = cur->j - prev.j;
        if (di != prevDi || dj != prevDj) {
            hppath.push_back(prev);
            prevDi = di;
            prevDj = dj;
        }
        prev = *cur;
        ++cur;
    }
    if (!(hppath.back() == lppath.back())) {
        hppath.push_back(lppath.back());
    }
}
