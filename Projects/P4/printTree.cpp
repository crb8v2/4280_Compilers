//
// Created by crbaniak on 5/16/19.
//

#include "printTree.h"

void printTree(node *node, int level) {

    for(int x = 0; x < 1; x++) {

        if (node == NULL)
            return;

        string line;

        //two spaces for each level
        for (int counter = 0; counter < level; counter++) {
            line.append("  ");
        }

        line.append(node->id);
        line.append(" ");
        line.append(node->literal);
        line.append(" ");
        line.append(node->value);

        //if vars or r, print
        line.append(" ");

        cout << line << "\n";

        //Print the children of the node, where the children go from
        //left to right.
        printTree(node->child0, level + 1);
        printTree(node->child1, level + 1);
        printTree(node->child2, level + 1);
        printTree(node->child3, level + 1);
    }
}