//
// Created by crbaniak.
//

#include "scanner.h"
#include "token.h"
#include "prefilter.h"
#include "testScanner.h"

#include <stdio.h>

void createRawFile(string filename){
    //output stream and .dat filename
    ofstream datFile;
    filename = "raw.input1";

    //open file for read
    // .c_str() converts to formal c string
    datFile.open(filename.c_str());

    datFile << "\n";

    string input;
    while (getline(cin, input)) {
        datFile << input << "\n";
    }

    datFile << "\n\n";

    //close file
    datFile.close();

    cout << endl << endl;
}

void writeToRawFile(string filename){

    ifstream infile(filename.c_str());
    ofstream outfile("raw.input1");
    string content = "";
    int i;

    for(i=0 ; infile.eof()!=true ; i++) // get content of infile
        content += infile.get();

    i--;
    content.erase(content.end()-1);     // erase last character

    cout << i << " characters read...\n";
    infile.close();

    outfile << content;                 // output
    outfile.close();

}

int main(int argc, char *argv[]) {

    string filename;

    if (argc == 1) {                    // get keyboard input or pipe and write to file
        createRawFile(filename);

    } else if (argc == 2) {             // get input from a file

        // argv[1] is filename (second param)
        filename = argv[1];

        writeToRawFile(filename);

    } else if (argc > 2) {              // else error
        fprintf(stderr, "Too many command line arguments. \n");
        exit(EXIT_FAILURE);
    };


    prefilter("raw.input1");
    testScanner("toScanner.txt");

    return 0;
}