//
// Created by crbaniak on 3/8/19.
//

#include "scanner.h"
#include "token.h"

void scanner(char c1){
    // run char against FSA table
            cout << c1 << endl;
}

string FSATable() {

    //create FSA table
    string FSA_table[4][6];
    FSA_table[0][0] = "error";
    FSA_table[0][1] = "S4";
    FSA_table[0][2] = "S2";
    FSA_table[0][3] = "S3";
    FSA_table[0][4] = "S1";
    FSA_table[0][5] = "EOFTK";

    FSA_table[1][0] = "INTTK";
    FSA_table[1][1] = "INTTK";
    FSA_table[1][2] = "S2";
    FSA_table[1][3] = "INTTK";
    FSA_table[1][4] = "INTTK";
    FSA_table[1][5] = "INTTK";

    FSA_table[2][0] = "SYMTK";
    FSA_table[2][1] = "SYMTK";
    FSA_table[2][2] = "SYMTK";
    FSA_table[2][3] = "SYMTK";
    FSA_table[2][4] = "SYMTK";
    FSA_table[2][5] = "SYMTK";

    FSA_table[3][0] = "S4";
    FSA_table[3][1] = "S4";
    FSA_table[3][2] = "S4";
    FSA_table[3][3] = "IDTK";
    FSA_table[3][4] = "IDTK";
    FSA_table[3][5] = "IDTK";


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

    string tableString = FSA_table[0][0];

    return tableString;

}

void error(){
    cout << "an error has taken place on line...";
    exit(0);
}

