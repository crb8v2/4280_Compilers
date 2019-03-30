//
// Created by crbaniak on 3/26/19.
//

#include "prefilter.h"

// get line number

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
    cout << source;

    // closing output file
    ofs.close();

    // closing input file
    readFile.close();
}

