//
// Created by crbaniak on 3/8/19.
//

#include "scanner.h"
#include "token.h"

char symbolSet[18] = {'=','<','>', ':', '+', '-', '*', '/', '%', '.', '(', ')',
                      ',', '{', '}', ';', '[', ']'};

string keywords[12] = {"Begin", "End", "Loop", "Void", "INT", "Return", "Read",
                     "Output", "Program", "IFF", "Let", "Then"};

token finalTokenSet[256];
int tokenPos = 0;   // finalTokenSet placeholder
int busy = 0;       // ignore lowercase if building an IDTK

// strips comments from raw.input1 and makes to file for
void prefilter(string filename){

    string source;
    ifstream readFile(filename.c_str());

    // open file in write mode or out mode
    ofstream ofs;
    ofs.open("toScanner.txt", ofstream::out);

    getline(readFile, source, '\0');

    while(source.find("/*") != std::string::npos) {
        size_t Beg = source.find("/*");
        source.erase(Beg, (source.find("*/", Beg) - Beg)+2);
    }

    while(source.find("//") != std::string::npos) {
        size_t Beg = source.find("//");
        source.erase(Beg, source.find("\n", Beg) - Beg);
    }

    ofs << source;

    // closing output file
    ofs.close();

    // closing input file
    readFile.close();
}

void toScanner(string filename){
    int state = 0;          //program state
    int linecount = 0;      //line number holder

    ifstream infile(filename.c_str());

    while (true) {
        char c1, c2;
        infile.get(c1);

        if(c1 == '\n') {    //newline counter
            linecount++;
        }

        c2 = infile.peek();     //lookahead char

        if( infile.eof() )
            break;

        //call scanner
        state = scanner(c1, c2, state, linecount);
    }

    // call final output
    printTokens();
}


// returns case based on FSA table
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
               if(busy == 1) // allows lowercase letters if in IDTK
                   break;
               //needs to tell line number here
               fprintf(stderr, "ERROR: Line#: %d \n    IDTK can not start with lowercase letter. \n", linecount);
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

// idenifies type of char on the FSA Table
int typeOfChar(char c1){

    int tableColumn = -1;

    if(isalpha(c1) && islower(c1)) {        //lowercase
        tableColumn = 0;
    }else if(isalpha(c1) && isupper(c1)) {  //uppercase
        tableColumn = 1;
    }else if(isdigit(c1)){                  //digit
        tableColumn = 2;
    }else{                                  //symbol
        tableColumn = 3;
    }
    return tableColumn;
}

// creates an INTTK for as long as need be
int makeDigit(char c1, char c2, int state, int linecount){

    finalTokenSet[tokenPos].tokenLiteral += c1;     //append number
    finalTokenSet[tokenPos].linecount = linecount;  //linecount

    if(isdigit(c2)){
        state = 1;      // send back to state 2 if digit
    } else {
        finalTokenSet[tokenPos].tokenID = "INTTK";
        state = 0;      // send to initial state 1 if not a digit
        tokenPos++;     // increment token array
    }
    return state;
}

// id SYMTK, symbol literal, and line num
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

// makes an IDTK for as long as need be and checks for keyword token
int makeID(char c1, char c2, int state, int linecount){

    finalTokenSet[tokenPos].tokenLiteral += c1;
    finalTokenSet[tokenPos].linecount = linecount;
    busy = 1;       // allows lowercase to pass through

    if(isalpha(c2) || isdigit(c2)){     //continue IDTK with letters or numbers
        state = 3;      //state 4
    } else {
        //check if keyword
        int ii;
        for(ii = 0; ii < 12; ii++) {
            if (finalTokenSet[tokenPos].tokenLiteral == keywords[ii]){
                finalTokenSet[tokenPos].tokenID =  keywords[ii] + "TK";
                break;
            }else{      // not keyword
            finalTokenSet[tokenPos].tokenID = "IDTK";
            }
        }

            state = 0;      //state back to 1
            tokenPos++;     //increment token array
            busy = 0;       // no more allowing lowercase letters
    }

    return state;
}

// prints final token format: token, literal, line number
void printTokens(){
    int ii = 0;
    cout << endl << endl;
    for(ii = 0; ii < tokenPos; ii++){
        cout << setw(8) << finalTokenSet[ii].tokenID << "  " << endl;
//        cout << setw(8) << finalTokenSet[ii].tokenLiteral << "  ";
//        cout << setw(8) << "Line: " << finalTokenSet[ii].linecount << endl;
    }
    cout << "   EOFTK" << endl;
}
