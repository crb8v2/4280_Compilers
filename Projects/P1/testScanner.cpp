//
// Created by crbaniak on 3/8/19.
//

#include "testScanner.h"
#include "token.h"
#include "scanner.h"

void testScanner(string filename){
    //THIS IS RESPONSIBLE FOR THE PROGRAMS STATE
    int state = 0;
    int linecount = 0;

    ifstream infile(filename.c_str());

    while (true) {
        char c1, c2;
        infile.get(c1);
        if(c1 == '\n') {
            cout << "newlineeeeeeeeeeeeee" << endl;
            linecount++;
        }
        c2 = infile.peek();     //lookahead char

        if( infile.eof() )
            break;


        cout << "line nummmmmmmmmm    " << linecount << endl;

        //call scanner
        state = scanner(c1, c2, state, linecount);
    }
    // call final print
        printTokens();
}