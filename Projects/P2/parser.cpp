//
// Created by crbaniak on 4/22/19.
//

#include "parser.h"
#include "node.h"


node *getNode(string s) {
    node *noder = new node;
    noder->label = s;
    return noder;
}

node_t* parser() {
    node_t *treep;
    //open file and delete one line
//    tk = scanner(fp, lineNum);
    treep = prog_f();

    cout << "Parse OK\n";
    return treep;
}
