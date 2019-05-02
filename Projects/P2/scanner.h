//
// Created by crbaniak on 3/8/19.
//

#ifndef P1_SCANNER_H
#define P1_SCANNER_H

#include "token.h"

extern token finalTokenSet[];
extern int fileSize;

void toScanner(string);
void prefilter(string);
int scanner(char, char, int, int);
int typeOfChar(char);
int FSATable(int, int);
int makeDigit(char, char, int, int);
void makeSymbol(char, int);
void printTokens();
int makeID(char, char, int, int);

#endif //P1_SCANNER_H
