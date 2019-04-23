//
// Created by crbaniak on 4/22/19.
//

#ifndef P1_NODE_H
#define P1_NODE_H

#include "scanner.h" //magic maybe?

#include <string>

struct node {
    string label;
    node* child1, *child2, *child3, *child4, *child5;
    token token_t;
};

#endif //P1_NODE_H
