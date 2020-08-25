#ifndef RBTREE_H
#define RBTREE_H
#include <iostream>
#include <bits/stdc++.h>
#include "node.h"
using namespace std;

template <typename Tkey, typename Tvalue>
class RBTree
{
private:
    Node<Tkey, Tvalue> *root;
    Node<Tkey, Tvalue> *nil;

protected:
    void left_rotate(Node<Tkey, Tvalue> *x)
    {
        Node<Tkey, Tvalue> *y = x->right;
        x->right = y->left;
        if (y->left != nil)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nil)
        {
            root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;
    }

    void right_rotate(Node<Tkey, Tvalue> *x)
    {
        Node<Tkey, Tvalue> *y = x->left;
        x->left = y->right;
        if (y->right != nil)
        {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nil)
        {
            root = y;
        }
        else if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        else
        {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void RBinsert(Node<Tkey, Tvalue> *z)
    {
        Node<Tkey, Tvalue> *father = nil;
        Node<Tkey, Tvalue> *son = root;
        while (son != nil)
        {
            father = son;
            if (z->key == son->key)
            {
                //  Diferent  from  Cormen
                delete z;
                //  Repeated  keys  not  allowed
                return;
            }
            son = (z->key < son->key) ? son->left : son->right;
        }
        z->parent = father;
        if (father == nil)
            root = z;
        else if (z->key < father->key)
            father->left = z;
        else
            father->right = z;
        z->left = z->right = nil;
        z->color = RED;
        // Fix  Red  Black  Tree  violations
        RBinsert_fixUp(z);
    }

    void RBinsert_fixUp(Node<Tkey, Tvalue> *z)
    {
        while (z->parent->color == RED)
        {
            if (z->parent == z->parent->parent->left)
            {
                Node<Tkey, Tvalue> *uncle = z->parent->parent->right;
                if (uncle->color == RED)
                {                                   // Case 1a
                    z->parent->color = BLACK;       // Case 1a
                    uncle->color = BLACK;           // Case 1a
                    z->parent->parent->color = RED; // Case 1a
                    z = z->parent->parent;          // Case 1a
                }
                else
                {
                    if (z == z->parent->right)
                    {                   // Case 2a
                        z = z->parent;  // Case 2a
                        left_rotate(z); // Case 2a
                    }
                    z->parent->color = BLACK;        // Case 3a
                    z->parent->parent->color = RED;  // Case 3a
                    right_rotate(z->parent->parent); // Case 3a
                }
            }
            else
            {
                Node<Tkey, Tvalue> *uncle = z->parent->parent->left;
                if (uncle->color == RED)
                {                                   // Case 1a
                    z->parent->color = BLACK;       // Case 1a
                    uncle->color = BLACK;           // Case 1a
                    z->parent->parent->color = RED; // Case 1a
                    z = z->parent->parent;          // Case 1a
                }
                else
                {
                    if (z == z->parent->left)
                    {                    // Case 2a
                        z = z->parent;   // Case 2a
                        right_rotate(z); // Case 2a
                    }
                    z->parent->color = BLACK;       // Case 3a
                    z->parent->parent->color = RED; // Case 3a
                    left_rotate(z->parent->parent); // Case 3a
                }
            }
        }
        root->color = BLACK; //  Guarantee  Property 2
    }

    void RBdelete(Node<Tkey, Tvalue> *z)
    {
        Node<Tkey, Tvalue> *y; //  aponta  no que  sera  removido
        Node<Tkey, Tvalue> *x; //  aponta  no que  tomara o lugar  de y
        if (z->left == nil || z->right == nil)
            y = z;
        else
            y = minimum(z->right); // pega o sucessor  de z
        if (y->left != nil)
            x = y->left;
        else
            x = y->right;
        if (x != nil)
            x->parent = y->parent;
        if (y->parent == nil)
        {
            root = x;
        }
        else
        {
            if (y == y->parent->left)
                y->parent->left = x;
            else
                y->parent->right = x;
        }
        if (y != z)
            z->key = y->key;
        if (y->color == BLACK)
            RBdelete_fixUp(x); //  Conserta  possiveis  estragos
        delete y;
    }

    Node<Tkey, Tvalue> *minimum(Node<Tkey, Tvalue> *no)
    {
        while (no->left != nil)
        {
            no = no->left;
        }
        return no;
    }

    void RBdelete_fixUp(Node<Tkey, Tvalue> *no)
    {
        while (no != root && no->color == BLACK)
        {
            if (no == no->parent->left)
            { // x is a left  child
                Node<Tkey, Tvalue> *w = no->parent->right;
                if (w->color == RED)
                {                            // Case 1
                    w->color = BLACK;        // Case 1
                    no->parent->color = RED; // Case 1
                    left_rotate(no->parent); // Case 1
                    w = no->parent->right;   // Case 1
                }
                if (w->left->color == BLACK && w->right->color == BLACK)
                {                    // Case 2
                    w->color = RED;  // Case 2
                    no = no->parent; // Case 2
                }
                else
                {
                    if (w->right->color == BLACK)
                    {                           // Case 3
                        w->left->color = BLACK; // Case 3
                        w->color = RED;         // Case 3
                        right_rotate(w);        // Case 3
                        w = no->parent->right;  // Case 3
                    }
                    w->color = no->parent->color; // Case 4
                    no->parent->color = BLACK;    // Case 4
                    w->right->color = BLACK;      // Case 4
                    left_rotate(no->parent);      // Case 4
                    no = root;
                }
            }
            else
            {
                Node<Tkey, Tvalue> *w = no->parent->left;
                if (w->color == RED)
                {                            // Case 1
                    w->color = BLACK;        // Case 1
                    no->parent->color = RED; // Case 1
                    left_rotate(no->parent); // Case 1
                    w = no->parent->left;    // Case 1
                }
                if (w->left->color == BLACK && w->right->color == BLACK)
                {                    // Case 2
                    w->color = RED;  // Case 2
                    no = no->parent; // Case 2
                }
                else
                {
                    if (w->left->color == BLACK)
                    {                            // Case 3
                        w->right->color = BLACK; // Case 3
                        w->color = RED;          // Case 3
                        left_rotate(w);          // Case 3
                        w = no->parent->right;   // Case 3
                    }
                    w->color = no->parent->color; // Case 4
                    no->parent->color = BLACK;    // Case 4
                    w->right->color = BLACK;      // Case 4
                    right_rotate(no->parent);     // Case 4
                    no = root;
                }
            }
        }
        no->color = BLACK;
    }

    bool empty()

    {
        if (root->left == nil && root->right == nil)
        {
            return true;
        }
        return false;
    }

public:
    RBTree()
    {
        nil = new Node<Tkey, Tvalue>{};
        nil->key = 0;
        nil->left = nil->right = nil->parent = nil;
        nil->color = BLACK;
        root = nil;
    }

    Node<Tkey, Tvalue> *getRoot()
    {
        return root;
    }

    void insert(const Tkey &key, const Tvalue &v)
    {
        //  Allocate a new  Node<Tkey, Tvalue>
        Node<Tkey, Tvalue> *newNode = new Node<Tkey, Tvalue>{};
        newNode->key = key;
        newNode->value = v;
        newNode->left = newNode->right = nil;
        newNode->parent = nil;
        // Do a normal  BST  insert
        RBinsert(newNode);
    }
    void remove(const Tkey &key)
    {
        Node<Tkey, Tvalue> *p = root;
        while (p != nil && p->key != key)
        {
            p = (key < p->key) ? p->left : p->right;
        }
        if (p != nil)
            RBdelete(p);
    }

    Node<Tkey, Tvalue> *search(const Tkey &key)
    {
        Node<Tkey, Tvalue> *p = root;
        while (p != nil && p->key != key)
        {
            p = (key < p->key) ? p->left : p->right;
        }
        if (p != nil)
            return p;
        return nullptr;
    }

    Tvalue getValue(Node<Tkey, Tvalue> *no)
    {
        return no->value;
    }

    void preorder() const
    {
        Node<Tkey, Tvalue> *tree = root;
        stack<Node<Tkey, Tvalue> *> pilha;
        if (tree != nil)
        {
            pilha.push(tree);
            while (!pilha.empty())
            {
                tree = pilha.top();
                pilha.pop();
                if (tree->color == BLACK)
                {
                    cout << "(" << tree->key << "," << tree->value << ") -> Black" << endl;
                }
                else
                {
                    cout << "(" << tree->key << "," << tree->value << ") -> Red" << endl;
                }
                if (tree->right != nil)
                {
                    pilha.push(tree->right);
                }
                if (tree->left != nil)
                {
                    pilha.push(tree->left);
                }
            }
        }
    }

    void clear(Node<Tkey, Tvalue> *root)
    {
        Node<Tkey, Tvalue> *aux = root;
        stack<Node<Tkey, Tvalue> *> nodes;

        if (aux != nil)
        {
            nodes.push(aux);
        }
        while (!nodes.empty())
        {
            Node<Tkey, Tvalue> *node = nodes.top();
            if (node->right != nil)
            {
                nodes.push(node->right);
            }
            if (node->left != nil)
            {
                nodes.push(node->left);
            }
            if (node->left == nil && node->right == nil)
            {
                RBdelete(node);
                nodes.pop();
            }
        }
    }

    int height(Node<Tkey, Tvalue> *node)
    {
        if (node != nil)
        {
            int l, r;
            l = height(node->left);
            r = height(node->right);
            if (l > r)
                return 1 + l;
            else
                return 1 + r;
        }
        else
            return 0;
    }
    ~RBTree()
    {
        //clear(root); // Para  casa: Codifiquem  esta  funcao
        delete nil;
        nil = nullptr;
        root = nullptr;
    }
};
#endif