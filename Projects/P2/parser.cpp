//
// Created by crbaniak on 4/22/19.
//

#include "parser.h"
#include "node.h"

token tk;
FILE *fp = NULL;
int lineNum = 0;
int level = 0;

node *getNode(string s) {
    node *noder = new node;
    noder->label = s;
    return noder;
}

//fix treep
node *parser() {
    node *treep;
    //open file and delete one line
//    tk = scanner(fp, lineNum);
//    treep = prog_f();

    cout << "Parse OK\n";
    return treep;
}

//<program>  ->     PROGRAM <var> <block>
node* prog_f() {
    node *p = getNode("<program>");

//    if(tk.tokenId == PROG_tk) { // PROGRAM
//        p->child1 = getNode("PROGRAM");
////        tk = scanner(fp, lineNum); needs to call and pop file instead
////        p->child2 = var_f();
////        p->child3 = block_f();
//        return p;
//    } else {
//        error("Got token " + tk.name + ", expected PROGRAM token\n");
//    }

        cout << "we made it here" << endl;
    return p;
}
