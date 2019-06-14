//
// Created by crbaniak on 6/5/19.
//

#ifndef P1_SEMANTICS_H
#define P1_SEMANTICS_H

#include <bits/stdc++.h>
#include "node.h"
#include "scanner.h"


using namespace std;

#define MAX 1000

//void pushVariables();
//void printStack();

string parser(node *);
string program(node *);
string vars(node *);
string block(node *);
string stats(node *);
string stat(node *);
string mstats(node *);
string in(node *);
string out(node *);
string iff(node *);
string expr(node *);
string a(node *);
string n(node *);
string m(node *);
string r(node *);
string z(node *);
string ro(node *);
string loop(node *);
string assign(node *);
void gatherVars();
void prePrint();
void printToFile(string);
void closeFile();


#endif //P1_SEMANTICS_H
