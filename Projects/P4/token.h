//
// Created by crbaniak on 3/26/19.
//

#ifndef P1_TOKEN_H
#define P1_TOKEN_H


#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <iomanip>

using namespace std;
//typedef
struct token {
    string tokenID;
    string tokenLiteral;

    int linecount;
};
//token_t ^^^

#endif //P1_TOKEN_H
