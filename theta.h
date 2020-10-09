#ifndef PATHPLANNING_THETA_H
#define PATHPLANNING_THETA_H

#include "astar.h"

class Theta : public Astar {
public:
    Theta(double HW, bool BT);

    bool isOnSight(Node *curNode, Node *neighbour, const Map &map, const EnvironmentOptions &options) const override;

    void updateNodesParent(Node *curNode, Node *neighbour,
                           const Map &map, const EnvironmentOptions &options) const override;

    void makePrimaryPath(Node curNode) override;

    void makeSecondaryPath() override;
};


#endif //PATHPLANNING_THETA_H
