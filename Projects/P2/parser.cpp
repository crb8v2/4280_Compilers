//
// Created by crbaniak on 4/22/19.
//

#include "parser.h"
#include "node.h"
#include "token.h"
#include "scanner.h"

string tk;
FILE *fp = NULL;
int lineNum = 0;
int level = 0;
static int tokenCounter = 0;

node *createNode(string s) {
    node *newNode = new node;
    newNode-> literal = s;
    return newNode;
}

node *parser() {
    node *tree;
//    tk = scanner(fp, lineNum);
    tree = program();

    cout << "Parse OK\n";
    return tree;
}

//<program>  ->     PROGRAM <var> <block>
node *program() {

    node *p = createNode("<program>");

//    node->child_0 = vars();
//    node->child_1 = block();

    return p;
}


//node *vars() {
//    node_t *p = getNode("<var>");
//
//    if(tk.tokenId == DEL_tk && tk.name == "{"|| tk.tokenId == SCAN_tk || tk.tokenId == IF_tk || tk.tokenId == PRINT_tk ||
//       tk.tokenId == LOOP_tk || tk.tokenId == IDENT_tk) { // empty
//        return p;
//    } else if(tk.tokenId == INT_tk) { // INTEGER
//        p->child1 = getNode("INTEGER");
//        p->child1->token_t = tk;
//        tk = scanner(fp, lineNum);
//        if(tk.tokenId == IDENT_tk) { // IDENTIFIER
//            p->child2 = getNode("IDENTIFIER");
//            p->child2->token_t = tk;
//            tk = scanner(fp, lineNum);
//            p->child3 = mvars_f();
//            if (tk.tokenId == DEL_tk && tk.name == ";") { // ;
//                //don't need to put delimiters in the tree
//                tk = scanner(fp, lineNum);
//                return p;
//            } else {
//                error("Got token " + tk.name + ", expected ; token\n");
//            }
//        } else {
//            error("Got token " + tk.name + ", expected IDENTIFIER token\n");
//        }
//    } else {
//        error("Got token " + tk.name + ", expected empty or INTEGER token\n");
//    }
//    return p;
//}
//
//
//node *block() {
//    node_t *p = getNode("<block>");
//
//    if (tk.tokenId == DEL_tk && tk.name == "{") { // {
//        //don't need to put delimiters in the tree
//        tk = scanner(fp, lineNum);
//        p->child1 = var_f();
//        p->child2 = stats_f();
//        if (tk.tokenId == DEL_tk && tk.name == "}") { // }
//            //don't need to put delimiters in the tree
//            tk = scanner(fp, lineNum);
//            return p;
//        } else {
//            error("Got token " + tk.name + ", expected } token");
//        }
//    } else {
//        error("Got token " + tk.name + ", expected { token");
//    }
//
//    return p;
//}
