//
// Created by crbaniak on 4/22/19.
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


struct token {
    string tokenID;
    string tokenLiteral;
    int linecount;
};


#endif //P1_TOKEN_H
