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

    if( parent->child0->literal == "<in>") {
                return in(parent->child0);
        } else if(parent->child0->literal == "<out>"){
                return out(parent->child0);
        } else if(parent->child0->literal == "<block>"){
                return block(parent->child0);
        } else if(parent->child0->literal == "<IFF>"){
                return iff(parent->child0);
        } else if(parent->child0->literal == "<loop>"){
                return loop(parent->child0);
        } else if(parent->child0->literal == "<assign>"){
                return assign(parent->child0);
        }

        if( parent->child1->literal == "<in>") {
                return in(parent->child1);
        } else if(parent->literal == "<out>"){
                return out(parent->child1);
        } else if(parent->child1->literal == "<block>"){
                return block(parent->child1);
        } else if(parent->literal == "<IFF>"){
                return iff(parent->child1);
        } else if(parent->literal == "<loop>"){
                return loop(parent->child1);
        } else if(parent->child1->literal == "<assign>"){
                return assign(parent->child1);
        }

        if( parent->child2->literal == "<in>") {
                return in(parent->child2);
        } else if(parent->child2->literal == "<out>"){
                return out(parent->child2);
        } else if(parent->child2->literal == "<block>"){
                return block(parent->child2);
        } else if(parent->child2->literal == "<IFF>"){
                return iff(parent->child2);
        } else if(parent->child2->literal == "<loop>"){
                return loop(parent->child2);
        } else if(parent->child2->literal == "<assign>"){
                return assign(parent->child2);
        }

        if( parent->child3->literal == "<in>") {
            return in(parent->child3);
        } else if(parent->child3->literal == "<out>"){
            return out(parent->child3);
        } else if(parent->child3->literal == "<block>"){
            return block(parent->child3);
        } else if(parent->child3->literal == "<IFF>"){
            return iff(parent->child3);
        } else if(parent->child3->literal == "<loop>"){
            return loop(parent->child3);
        } else if(parent->child3->literal == "<assign>"){
            return assign(parent->child3);
        }

}

string mstats(node* parent){
        return "";
}

string in(node* parent){

    printToFile("READ X1");

        return "";
}

string out(node* parent){

    printToFile("WRITE X1");

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

//    cout << "LOAD 0" << endl;
//    cout << "PUSH" << endl;
}

void gatherVars() {

    int varCount = 0;

    for (int ii = 0; ii < tokenPos; ii++) {

        static int count = 0;

        if (finalTokenSet[ii].tokenID == "IDTK") {
//            cout << finalTokenSet[ii].tokenLiteral << " " << count << endl;
            printToFile(finalTokenSet[ii].tokenLiteral + " 0");
            varCount++;
            count++;
        }
    }

    cout << "Done - check test.asm file for output" << endl;

    closeFile();

}

void printToFile(string theThing){

//    myfile.open ("test.asm");
    myfile.open("test.asm", std::ios::app);
    myfile << theThing + "\n";
    myfile.close();
    return;
}

void closeFile(){
    myfile.close();
}