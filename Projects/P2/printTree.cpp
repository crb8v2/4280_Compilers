

#include <iostream>

#include "node.h"




string tokenNames[] = {"Identifier", "Number", "Begin keyword", "End keyword", "Start keyword", "Finish keyword",
                       "Then keyword", "If keyword", "Loop keyword", "Integer keyword", "Do keyword", "Scan keyword",
                       "Print keyword", "Void keyword", "Return keyword", "Program keyword", "Dummy keyword",
                       "Relational Operator", "Other Operator", "Delimeter", "End of File", "Error"};

void printTree(node *root, int level) {
    if (root == NULL) {
        return;
    } else { //process node
        for (int i = 0; i < level; i++) {
            cout << "  ";
        }
        level++;

        cout << root->literal << "\t";
//
//        token token = root->literal;
//
//        if (token.tokenLiteral != "") {
//            cout <<  "bad Instance: " + token.tokenLiteral << endl;
//        }
//
//        cout << "\n";
//
//        //recursively process children
//        printTree(root->child0, level);
//        printTree(root->child1, level);
//        printTree(root->child2, level);
//        printTree(root->child3, level);
//        printTree(root->child4, level);
    }
}