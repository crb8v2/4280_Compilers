//
// Created by crbaniak on 4/22/19.
//

// error with mstats after assign, loop doesnt work, begin wont call more than once

#include "parser.h"
#include "node.h"
#include "token.h"
#include "scanner.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

static int posInFTS = 0;


node* parser() {
    node* root;

    root = program();

    return root;
}

node* program() {

    node *tree = create_node("<program>");

    tree->child0 = vars();
    tree->child1 = block();

    if(finalTokenSet[fileSize].tokenID == "EOFtk"){
        cout << "Parse OK\n";
    } else {
        cout << "Parse failed : error out";
    }

    return tree;
}

node* vars() {

    node *tree = create_node("<vars>");


    if(finalTokenSet[posInFTS].tokenID == "INTTK") {
        posInFTS += 1;
        if(finalTokenSet[posInFTS].tokenID == "IDTK"){
            // put info in node
            posInFTS += 1;

            if(finalTokenSet[posInFTS].tokenID == "NUMTK"){
                posInFTS += 1;
                tree->child0 = vars();
                return tree;

            } else
                error("NUMTK");
        } else
            error("IDTK");
    }

    return NULL;
}

node* block() {

    node *tree = create_node("<block>");


    if (finalTokenSet[posInFTS].tokenID == "BeginTK") {
        posInFTS += 1;
    } else
        error("BeginTK");

    tree->child0 = vars();
    tree->child1 = stats();

    if (finalTokenSet[posInFTS].tokenID == "EndTK") {
        posInFTS += 1;
    } else
        error("EndTKk");

    return tree;
}

node* stats(){

    node *tree = create_node("<stats>");

    tree->child0 = stat();

    if(finalTokenSet[posInFTS].tokenID == "SYMTK:"){
        posInFTS += 1;

    } else
        error("SYMTK:");

    tree->child1 = mstats();

    return tree;
}

node* stat(){

    node *tree = create_node("<stat>");

    if(finalTokenSet[posInFTS].tokenID == "ReadTK"){
        tree->child0 = in();
    } else if(finalTokenSet[posInFTS].tokenID == "OutputTK"){
        tree->child0 = out();
    } else if(finalTokenSet[posInFTS].tokenID == "BeginTK"){
        tree->child0 = block();
    } else if(finalTokenSet[posInFTS].tokenID == "LoopTK"){
        tree->child0 = loop();
    } else if(finalTokenSet[posInFTS].tokenID == "IFFTK"){
        tree->child0 = iff();
    }  else if(finalTokenSet[posInFTS].tokenID == "IDTK")
        tree->child0 = assign();
    else{
        error(finalTokenSet[posInFTS].tokenID);
    }

    return tree;
}

node* mstats(){

    node *tree = create_node("<mstats>");

    if(finalTokenSet[posInFTS].tokenID == "EndTK"){
        return NULL;
    }

    if(finalTokenSet[posInFTS].tokenID == "IDTK" ||
            finalTokenSet[posInFTS].tokenID == "ReadTK" ||
            finalTokenSet[posInFTS].tokenID == "OutputTK" ||
            finalTokenSet[posInFTS].tokenID == "BeginTK" ||
            finalTokenSet[posInFTS].tokenID == "LoopTK" ||
            finalTokenSet[posInFTS].tokenID == "IFFTK"){
        tree->child0 = stat();
        if(finalTokenSet[posInFTS].tokenID == "SYMTK:") {
            posInFTS += 1;
        } else {
            error("SYMTK:");
        }
        tree->child1 = mstats();
        return tree;
    }

    return NULL;
}

node* in(){

    node *tree = create_node("<in>");

    if(finalTokenSet[posInFTS].tokenID == "ReadTK"){
        posInFTS += 1;
        if(finalTokenSet[posInFTS].tokenID == "SYMTK["){
            posInFTS += 1;
            tree->child0 = expr();
            if(finalTokenSet[posInFTS].tokenID == "SYMTK]"){
                posInFTS += 1;

            } else
                error("SYMTK]");
        } else
            error("SYMTK[");
    } else
        error("OutputTK");

    return tree;
}

node* out(){

    node *tree = create_node("<out>");


    if(finalTokenSet[posInFTS].tokenID == "OutputTK"){
        posInFTS += 1;
        if(finalTokenSet[posInFTS].tokenID == "SYMTK["){
            posInFTS += 1;
            tree->child0 = expr();
            if(finalTokenSet[posInFTS].tokenID == "SYMTK]"){
                posInFTS += 1;

            } else
                error("SYMTK]");
        } else
            error("SYMTK[");
    } else
        error("OutputTK");

    return tree;
}

node* iff(){

    node *tree = create_node("<IFF>");

    if(finalTokenSet[posInFTS].tokenID == "IFFTK"){
        posInFTS += 1;
        if(finalTokenSet[posInFTS].tokenID == "SYMTK["){
            posInFTS += 1;
            tree->child0 = expr();
            tree->child1 = ro();
            tree->child2 = expr();
            if(finalTokenSet[posInFTS].tokenID == "SYMTK]"){
                posInFTS += 1;
                stat();
            } else
                error("SYMTK]");
        } else
            error("SYMTK[");
    } else
        error("IFFTK");

    return tree;
}

node* loop(){

    node *tree = create_node("<Loop>");

    if(finalTokenSet[posInFTS].tokenID == "LoopTK"){
        posInFTS += 1;
        if(finalTokenSet[posInFTS].tokenID == "SYMTK["){
            posInFTS += 1;
            tree->child0 = expr();
            tree->child1 = ro();
            tree->child2 = expr();
            if(finalTokenSet[posInFTS].tokenID == "SYMTK]"){
                posInFTS += 1;
                tree->child3 = stat();
            } else
                error("SYMTK]");
        } else
            error("SYMTK[");
    } else
        error("LoopTK");

    return tree;
}

node* assign(){

    node *tree = create_node("<assign>");

    if(finalTokenSet[posInFTS].tokenID == "IDTK"){
        posInFTS += 1;

        if(finalTokenSet[posInFTS].tokenID == "SYMTK="){
            posInFTS += 1;
            tree->child0 = expr();

        } else
            error("SYMTK=");
    } else
        error("IDTK (in assign)");

    return tree;
}

node* expr(){

    node *tree = create_node("<expr>");

    tree->child0 = a();
    tree->child1 = z();

    return tree;
}

node* a(){

    node *tree = create_node("<a>");

    tree->child0 = n();

    if(finalTokenSet[posInFTS].tokenID == "SYMTK*"){
        posInFTS += 1;
        tree->child1 = a();
    }

    return tree;
}

node* n(){

    node *tree = create_node("<n>");

    tree->child0 = m();

    if(finalTokenSet[posInFTS].tokenID == "SYMTK/"){
        posInFTS += 1;
        tree->child1 = n();
    }

    return tree;
}

node* m(){

    node *tree = create_node("<m>");

    if(finalTokenSet[posInFTS].tokenID == "SYMTK-"){
        posInFTS += 1;
        tree->child0 = m();
    } else {
        tree->child1 = r();
    }

    return tree;
}

node* r(){

    node *tree = create_node("<r>");

    if(finalTokenSet[posInFTS].tokenID == "SYMTK["){
        posInFTS += 1;
        tree->child0 = expr();
        if(finalTokenSet[posInFTS].tokenID == "SYMTK]"){
            posInFTS += 1;

        } else
            error("SYMTK]");
    } else if(finalTokenSet[posInFTS].tokenID == "NUMTK" ||
                finalTokenSet[posInFTS].tokenID == "IDTK"){
        posInFTS += 1;
    } else {
        error(" in r ");
    }

    return tree;
}

node* z(){

    node *tree = create_node("<z>");

    if(finalTokenSet[posInFTS].tokenID == "SYMTK-" ||
        finalTokenSet[posInFTS].tokenID == "SYMTK+"){
        posInFTS += 1;
        tree->child0 = expr();
        return tree;
    }

    return NULL;
}

node* ro(){

    node *tree = create_node("<ro>");

    if(finalTokenSet[posInFTS].tokenID == "SYMTK<" ||
            finalTokenSet[posInFTS].tokenID == "SYMTK>"){

        posInFTS += 1;
        return tree;

    }else if (finalTokenSet[posInFTS].tokenID == "SYMTK="){

        posInFTS += 1;

        if(finalTokenSet[posInFTS].tokenID == "SYMTK=" ||
                finalTokenSet[posInFTS].tokenID == "SYMTK<" ||
                finalTokenSet[posInFTS].tokenID == "SYMTK>"){

            posInFTS += 1;
            return tree;
        }
    } else{
        error("Relational Operator");
    }

    return NULL;
}

void error(string bean){

    cout << "ERROR in Line: " << finalTokenSet[posInFTS+1].linecount + 2 << " -- Recieved: "
    << finalTokenSet[posInFTS].tokenID << " -- Expected: " << bean << endl;

    exit(0);
}

node *create_node(string production_name)
{
    node *tree = new node();
    tree->child0 = NULL;
    tree->child1 = NULL;
    tree->child2 = NULL;
    tree->child3 = NULL;

    tree->literal = production_name;

    return tree;
}

//  printf("here: %s\n", finalTokenSet[posInFTS].tokenID.c_str());

