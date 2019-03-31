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
//#include <locale>         // std::locale, std::isalpha

using namespace std;

struct token {
    std::string tokenID;
    int tokenInstance;
    int lineNumber;
};

struct symbolKey {
    int key;
    int value;
};


#endif //P1_TOKEN_H
