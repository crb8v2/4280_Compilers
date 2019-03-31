//
// Created by crbaniak on 3/8/19.
//

#include "scanner.h"
#include "testScanner.h"
#include "token.h"
#include "postfilter.h"

char symbolSet[18] = {'=','<','>', ':', '+', '-', '*', '/', '%', '.', '(', ')',
                      ',', '{', '}', ';', '[', ']'};

string keywords[12] = {"Begin", "End", "Loop", "Void", "INT", "Return", "Read",
                     "Output", "Program", "IFF", "Let", "Then"};


token finalTokenSet[256];
int tokenPos = 0;

int busy = 0;   //ignore lowercase if building an IDTK

int scanner(char c1, char c2, int state, int linecount){

    int charType = typeOfChar(c1);

    //check fsa table
   int column = FSATable(state, charType);

       switch(column) {
           case 001:
                break;
            case 002:
                state = makeDigit(c1, c2, state, linecount);
                break;
            case 003:
                makeSymbol(c1, linecount);
                //after symtk, go back to state one
                state = 0;
                break;
            case 004:
                state = makeID(c1, c2, state, linecount);
                break;
            case 111:
                cout << "IDTK" << endl;
                break;
           case 222:
               cout << "INTTK" << endl;
               break;
           case 333:
               cout << "SYMTK" << endl;
               break;
           case 999:
               cout << "EOFTK" << endl;
               break;

           case 666:

               if(busy == 1)
                   break;

               //needs to tell line number here
               fprintf(stderr, "ERROR: IDTK can not start with lowercase letter. \n");
               exit(EXIT_FAILURE);
   }

   return state;
}

int FSATable(int state, int col) {

    /*
     * STATES:
     * 1 = 001
     * 2 = 002
     * 3 = 003
     * 4 = 004
     *
     * TOKENS:
     * IDTK  = 111
     * INTTK = 222
     * SYMTK = 333
     * ERROR = 999
     *
     */

    int FSA_Table[4][5] = {
            {666, 004, 002, 003, 999},
            {222, 222, 002, 222, 222},
            {333, 333, 333, 333, 333},
            {004, 004, 004, 111, 111}
    };

    int tableString = FSA_Table[state][col];

    return tableString;

}

int typeOfChar(char c1){

    int tableColumn = -1;

    if(isalpha(c1) && islower(c1)) {
//        cout << "lowercase" << endl;
        tableColumn = 0;
    }else if(isalpha(c1) && isupper(c1)) {
//        cout << "uppercase" << endl;
        tableColumn = 1;
    }else if(isdigit(c1)){
//        cout << "digit" << endl;
        tableColumn = 2;
    }else{                          //works
//        cout << "symbol" << endl;
        tableColumn = 3;

    }

    return tableColumn;
}

int makeDigit(char c1, char c2, int state, int linecount){

    finalTokenSet[tokenPos].tokenLiteral += c1;
    finalTokenSet[tokenPos].linecount = linecount;

    if(isdigit(c2)){
        state = 1;
    } else {
        finalTokenSet[tokenPos].tokenID = "INTTK";
        state = 0;
        tokenPos++;
    }
    return state;
}

void makeSymbol(char c1, int linecount){
    int ii;
    for( ii = 0; ii < sizeof(symbolSet); ii++){
        if(c1 == symbolSet[ii]) {
            finalTokenSet[tokenPos].tokenID = "SYMTK";
            finalTokenSet[tokenPos].tokenLiteral = c1;
            finalTokenSet[tokenPos].linecount = linecount;


            tokenPos++;
        }
    }
}

int makeID(char c1, char c2, int state, int linecount){

    finalTokenSet[tokenPos].tokenLiteral += c1;
    finalTokenSet[tokenPos].linecount = linecount;
    busy = 1;

    if(isalpha(c2) || isdigit(c2)){
        state = 3;
    } else {
        //check if keyword
        int ii;
        for(ii = 0; ii < 12; ii++) {
            if (finalTokenSet[tokenPos].tokenLiteral == keywords[ii]){
                finalTokenSet[tokenPos].tokenID =  keywords[ii] + "TK";
                break;
            }else{
            finalTokenSet[tokenPos].tokenID = "IDTK";
            }
        }

            state = 0;
            tokenPos++;
            busy = 0;
    }

    return state;
}

void printTokens(){
    int ii = 0;

    cout << endl << endl;

    for(ii = 0; ii < tokenPos; ii++){
        cout << setw(8) << finalTokenSet[ii].tokenID << "  ";
        cout << setw(8) << finalTokenSet[ii].tokenLiteral << "  ";
        cout << setw(8) << "Line: " << finalTokenSet[ii].linecount << endl;

    }
    cout << "   EOFTK" << endl;
}
