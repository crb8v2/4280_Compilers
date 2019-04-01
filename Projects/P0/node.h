//
// Created by crbaniak on 2/11/19.
//

#ifndef P0_NODE_H
#define P0_NODE_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <set>

using namespace std;

class BST{
    private:
        struct node{
            node* left;
            node* right;
            char data;
            std::set<string> myset;
        };

        node* root;

    public:
    BST(){
        root = NULL;
    }

    bool isEmpty() const { return root==NULL; }
    void buildTree(char);
    void inorder(node*);
    void print_inorder();
    void preorder(node*);
    void print_preorder();
    void postorder(node*);
    void print_postorder();


};



#endif //P0_NODE_H
