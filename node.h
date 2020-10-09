#ifndef NODE_H
#define NODE_H

#include <cmath>

//That's the data structure for storing a single search node.
//Although one might realize A* pathfinder relying only on g-value,
//it's a good idea to store f- and h-values explicitly for the sake of simplicity
//(and either h- or f-value is definetely needed for realizing different tie-breaking strategies).
//Backpointer is obligatory for any-angle algorithms, e.g. Theta*, and it makes sense to utilize it
//in A*-like algorithms as well for reconstructing path (after the main search phase is finished).

//So, in the end of the day, we have a sort of "universal" search-node structure
//compatable with various types of grid pathfinders (Dijkstra, A*, Jump Point Search, Theta* etc.)
//which means - that's all you need for that project.

struct Node {
    Node() {
        i = 0;
        j = 0;
        F = 0;
        g = 0;
        H = 0;
        parent = nullptr;
    }

    Node(int i, int j, Node *parent) : i(i), j(j), F(), g(), H(), parent(parent) {
        if (parent != nullptr) {
            if (i != parent->i && j != parent->j) {
                g = parent->g + sqrt(2);
            } else {
                g = parent->g + 1;
            }
        }
    }

    bool operator==(const Node &other) const {
        return i == other.i && j == other.j;
    }

    bool operator<(const Node &other) const {
        if (F != other.F) {
            return F < other.F;
        }

        if (i != other.i) {
            return i < other.i;
        }
        return j < other.j;
    }

    int i, j; //grid cell coordinates
    double F, g, H; //f-, g- and h-values of the search node
    Node *parent; //backpointer to the predecessor node (e.g. the node which g-value was used to set the g-velue of the current node)

};

#endif
