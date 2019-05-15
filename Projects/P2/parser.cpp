//
// Created by crbaniak on 4/22/19.
//

#include "parser.h"
#include "node.h"
#include "token.h"
#include "scanner.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

token tk;
static int posInFTS = 0;

void parser() {
    tk = finalTokenSet[posInFTS];
//    posInFTS+=1;
    program();

    return;
}

void program() {

    vars();
    block();

    if(finalTokenSet[fileSize].tokenID == "EOFtk"){
        cout << "Parse OK\n";
    } else {
        cout << "Parse failed : error out";
    }

    return;
}

void vars() {

    if(finalTokenSet[posInFTS].tokenID == "INTTK") {
        posInFTS += 1;
        tk = finalTokenSet[posInFTS];

        if(finalTokenSet[posInFTS].tokenID == "IDTK"){
            posInFTS += 1;
            tk = finalTokenSet[posInFTS];

            if(finalTokenSet[posInFTS].tokenID == "NUMTK"){
                posInFTS += 1;
                tk = finalTokenSet[posInFTS];
                vars();
                return;

            } else
                error("NUMTK");
        } else
            error("IDTK");
    } else
        return;

    return;
}

void block() {

    if (finalTokenSet[posInFTS].tokenID == "BeginTK") {
        posInFTS += 1;
        tk = finalTokenSet[posInFTS];
    } else
        error("BeginTK");

    vars();
    stats();

    if (finalTokenSet[posInFTS].tokenID == "EndTK") {
        posInFTS += 2;
        tk = finalTokenSet[posInFTS];
    } else
        error("EndTK");

    return;
}

void stats(){

    stat();

    if(finalTokenSet[posInFTS].tokenID == "SYMTK:"){
        posInFTS += 1;
        tk = finalTokenSet[posInFTS];

    } else
        error("SYMTK:");

    mstats();

    return;
}

void stat(){

    if(finalTokenSet[posInFTS].tokenID == "ReadTK"){
        in();
    } else if(finalTokenSet[posInFTS].tokenID == "OutputTK"){
        out();
    } else if(finalTokenSet[posInFTS].tokenID == "BeginTK"){ //doesnt work
        block();
    } else if(finalTokenSet[posInFTS].tokenID == "IFFTK"){
        iff();
    } else if(finalTokenSet[posInFTS].tokenID == "LoopTk"){
        loop();
    } else if(finalTokenSet[posInFTS].tokenID == "IDTK")
        assign();
    else{
        error(" in 'stats'");
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
            tk = finalTokenSet[posInFTS];
        } else {
            error("SYMTK:");
        }
        mstats();

    }

    return;
}

void in(){

    if(finalTokenSet[posInFTS].tokenID == "ReadTK"){
        posInFTS += 1;
        tk = finalTokenSet[posInFTS];
        if(finalTokenSet[posInFTS].tokenID == "SYMTK["){
            posInFTS += 1;
            tk = finalTokenSet[posInFTS];
            expr();
            if(finalTokenSet[posInFTS].tokenID == "SYMTK]"){
                posInFTS += 1;
                tk = finalTokenSet[posInFTS];

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
        tk = finalTokenSet[posInFTS];
        if(finalTokenSet[posInFTS].tokenID == "SYMTK["){
            posInFTS += 1;
            tk = finalTokenSet[posInFTS];
            expr();
            if(finalTokenSet[posInFTS].tokenID == "SYMTK]"){
                posInFTS += 1;
                tk = finalTokenSet[posInFTS];

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
        tk = finalTokenSet[posInFTS];
        if(finalTokenSet[posInFTS].tokenID == "SYMTK["){
            posInFTS += 1;
            tk = finalTokenSet[posInFTS];
            expr();
            ro();
            expr();
            if(finalTokenSet[posInFTS].tokenID == "SYMTK]"){
                posInFTS += 1;
                tk = finalTokenSet[posInFTS];
                stat();
            } else
                error("SYMTK]");
        } else
            error("SYMTK[");
    } else
        error("IFFTK");

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
        tk = finalTokenSet[posInFTS];
        a();
    }

    return;
}

void n(){

    m();

    if(finalTokenSet[posInFTS].tokenID == "SYMTK/"){
        posInFTS += 1;
        tk = finalTokenSet[posInFTS];
        n();
    }

    return;
}

void m(){

    if(finalTokenSet[posInFTS].tokenID == "SYMTK-"){
        posInFTS += 1;
        tk = finalTokenSet[posInFTS];
        m();
    } else {
        r();
    }

    return;
}

void r(){

    if(finalTokenSet[posInFTS].tokenID == "SYMTK["){
        posInFTS += 1;
        tk = finalTokenSet[posInFTS];
        expr();
        if(finalTokenSet[posInFTS].tokenID == "SYMTK]"){
            posInFTS += 1;
            tk = finalTokenSet[posInFTS];

        } else
            error("SYMTK]");
    } else if(finalTokenSet[posInFTS].tokenID == "NUMTK" ||
                finalTokenSet[posInFTS].tokenID == "IDTK"){
        posInFTS += 1;
        tk = finalTokenSet[posInFTS];
    } else {
        error("impressive");
    }


    return;
}

void z(){

    if(finalTokenSet[posInFTS].tokenID == "SYMTK-" ||
        finalTokenSet[posInFTS].tokenID == "SYMTK+"){
        posInFTS += 1;
        tk = finalTokenSet[posInFTS];
        expr();
    }

    return;
}

void ro(){

    if(finalTokenSet[posInFTS].tokenID == "SYMTK<" ||
            finalTokenSet[posInFTS].tokenID == "SYMTK>"){

        posInFTS += 1;
        tk = finalTokenSet[posInFTS];

    }else if (finalTokenSet[posInFTS].tokenID == "SYMTK="){

        posInFTS += 1;
        tk = finalTokenSet[posInFTS];

        if(finalTokenSet[posInFTS].tokenID == "SYMTK=" ||
                finalTokenSet[posInFTS].tokenID == "SYMTK<" ||
                finalTokenSet[posInFTS].tokenID == "SYMTK>"){

            posInFTS += 1;
            tk = finalTokenSet[posInFTS];
        }
    } else{
        error("Relational Operator");
    }

    return;
}

void loop(){

    return;
}

void assign(){

    return;
}

void error(string bean){

    cout << "ERROR in Line: " << finalTokenSet[posInFTS+1].linecount + 1 << " -- Recieved: "
    << finalTokenSet[posInFTS].tokenID << " -- Expected: " << bean << endl;

    exit(0);
}



//  printf("here: %s\n", finalTokenSet[posInFTS].tokenID.c_str());

