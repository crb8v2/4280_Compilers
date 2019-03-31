//
// Created by crbaniak on 3/8/19.
//

#include "scanner.h"
#include "testScanner.h"
#include "token.h"

void scanner(char c1, int state){
    // run char against FSA table
    cout << c1 << endl;

//    //id what type of char - uc, lc, sym, eof

    int charType = typeOfChar(c1);

    //check fsa table
   int word = FSATable(state, charType);
   cout << word << endl;
}

int FSATable(int state, int col) {

    int FSA_Table[4][6] = {
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
        cout << "lowercase" << endl;
        tableColumn = 0;
    }else if(isalpha(c1) && isupper(c1)) {
        cout << "uppercase" << endl;
        tableColumn = 1;
    }else if(isdigit(c1)){
        cout << "digit" << endl;
        tableColumn = 3;
    }else{
        cout << "symbol" << endl;
        tableColumn = 4;
    }

    return tableColumn;

}



void error(){
    cout << "an error has taken place on line...";
    exit(0);
}




//    //create FSA table
//    string FSA_table[4][6];
//    FSA_table[0][0] = "error";
//    FSA_table[0][1] = "S4";
//    FSA_table[0][2] = "S2";
//    FSA_table[0][3] = "S3";
//    FSA_table[0][4] = "S1";
//    FSA_table[0][5] = "EOFTK";
//
//    FSA_table[1][0] = "INTTK";
//    FSA_table[1][1] = "INTTK";
//    FSA_table[1][2] = "S2";
//    FSA_table[1][3] = "INTTK";
//    FSA_table[1][4] = "INTTK";
//    FSA_table[1][5] = "INTTK";
//
//    FSA_table[2][0] = "SYMTK";
//    FSA_table[2][1] = "SYMTK";
//    FSA_table[2][2] = "SYMTK";
//    FSA_table[2][3] = "SYMTK";
//    FSA_table[2][4] = "SYMTK";
//    FSA_table[2][5] = "SYMTK";
//
//    FSA_table[3][0] = "S4";
//    FSA_table[3][1] = "S4";
//    FSA_table[3][2] = "S4";
//    FSA_table[3][3] = "IDTK";
//    FSA_table[3][4] = "IDTK";
//    FSA_table[3][5] = "IDTK";


//    for(int i=0; i<3; i++)    //This loops on the rows.
//    {
//        for(int j=0; j<5; j++) //This loops on the columns
//        {
//            cout << FSA_table[i][j]  << "  ";
//        }
//        cout << endl;
//    }
//
//    cout << endl;
//    cout << endl;