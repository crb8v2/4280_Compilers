//
// Created by crbaniak on 6/5/19.
//

#include "semantics.h"
#include "node.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>


ofstream myfile;

string program(node* parent){

    return block(parent->child1);
}

string vars(node* parent){

    if (parent->child0 != NULL) {
        return vars(parent->child0);
    } else if (parent->child1 != NULL){
        return vars(parent->child1);
    } else if (parent->child2 != NULL){
        return vars(parent->child2);
    }  else if (parent->child3 != NULL){
        return vars(parent->child3);
    }

        return "";
}

string block(node* parent) {

    //check begin

    if (parent->child0 != NULL) {
        return stats(parent->child0);
    } else if (parent->child1 != NULL){
        return stats(parent->child1);
    } else if (parent->child2 != NULL){
        return stats(parent->child2);
    }  else if (parent->child3 != NULL){
        return stats(parent->child3);
    }


}

string stats(node* parent){

    return stat(parent->child0) + mstats(parent->child1);

}

string stat(node* parent){

    if( parent->child0->id == "<in>") {
                return in(parent->child0);
        } else if(parent->child0->id == "<out>"){
                return out(parent->child0);
        } else if(parent->child0->id == "<block>"){
                return block(parent->child0);
        } else if(parent->child0->id == "<IFF>"){
                return iff(parent->child0);
        } else if(parent->child0->id == "<loop>"){
                return loop(parent->child0);
        } else if(parent->child0->id == "<assign>"){
                return assign(parent->child0);
        }

        if( parent->child1->id == "<in>") {
                return in(parent->child1);
        } else if(parent->id == "<out>"){
                return out(parent->child1);
        } else if(parent->child1->id == "<block>"){
                return block(parent->child1);
        } else if(parent->id == "<IFF>"){
                return iff(parent->child1);
        } else if(parent->id == "<loop>"){
                return loop(parent->child1);
        } else if(parent->child1->id == "<assign>"){
                return assign(parent->child1);
        }

        if( parent->child2->id == "<in>") {
                return in(parent->child2);
        } else if(parent->child2->id == "<out>"){
                return out(parent->child2);
        } else if(parent->child2->id == "<block>"){
                return block(parent->child2);
        } else if(parent->child2->id == "<IFF>"){
                return iff(parent->child2);
        } else if(parent->child2->id == "<loop>"){
                return loop(parent->child2);
        } else if(parent->child2->id == "<assign>"){
                return assign(parent->child2);
        }

        if( parent->child3->id == "<in>") {
            return in(parent->child3);
        } else if(parent->child3->id == "<out>"){
            return out(parent->child3);
        } else if(parent->child3->id == "<block>"){
            return block(parent->child3);
        } else if(parent->child3->id == "<IFF>"){
            return iff(parent->child3);
        } else if(parent->child3->id == "<loop>"){
            return loop(parent->child3);
        } else if(parent->child3->id == "<assign>"){
            return assign(parent->child3);
        }

}

string mstats(node* parent){
        return "";
}

string in(node* parent){

    printToFile("READ T");

        return "";
}

string out(node* parent){

    printToFile("WRITE T");

        return "";
}


string iff(node* parent){
        return "";
}

string expr(node* parent){
        return "";
}

string a(node* parent){
        return "";
}

string n(node* parent){
        return "";
}

string m(node* parent){
        return "";
}

string r(node* parent){
        return "";
}

string z(node* parent){
        return "";
}

string ro(node* parent){
        return "";
}

string loop(node* parent){
        return "";
}

string assign(node* parent){
        return "";
}

void prePrint(){

    printToFile("LOAD 0");
    printToFile("PUSH");

    cout << "LOAD 0" << endl;
    cout << "PUSH" << endl;
}

void gatherVars() {

    int varCount = 0;

    static int arrPos = 0;

    string arrayOfVars[30];

    printToFile("T 0");

    for (int ii = 0; ii < tokenPos; ii++) {

        static int count = 0;

        if (finalTokenSet[ii].tokenID == "IDTK") {

//            arrayOfVars[arrPos] = finalTokenSet[ii].tokenLiteral;
//            arrPos++;
            printToFile(finalTokenSet[ii].tokenLiteral + " 0");

            varCount++;
            count++;
        }
    }

//    for(int jj = 0; jj < 30; jj++) {
//        for (int kk = 0; kk < 30; kk++){
//            if (arrayOfVars[jj] == arrayOfVars[kk]) {
//                arrayOfVars[jj] = "";
//            }
//        }
//    }
//
//    for(int ll = 0; ll < 30; ll++){
//        if(arrayOfVars[ll] != ""){
//            printToFile(finalTokenSet[ll].tokenLiteral + " 0");
//
//        }
//    }

    cout << "Done - check test.asm file for output" << endl;

    closeFile();

}

void printToFile(string theThing){

    string arrOfVars[30];
    static int pos = 0;

//    arrOfVars[pos] = theThing;
//    cout << arrOfVars[pos] << endl;
//    pos++;

//    for(int jj = 0; jj < 30; jj++) {
//        for (int kk = 0; kk < 30; kk++){
//            if (arrOfVars[jj] == arrOfVars[kk] && arrOfVars[jj] != "") {
//                arrOfVars[kk] = "0";
//                break;
//            }
//        }
//    }

//    for(int ii = 0; ii < 30; ii++) {
//        if(arrOfVars[ii] != "" || arrOfVars[ii] != "0") {

            myfile.open("test.asm", std::ios::app);
            myfile << theThing +"\n";
            myfile.close();
//        }
//    }
    return;
}

void closeFile(){
    myfile.close();
}