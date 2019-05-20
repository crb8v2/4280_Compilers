//
// Created by crbaniak.
//

#include "scanner.h"
#include "token.h"
#include "parser.h"
#include "printTree.h"
#include "node.h"

#include <stdio.h>

//creates a raw file of the user input / pipe
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

    datFile.close();
}

// take input file and convert to raw file
void writeToRawFile(string filename){
    ifstream infile(filename.c_str());
    ofstream outfile("raw.input1");
    string content = "";
    int ii;

    for(ii=0 ; infile.eof()!=true ; ii++) // get content of infile
        content += infile.get();

    content.erase(content.end()-1);     // erase last character
    infile.close();
    outfile << content;                 // output
    outfile.close();
}

//checks is a filename given exists
bool fexists(string& filename)
{
    ifstream file(filename.c_str());
    return (bool)file;
}

int main(int argc, char *argv[]) {

    string filename;

    if (argc == 1) {                    // get keyboard input or pipe and write to file
        createRawFile(filename);

    } else if (argc == 2) {             // get input from a file

        // argv[1] is filename (second param)
        filename = argv[1];

        filename.append(".input1");

        if(fexists(filename) == false){     //check if file exists
            fprintf(stderr, "File does not exists. \n");
            exit(EXIT_FAILURE);
        }
        writeToRawFile(filename);

    } else if (argc > 2) {              // else error
        fprintf(stderr, "Too many command line arguments. \n");
        exit(EXIT_FAILURE);
    };

    prefilter("raw.input1");        // removes comments and get line number
    toScanner("toScanner.txt");   // parses file char by char

    printTokens();

    node* root = parser();

    printTree(root, 0);


//    int ii;
//    for(ii = 0; ii < 256; ii++){
//        if(finalTokenSet[ii].tokenID != ""){
//            cout << setw(10) << finalTokenSet[ii].tokenID << "  ";
//        }
//    }

    return 0;
}