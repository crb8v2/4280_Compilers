//
// Created by crbaniak on 2/11/19.
//

#include "tree.h"

void BST::buildTree(char d)
{
    node* t = new node;
    node* parent;
    t->data = d;
    t->left = NULL;
    t->right = NULL;
    parent = NULL;

    // is this a new tree?
    if(isEmpty()) root = t;
    else
    {
        //Note: ALL insertions are as leaf nodes
        node* curr;
        curr = root;
        // Find the Node's parent
        while(curr)
        {
            parent = curr;
            if(t->data > curr->data) curr = curr->right;
            else curr = curr->left;
        }

        if(t->data < parent->data)
            parent->left = t;
        else
            parent->right = t;
    }
}

void BST::print_inorder()
{
    cout << "Inorder:";
    inorder(root);
}

void BST::inorder(node* p)
{
    // work to do here.
    ofstream logFile("out.inorder");
    if(p != NULL && logFile.is_open())
    {
        if(p->left) inorder(p->left);
        cout<<" "<<p->data<<" ";
        logFile << p->data;
        if(p->right) inorder(p->right);
        logFile.close();
    }
    else return;
}

void BST::print_preorder()
{
    cout << "Preorder:";
    preorder(root);
}

void BST::preorder(node* p)
{
    ofstream logFile("out.preorder");
    if(p != NULL && logFile.is_open())
    {
        cout<<" "<<p->data<<" ";
        logFile << p->data;
        if(p->left) preorder(p->left);
        if(p->right) preorder(p->right);
        logFile.close();
    }
    else return;
}

void BST::print_postorder()
{
    cout << "Postorder:";
    postorder(root);
}

void BST::postorder(node* p)
{
    ofstream logFile("out.postorder");
    if(p != NULL )
    {
        if(p->left) postorder(p->left);
        if(p->right) postorder(p->right);
        cout<<" "<<p->data<<" ";
        logFile <<" "<<p->data<<" ";
        logFile << "connor was here";
//        logFile.close();
    }
    else return;
}
