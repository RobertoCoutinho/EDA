
#include<iostream>
#include <bits/stdc++.h>
//#include<stack> // para a preorder
#include "rbtree.h"
using namespace std;

//  Constructor
RBTree::RBTree(){
    nil = new  Node {};
    nil ->key = 0;
    nil ->left = nil ->right = nil ->parent = nil;
    nil ->color = BLACK;
    root = nil;
}
//  Destructor
RBTree::~RBTree(){
    //clear(root); // Para  casa: Codifiquem  esta  funcao
    delete  nil;
    nil = nullptr;
    root = nullptr;
}

void RBTree::preorder() const{
    Node* tree = root;
    stack<Node*> pilha;
    if(tree != nil){
        pilha.push(tree);
        while(!pilha.empty()){
            tree = pilha.top();
            pilha.pop();
            if(tree->color == BLACK){
                cout << "(" << tree->key << "," << tree->value << ") -> Black" << endl;
            }else{
                cout << "(" << tree->key << "," << tree->value << ") -> Red" << endl;
            }
            if(tree->right != nil){
                pilha.push(tree->right);
            }
            if(tree->left != nil){
                pilha.push(tree->left);
            }
        }
    } 
}

void  RBTree :: left_rotate(Node *x){
    Node *y = x->right;
    x->right = y->left;
    if (y->left != nil){
        y->left ->parent = x;
    }
    y->parent = x->parent;
    if (x->parent  == nil) {
        root = y;
    }
    else if (x == x->parent ->left) {
        x->parent ->left = y;
    } 
    else {
        x->parent ->right = y;
    }

    y->left = x;
    x->parent = y;
}



void  RBTree::right_rotate(Node *x){
    Node *y = x->left;
    x->left = y->right;
    if (y->right  != nil){
        y->right ->parent = x;
    }
    y->parent = x->parent;
    if (x->parent  == nil) {
        root = y;
    } 
    else if (x == x->parent ->right) {
        x->parent ->right = y;
    } 
    else {
        x->parent ->left = y;
    }
    y->right = x;
    x->parent = y;
}

void  RBTree :: insert (const  Tkey& key , const  Tvalue& v) {
    //  Allocate a new  Node
    Node *newNode = new  Node {};
    newNode ->key = key;
    newNode ->value = v;
    newNode ->left = newNode ->right = nil;
    newNode ->parent = nil;
    // Do a normal  BST  insert
    RBinsert(newNode);
}

void  RBTree :: RBinsert(Node *z) {
    Node *father = nil;
    Node *son = root;
    while (son != nil) {
        father = son;
        if(z->key == son ->key) { 
            //  Diferent  from  Cormen
            delete z; 
            //  Repeated  keys  not  allowed
            return;
        }
        son = (z->key < son ->key) ? son ->left : son ->right;
    }
    z->parent = father;
    if (father  == nil)
        root = z;
    else if (z->key < father ->key)
        father ->left = z;
    else  father ->right = z;
    z->left = z->right = nil;
    z->color = RED;
    // Fix  Red  Black  Tree  violations
    RBinsert_fixUp(z);
}

void  RBTree :: RBinsert_fixUp (Node *z) {
    while (z->parent ->color  == RED) {
        if (z->parent  == z->parent ->parent ->left) {
            Node *uncle = z->parent ->parent ->right;
            if (uncle ->color  == RED) {// Case 1a
                z->parent ->color = BLACK;// Case 1a
                uncle ->color = BLACK;// Case 1a
                z->parent ->parent ->color = RED;   // Case 1a
                z = z->parent ->parent;// Case 1a
            } 
            else {
                if (z == z->parent ->right) {// Case 2a
                    z = z->parent;// Case 2a
                    left_rotate(z);// Case 2a
                }
                z->parent ->color = BLACK;// Case 3a
                z->parent ->parent ->color = RED;   // Case 3a
                right_rotate(z->parent ->parent); // Case 3a
            }
        }
        else {
            Node *uncle = z->parent ->parent ->left;
            if(uncle ->color  == RED) {// Case 1a
                z->parent ->color = BLACK;// Case 1a
                uncle ->color = BLACK;// Case 1a
                z->parent ->parent ->color = RED;   // Case 1a
                z = z->parent ->parent;// Case 1a
            } 
            else {
                if (z == z->parent ->left) {// Case 2a
                    z = z->parent;// Case 2a
                    right_rotate(z);// Case 2a
                }
                z->parent ->color = BLACK;// Case 3a
                z->parent ->parent ->color = RED;   // Case 3a
                left_rotate(z->parent ->parent); // Case 3a
            }
        }
    }
    root ->color = BLACK; //  Guarantee  Property 2
}

void  RBTree :: remove(const  Tkey& key) {
    Node *p = root;
    while(p != nil && p->key != key) {
            p = (key < p->key) ? p->left : p->right;
    }
    if(p != nil) RBdelete(p);
}

//  Recebe  ponteiro  para no z e o remove  da  arvore
void  RBTree :: RBdelete(Node *z) {
    Node *y; //  aponta  no que  sera  removido
    Node *x; //  aponta  no que  tomara o lugar  de y
    if(z->left == nil || z->right  == nil) y = z;
    else y = minimum(z->right); // pega o sucessor  de z
    if(y->left != nil) x = y->left;
    else x = y->right;
    if(x != nil) x->parent = y->parent;
    if(y->parent  == nil) {
        root = x;
    } 
    else {
        if(y == y->parent ->left)
            y->parent ->left = x;
        else y->parent ->right = x;
    }
    if(y != z) z->key = y->key;
    if(y->color  == BLACK)
        RBdelete_fixUp(x); //  Conserta  possiveis  estragos
    delete y;
}

Node *RBTree :: minimum(Node *no) {
    while(no ->left != nil) {
        no = no->left;
    }
    return  no;
}

void  RBTree :: RBdelete_fixUp(Node *no) {
    while (no != root && no->color  ==  BLACK) {
        if (no == no->parent ->left) { // x is a left  child
            Node *w = no->parent ->right;
            if (w->color  == RED) {// Case 1
                w->color = BLACK;// Case 1
                no->parent ->color = RED;// Case 1
                left_rotate(no->parent);// Case 1
                w = no->parent ->right;// Case 1
            }
            if (w->left ->color  ==  BLACK  && w->right ->color  ==  BLACK) {    // Case 2
                w->color = RED;// Case 2
                x = x->parent;// Case 2
            }
            else {
                if (w->right ->color  ==  BLACK) { // Case 3
                    w->left ->color = BLACK;// Case 3
                    w->color = RED;// Case 3
                    right_rotate(w);// Case 3
                    w = x->parent ->right;// Case 3
                }
                w->color = x->parent ->color;// Case 4
                x->parent ->color = BLACK;// Case 4
                w->right ->color = BLACK;// Case 4
                left_rotate(x->parent);// Case 4
                x = root;
            }
        }
        else {
            Node *w = x->parent ->left;
            if (w->color  == RED) {// Case 1
                w->color = BLACK;// Case 1
                x->parent ->color = RED;// Case 1
                left_rotate(x->parent);// Case 1
                w = x->parent ->left;// Case 1
            }
            if (w->left ->color  ==  BLACK  && w->right ->color  ==  BLACK) {    // Case 2
                w->color = RED;// Case 2
                x = x->parent;// Case 2
            }
            else {
                if (w->left->color  ==  BLACK) { // Case 3
                    w->right->color = BLACK;// Case 3
                    w->color = RED;// Case 3
                    left_rotate(w);// Case 3
                    w = x->parent ->right;// Case 3
                }
                w->color = x->parent ->color;// Case 4
                x->parent ->color = BLACK;// Case 4
                w->right ->color = BLACK;// Case 4
                right_rotate(x->parent);// Case 4
                x = root;
            }
        }
    }
    x->color = BLACK;
}