//
// Created by crbaniak on 4/22/19.
//

#ifndef P1_NODE_H
#define P1_NODE_H

#include "scanner.h" //magic maybe?

#include <string>

struct node {

    node *child0, *child1, *child2, *child3, *child4;
    token token_t;
    string literal;
};

#endif //P1_NODE_H
