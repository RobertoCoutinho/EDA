#ifndef RBTREE_H
#define RBTREE_H
#include <iostream>
#include <bits/stdc++.h>
#include "node.h"
using namespace std;
//template usado na classe RBTree
template <typename Tkey, typename Tvalue>
class RBTree
{
private:
    Node<Tkey, Tvalue> *root;
    Node<Tkey, Tvalue> *nil;

protected:
    //função que realiza a rotaação para a esquerda
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

    //função que realiza a rotação a direita
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
                delete z;
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
        RBinsert_fixUp(z);
    }

    //Função que verifica qual rotação realizar, dependendo do balanceamento
    void RBinsert_fixUp(Node<Tkey, Tvalue> *z)
    {
        while (z->parent->color == RED)
        {
            if (z->parent == z->parent->parent->left)
            {
                Node<Tkey, Tvalue> *uncle = z->parent->parent->right;
                if (uncle->color == RED)
                {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->right)
                    {
                        z = z->parent;
                        left_rotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    right_rotate(z->parent->parent);
                }
            }
            else
            {
                Node<Tkey, Tvalue> *uncle = z->parent->parent->left;
                if (uncle->color == RED)
                {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->left)
                    {
                        z = z->parent;
                        right_rotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    left_rotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK; //  Guarantee  Property 2
    }

    //deleta um no
    void RBdelete(Node<Tkey, Tvalue> *z)
    {
        Node<Tkey, Tvalue> *y;
        Node<Tkey, Tvalue> *x;
        if (z->left == nil || z->right == nil)
            y = z;
        else
            y = minimum(z->right);
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
            RBdelete_fixUp(x);
        delete y;
    }

    //retorna o no mais a esquerda possivel, ou seja o de menor valor
    Node<Tkey, Tvalue> *minimum(Node<Tkey, Tvalue> *no)
    {
        while (no->left != nil)
        {
            no = no->left;
        }
        return no;
    }
    //conserta o balanceamento apos remoção
    void RBdelete_fixUp(Node<Tkey, Tvalue> *no)
    {
        while (no != root && no->color == BLACK)
        {
            if (no == no->parent->left)
            {
                Node<Tkey, Tvalue> *w = no->parent->right;
                if (w->color == RED)
                {
                    w->color = BLACK;
                    no->parent->color = RED;
                    left_rotate(no->parent);
                    w = no->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK)
                {
                    w->color = RED;
                    no = no->parent;
                }
                else
                {
                    if (w->right->color == BLACK)
                    {
                        w->left->color = BLACK;
                        w->color = RED;
                        right_rotate(w);
                        w = no->parent->right;
                    }
                    w->color = no->parent->color;
                    no->parent->color = BLACK;
                    w->right->color = BLACK;
                    left_rotate(no->parent);
                    no = root;
                }
            }
            else
            {
                Node<Tkey, Tvalue> *w = no->parent->left;
                if (w->color == RED)
                {
                    w->color = BLACK;
                    no->parent->color = RED;
                    left_rotate(no->parent);
                    w = no->parent->left;
                }
                if (w->left->color == BLACK && w->right->color == BLACK)
                {
                    w->color = RED;
                    no = no->parent;
                }
                else
                {
                    if (w->left->color == BLACK)
                    {
                        w->right->color = BLACK;
                        w->color = RED;
                        left_rotate(w);
                        w = no->parent->right;
                    }
                    w->color = no->parent->color;
                    no->parent->color = BLACK;
                    w->right->color = BLACK;
                    right_rotate(no->parent);
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
    //cria um novo no com seus valores
    void insert(const Tkey &key, const Tvalue &v)
    {
        Node<Tkey, Tvalue> *newNode = new Node<Tkey, Tvalue>{};
        newNode->key = key;
        newNode->value = v;
        newNode->left = newNode->right = nil;
        newNode->parent = nil;
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

    //pesquisa um no pela chave, e o retorna
    //caso não exista retorna o ponteiro null
    Node<Tkey, Tvalue> *search(const Tkey &key)
    {
        Node<Tkey, Tvalue> *raiz = root;
        while (raiz != nil && raiz->key != key)
        {
            raiz = (key < raiz->key) ? raiz->left : raiz->right;
        }
        if (raiz != nil)
            return raiz;
        return nullptr;
    }

    //recebe um no e retorna o valor dele
    Tvalue getValue(Node<Tkey, Tvalue> *no)
    {
        return no->value;
    }
    //imprimi no percurso pre ordem
    void preorder() const
    {
        Node<Tkey, Tvalue> *raiz = root;
        stack<Node<Tkey, Tvalue> *> p;
        if (raiz != nil)
        {
            p.push(raiz);
            while (!p.empty())
            {
                raiz = p.top();
                p.pop();
                if (raiz->color == BLACK)
                    cout << raiz->key << "  " << raiz->value << "  Preto" << endl;
                else
                    cout << raiz->key << "  " << raiz->value << " Vermelho" << endl;
                if (raiz->right != nil)
                    p.push(raiz->right);
                if (raiz->left != nil)
                    p.push(raiz->left);
            }
        }
    }
    //deleta os nos
    void clear(Node<Tkey, Tvalue> *root)
    {
        Node<Tkey, Tvalue> *aux = root;
        stack<Node<Tkey, Tvalue> *> p;

        if (aux != nil)
            p.push(aux);
        while (!p.empty())
        {
            Node<Tkey, Tvalue> *node = p.top();
            if (node->left != nil)
                p.push(node->left);
            if (node->right != nil)
                p.push(node->right);
            if (node->left == nil && node->right == nil)
                RBdelete(node);
            p.pop();
        }
    }
    //retorna a altura da arvore
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