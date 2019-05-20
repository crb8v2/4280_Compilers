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
node* stats();
node* stat();
node* mstats();
node* in();
node* out();
node* iff();
node* expr();
node* a();
node* n();
node* m();
node* r();
node* z();
node* ro();
node* loop();
node* assign();
void error(string);
node *create_node(string);

#endif //P1_PARSER_H
