//
// Created by crbaniak on 4/21/19.
//

#ifndef P1_NODE_H
#define P1_NODE_H

using namespace std;

struct node {
    string label;
    node_t *child1, *child2, *child3, *child4;
    token myToken;
};

#endif //P1_NODE_H
