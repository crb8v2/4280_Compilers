//
// Created by crbaniak on 4/22/19.
//

#ifndef P1_PARSER_H
#define P1_PARSER_H

#include "node.h"

node* createNode(string);
node* parser();
node* program();
node* vars();
node* block();

#endif //P1_PARSER_H
