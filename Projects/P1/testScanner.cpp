//
// Created by crbaniak on 3/8/19.
//

#include "testScanner.h"
#include "token.h"
#include "scanner.h"

void testScanner(string filename){

    // go through file char by char and compare input to the fsa table.
    // get char by char w lookaheadand use FSA table

    ifstream infile(filename.c_str());

    while (true) {
        char c1, c2;
        infile >> c1;
        c2 = infile.peek();     //lookahead char

        if( infile.eof() )
            break;

        //call scanner
        scanner(c1);

//        cout << c1 << endl;
        cout << c2 << " peek" << endl;
    }
}