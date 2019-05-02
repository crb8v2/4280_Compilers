//
// Created by crbaniak on 4/22/19.
//

#include "parser.h"
#include "node.h"
#include "token.h"
#include "scanner.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

token tk;
static int posInFTS = 0;

void parser() {
    tk = finalTokenSet[posInFTS];
//    posInFTS+=1;
    program();

    return;
}

//<program>  ->     PROGRAM <var> <block>
void program() {

    vars();
    block();

    if(finalTokenSet[fileSize].tokenID == "EOFtk"){
        cout << "Parse OK\n";
    } else {
        cout << "Parse failed : error out";
    }

    return;
}


void vars() {

    if(finalTokenSet[posInFTS].tokenID == "INTTK") {
        posInFTS += 1;
        tk = finalTokenSet[posInFTS];

        if(finalTokenSet[posInFTS].tokenID == "IDTK"){
            posInFTS += 1;
            tk = finalTokenSet[posInFTS];

            if(finalTokenSet[posInFTS].tokenID == "NUMTK"){
                posInFTS += 1;
                tk = finalTokenSet[posInFTS];
                vars();
                return;

            } else
                error("NUMTK");
        } else
            error("IDTK");
    } else
        return;

    return;
}


void block() {

    if (finalTokenSet[posInFTS].tokenID == "BeginTK") {
        posInFTS += 1;
        tk = finalTokenSet[posInFTS];
    } else
        error("BeginTK");

    vars();
//    stats();

    if (finalTokenSet[posInFTS].tokenID == "EndTK") {
        posInFTS += 1;
        tk = finalTokenSet[posInFTS];
    } else
        error("EndTK");

    return;
}

void stats(){

    stat();

    if(finalTokenSet[posInFTS].tokenID == "SYMTK:"){
        posInFTS += 1;
        tk = finalTokenSet[posInFTS];
    } else
        error("SYMTK:");

    mstats();

    return;
}

void stat(){

    if(finalTokenSet[posInFTS].tokenID == "OutputTK"){
        posInFTS += 1;
        tk = finalTokenSet[posInFTS];
        out();
    }


    return;
}

void mstats(){

    return;
}

void out(){
//    if(finalTokenSet[posInFTS].tokenID == "OutputTK"){
//        posInFTS += 1;
//        tk = finalTokenSet[posInFTS];
//        if(finalTokenSet[posInFTS].tokenID == "SYMTK["){
//            posInFTS += 1;
//            tk = finalTokenSet[posInFTS];
//            expr();
//            if(finalTokenSet[posInFTS].tokenID == "SYMTK]"){
//                posInFTS += 1;
//                tk = finalTokenSet[posInFTS];
//            } else
//                error("SYMTK]");
//        } else
//            error("SYMTK[");
//    } else
//        error("OutputTK");

    return;
}

void expr(){

    return;
}

void error(string bean){

    cout << "ERROR in Line: " << finalTokenSet[posInFTS+1].linecount + 1 << " -- Recieved: "
    << finalTokenSet[posInFTS+1].tokenID << " -- Expected: " << bean << endl;

    exit(0);
}





//static Node * stats(){
//    Node * node = createNode(toString(stats));
//
//    node->child_0 = stat();
//    if (isInstance(tk.instance, toString( COLON_tk ) ) ) {
//        tk = scanner();
//    }else
//        parseError( toString( COLON_tk ) );
//    node->child_1 = mStat();
//    return node;
//}
//static Node * stat() {
//    Node * node = createNode(toString(stat));
//
//    if ( isInstance( tk.instance, toString( Read_tk ) ) ) {
//        node->child_0 =  in();
//    } else if ( isInstance( tk.instance, toString( Output_tk ) ) ) {
//        node->child_0 = out();
//    } else if ( isInstance( tk.instance, toString( IFF_tk ) ) )  {
//        node->child_0 = iff();
//    } else if ( isInstance( tk.instance, toString( Loop_tk ) ) ) {
//        node->child_0 = loop();
//    } else if(isInstance( tk.instance, toString( Begin_tk ) ) ){
//        node->child_0 = block();
//    } else if ( tk.id == IDENTtk && isNotKeyWd(tk.instance)){
//        node->child_0 =  assign();
//    }else
//        parseError( toString( Statment ) );
//    return  node;
//}
//
//static Node * mStat(){
//    Node * node = createNode(toString(mStat));
//    if( isInstance(tk.instance, toString(End_tk)))
//        return NULL;
//    if (   tk.id == IDENTtk ){
//        node->child_0 = stat();
//        if (isInstance(tk.instance, toString( COLON_tk ) ) ) {
//            tk = scanner();
//        }else
//            parseError( toString( COLON_tk ) );
//        node->child_1 = mStat();
//        return node;
//    }
//
//    return NULL;
//}
//static Node * out(){
//    Node * node = createNode( toString( out ) );
//    if (isInstance(tk.instance, toString(Output_tk ) ) ) {
//        tk = scanner();
//        if (isInstance(tk.instance, toString(OPEN_BRACKET_tk))) {
//            tk = scanner();
//            node->child_0 = expr();
//            if (isInstance(tk.instance, toString(CLOSE_BRACKET_tk))) {
//                tk = scanner();
//            } else
//                parseError(toString(CLOSE_BRACKET_tk));
//        } else
//            parseError(toString(OPEN_BRACKET_tk));
//    } else{
//        parseError(toString(Output_tk) );
//    }
//
//    return node;
//}
//static Node * in(){
//    Node * node = createNode( toString( in ) );
//
//    if ( isInstance(tk.instance, toString( Read_tk ) )) {
//        tk = scanner();
//        if (isInstance(tk.instance, toString(OPEN_BRACKET_tk))) {
//            tk = scanner();
//            if ( tk.id == IDENTtk && isNotKeyWd( tk.instance ) ) {
//                node->linkToken= createTokenNode();
//                tk = scanner();
//                if (isInstance(tk.instance, toString(CLOSE_BRACKET_tk))) {
//                    tk = scanner();
//                } else
//                    parseError(toString(CLOSE_BRACKET_tk));
//            } else
//                parseError(toString(IDENTtk));
//        } else
//            parseError(toString(OPEN_BRACKET_tk));
//    }else
//        parseError(toString(Read_tk) );
//    return node;
//}
//static Node * iff(){
//    Node * node = createNode(toString(iff));
//
//    if ( isInstance( tk.instance, toString( IFF_tk ) ) ){
//        tk= scanner();
//        if( isInstance( tk.instance, toString( OPEN_BRACKET_tk ) ) ){
//            tk = scanner();
//            node->child_0 = expr();
//            node->child_1 = ro();
//            node->child_2 = expr();
//            if (isInstance( tk.instance, toString( CLOSE_BRACKET_tk ) ) ){
//                tk = scanner();
//                node->child_3 = stat();
//            } else
//                parseError( toString( CLOSE_BRACKET_tk ) );
//        } else
//            parseError( toString( OPEN_BRACKET_tk ) );
//    } else
//        parseError( toString( IFF_tk) );
//    return node;
//}
//static Node * assign(){
//    Node * node = createNode(toString(assign));
//
//    if( tk.id == IDENTtk  && isNotKeyWd( tk.instance )){
//        node->linkToken = createTokenNode();
//        tk = scanner();
//        if ( isInstance( tk.instance, toString( EQUAL_tk ) ) ) {
//            tk = scanner();
//            node->child_0 = expr();
//        } else parseError( toString( EQUAL_tk) );
//    } else parseError( toString( IDENTtk) );
//    return node;
//}
//static Node * loop(){
//    Node * node = createNode(toString(loop));
//
//    if ( isInstance( tk.instance, toString( Loop_tk ) ) ){
//        tk = scanner();
//        if( isInstance( tk.instance, toString( OPEN_BRACKET_tk ) ) ){
//            tk = scanner();
//            node->child_0 = expr();
//            node->child_1 = ro();
//            node->child_2 = expr();
//            if (isInstance( tk.instance, toString( CLOSE_BRACKET_tk ) ) ){
//                tk = scanner();
//                node->child_3 = stat();
//            } else
//                parseError( toString( CLOSE_BRACKET_tk ) );
//        } else
//            parseError( toString( OPEN_BRACKET_tk ) );
//    } else
//        parseError( toString( Loop_tk) );
//    return node;
//}
//static Node * expr(){
//    Node * node = createNode(toString(expr));
//    node->child_0 =  a();
//    node->child_1 =  k();
//    return node;
//}
//static Node * k(){
//    Node * node = createNode(toString(k));
//
//    if ( isInstance(tk.instance, toString(MINUS_tk))
//         || isInstance( tk.instance, toString( PLUS_tk ) ) ){
//        node->linkToken = createTokenNode();
//        tk = scanner();
//        node->child_0 = expr();
//        return node;
//
//    }
//    return NULL;
//}
//static Node * a(){
//    Node * node = createNode(toString(a));
//
//    node->child_0 = n();
//    if ( isInstance( tk.instance, toString( ASTERISK_tk ) ) ){
//        node->linkToken = createTokenNode();
//        tk = scanner();
//        node->child_1 = a();
//    }
//    return node;
//}
//static Node * n(){
//    Node * node = createNode(toString(n));
//
//    node->child_0 = m();
//    if (isInstance( tk.instance, toString( SLASH_tk ))){
//        node->linkToken =createTokenNode();
//        tk = scanner();
//        node->child_1 = n();
//    }
//    return node;
//}
//static Node * m(){
//    Node * node = createNode(toString(m));
//
//    if (isInstance( tk.instance, toString( MINUS_tk ))){
//        node->linkToken = createTokenNode();
//        tk=scanner();
//        node->child_0 = m();
//    } else
//        node->child_0 = r();
//    return node;
//}
//static Node * r(){
//    Node * node = createNode(toString(r));
//
//    if ( isInstance( tk.instance, toString( OPEN_BRACKET_tk ))){
//        tk = scanner();
//        node->child_0 = expr();
//        if ( isInstance( tk.instance, toString( CLOSE_BRACKET_tk ))){
//            tk = scanner();
//        } else
//            parseError( toString( OPEN_BRACKET_tk) );
//    } else if( tk.id == NUMtk || ( tk.id == IDENTtk && isNotKeyWd( tk.instance ) ) ) {
//        node->linkToken = createTokenNode();
//        tk = scanner();
//    }else
//        parseError( "expr, identifier or integer" );
//    return node;
//}
//static Node * ro(){
//    Node * node = createNode(toString(ro));
//    node->linkToken = createTokenNode( tk );
//    if (isInstance( tk.instance, toString( LESS_THAN_tk ) ) ||
//        isInstance( tk.instance, toString( GREATER_THAN_tk ) ) ){
//        tk =scanner();
//        return node;
//    }else if (isInstance( tk.instance, toString( EQUAL_tk ) ) ){
//        tk = scanner();
//        node->linkToken->link = createTokenNode( tk );
//        if (isInstance( tk.instance, toString( EQUAL_tk ) ) ||
//            isInstance( tk.instance, toString( LESS_THAN_tk ) ) ||
//            isInstance( tk.instance, toString( GREATER_THAN_tk ) ) ){
//            tk = scanner();
//            return node;
//        }
//    } else
//        parseError("cond operator");
//    return NULL;
//}
