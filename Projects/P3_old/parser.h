//
// Created by crbaniak on 4/22/19.
//

#ifndef P1_PARSER_H
#define P1_PARSER_H

#include "node.h"

node* parser();
node* program();
node* vars();
node* block();
void stats();
void stat();
void mstats();
void in();
void out();
void iff();
void expr();
void a();
void n();
void m();
void r();
void z();
void ro();
void loop();
void assign();
void error(string);
node *create_node(string);

#endif //P1_PARSER_H
