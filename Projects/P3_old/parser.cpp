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

    return tree;
}

node* block() {

    node *tree = create_node("<block>");


    if (finalTokenSet[posInFTS].tokenID == "BeginTK") {
        posInFTS += 1;
    } else
        error("BeginTK");

    vars();
    stats();

    if (finalTokenSet[posInFTS].tokenID == "EndTK") {
        posInFTS += 1;
    } else
        error("EndTK");

    return tree;
}

void stats(){

    stat();

    if(finalTokenSet[posInFTS].tokenID == "SYMTK:"){
        posInFTS += 1;

    } else
        error("SYMTK:");

    mstats();

    return;
}

void stat(){

    cout << finalTokenSet[posInFTS].tokenID << endl;



    if(finalTokenSet[posInFTS].tokenID == "ReadTK"){
        in();
    } else if(finalTokenSet[posInFTS].tokenID == "OutputTK"){
        out();
    } else if(finalTokenSet[posInFTS].tokenID == "BeginTK"){
        block();
    } else if(finalTokenSet[posInFTS].tokenID == "LoopTk"){
        loop();
    } else if(finalTokenSet[posInFTS].tokenID == "IFFTK"){
        iff();
    }  else if(finalTokenSet[posInFTS].tokenID == "IDTK")
        assign();
    else{
        error(finalTokenSet[posInFTS].tokenID);
    }

    return;
}

void mstats(){

    if(finalTokenSet[posInFTS].tokenID == "EndTk"){
        return;
    }

    if(finalTokenSet[posInFTS].tokenID == "IDTK"){
        stat();
        if(finalTokenSet[posInFTS].tokenID == "SYMTK:") {
            posInFTS += 1;
        } else {
            error("SYMTK:");
        }
        mstats();
        return;
    }

    return;
}

void in(){

    if(finalTokenSet[posInFTS].tokenID == "ReadTK"){
        posInFTS += 1;
        if(finalTokenSet[posInFTS].tokenID == "SYMTK["){
            posInFTS += 1;
            expr();
            if(finalTokenSet[posInFTS].tokenID == "SYMTK]"){
                posInFTS += 1;

            } else
                error("SYMTK]");
        } else
            error("SYMTK[");
    } else
        error("OutputTK");

    return;
}

void out(){
    if(finalTokenSet[posInFTS].tokenID == "OutputTK"){
        posInFTS += 1;
        if(finalTokenSet[posInFTS].tokenID == "SYMTK["){
            posInFTS += 1;
            expr();
            if(finalTokenSet[posInFTS].tokenID == "SYMTK]"){
                posInFTS += 1;

            } else
                error("SYMTK]");
        } else
            error("SYMTK[");
    } else
        error("OutputTK");

    return;
}

void iff(){

    if(finalTokenSet[posInFTS].tokenID == "IFFTK"){
        posInFTS += 1;
        if(finalTokenSet[posInFTS].tokenID == "SYMTK["){
            posInFTS += 1;
            expr();
            ro();
            expr();
            if(finalTokenSet[posInFTS].tokenID == "SYMTK]"){
                posInFTS += 1;
                stat();
            } else
                error("SYMTK]");
        } else
            error("SYMTK[");
    } else
        error("IFFTK");

    return;
}

void loop(){

    if(finalTokenSet[posInFTS].tokenID == "LoopTK"){
        posInFTS += 1;
        if(finalTokenSet[posInFTS].tokenID == "SYMTK["){
            posInFTS += 1;
            expr();
            ro();
            expr();
            if(finalTokenSet[posInFTS].tokenID == "SYMTK]"){
                posInFTS += 1;
                stat();
            } else
                error("SYMTK]");
        } else
            error("SYMTK[");
    } else
        error("LoopTK");

    return;
}

void assign(){

    if(finalTokenSet[posInFTS].tokenID == "IDTK"){
        posInFTS += 1;

        if(finalTokenSet[posInFTS].tokenID == "SYMTK="){
            posInFTS += 1;
            expr();
//            if(finalTokenSet[posInFTS].tokenID == "SYMTK:"){
//                posInFTS += 1;
//                tk = finalTokenSet[posInFTS];
//            }
        } else
            error("SYMTK=");
    } else
        error("IDTK (in assign)");

    return;
}

void expr(){

    a();
    z();

    return;
}

void a(){

    n();

    if(finalTokenSet[posInFTS].tokenID == "SYMTK*"){
        posInFTS += 1;
        a();
    }

    return;
}

void n(){

    m();

    if(finalTokenSet[posInFTS].tokenID == "SYMTK/"){
        posInFTS += 1;
        n();
    }

    return;
}

void m(){

    if(finalTokenSet[posInFTS].tokenID == "SYMTK-"){
        posInFTS += 1;
        m();
    } else {
        r();
    }

    return;
}

void r(){

    if(finalTokenSet[posInFTS].tokenID == "SYMTK["){
        posInFTS += 1;
        expr();
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

    return;
}

void z(){

    if(finalTokenSet[posInFTS].tokenID == "SYMTK-" ||
        finalTokenSet[posInFTS].tokenID == "SYMTK+"){
        posInFTS += 1;
        expr();
        return;
    }

    return;
}

void ro(){

    if(finalTokenSet[posInFTS].tokenID == "SYMTK<" ||
            finalTokenSet[posInFTS].tokenID == "SYMTK>"){

        posInFTS += 1;
        return;

    }else if (finalTokenSet[posInFTS].tokenID == "SYMTK="){

        posInFTS += 1;

        if(finalTokenSet[posInFTS].tokenID == "SYMTK=" ||
                finalTokenSet[posInFTS].tokenID == "SYMTK<" ||
                finalTokenSet[posInFTS].tokenID == "SYMTK>"){

            posInFTS += 1;
            return;
        }
    } else{
        error("Relational Operator");
    }

    return;
}

void error(string bean){

    cout << "ERROR in Line: " << finalTokenSet[posInFTS+1].linecount + 1 << " -- Recieved: "
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

