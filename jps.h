//
// Created by anton on 11.03.19.
//

#ifndef PATHPLANNING_JPS_H
#define PATHPLANNING_JPS_H

#include "astar.h"

class JP_Search : public Astar {
public:
    JP_Search(double HW, bool BT);

    // allow of types of movement
    std::list<Node> findSuccessors(Node *curNode, const Map &map, const EnvironmentOptions &options) const override;


    void makePrimaryPath(Node curNode) override;

    void makeSecondaryPath() override;
};


#endif //PATHPLANNING_JPS_H
