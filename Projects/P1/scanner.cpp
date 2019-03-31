//
// Created by crbaniak on 3/8/19.
//

#include "scanner.h"
#include "testScanner.h"
#include "token.h"
#include "postfilter.h"

void scanner(char c1, char c2, int state){
    // run char against FSA table
    cout << c1 << endl;

//    //id what type of char - uc, lc, sym, eof

    int charType = typeOfChar(c1);

    //check fsa table
   int column = FSATable(state, charType);

       switch(column) {
       case 001:
           cout << "state changed to 1" << endl;
           state = 1;
           break;
       case 002:
           cout << "state changed to 2" << endl;
           state = 2;
           break;
       case 003:
           cout << "state changed to 3 = SYMTK, new state = 1" << endl;
           postfilter(333);
           state = 1;
           break;
       case 004:
           cout << "state changed to 4" << endl;
           state = 4;
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
               //needs to tell line number here
               fprintf(stderr, "IDTK can not start with lowercase letter. \n");
               exit(EXIT_FAILURE);
   }
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