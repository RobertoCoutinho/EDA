#include <bits/stdc++.h>
#include "rbtree.h"

using namespace std;

RBTree::RBTree () {
    nil = new Node{};
    nil->key = 0;
    nil->left = nil->right = nil->parent = nil;
    nil->color = BLACK;
    root = nil;
}

RBTree::~RBTree() {
    clear(root);
    delete nil;
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

void RBTree::clear (Node* node){
    stack<Node*> nodes;
    if(!nodes.empty()){
        nodes.push(node);
    }
    while (!nodes.empty()){
        Node* aux = nodes.top();
        if(aux->right != nil){
            nodes.push(aux->right);
        }
        if(aux->left != nil){
            nodes.push(aux->left);
        }
        if(aux->right == nil && aux->left == nil){
            RBdelete(nodes.top());

        }
    }
}

void RBTree::left_rotate(Node* node){
    Node* aux = node->right; 
    node->right = aux->left;

    if(aux->left != nil){
        aux->left->parent = node;
    }
    aux->parent = node->parent;
    if(node->parent == nil){
        root = aux;
    }else if(node == node->parent->left){
        node->parent->left = aux;
    }else{
        node->parent->right = aux;
    }

    aux->left = node;
    node->parent = aux;
}

void RBTree::right_rotate(Node* node){
    Node* aux = node->left;
    node->left = aux->right;

    if(aux->right != nil){
        aux->right->parent = node;
    }
    aux->parent = node->parent;
    if(node->parent == nil){
        root = aux;
    }else if(node == node->parent->right){
        node->parent->right = aux;
    }else{
        node->parent->left = aux;
    }

    aux->right = node;
    node->parent = aux;
}

void RBTree::insert(const Tkey &key, const Tvalue &v){
    Node* novo = new Node{};
    novo->key = key;
    novo->value = v;
    novo->left = novo->right = nil;
    novo->parent = nil;

    RBinsert(novo);
}

void RBTree::RBinsert(Node* node){
    Node* father = nil;
    Node* son = root;

    while(son != nil){
        father = son;

        if(node->key == son->key){
            delete node;
            return;
        }
        if(node->key < son->key){
            son = son->left;
        }else{
            son = son->right;
        }
    }
    node->parent = father;
    if(father == nil){
        root = node;
    }else if(node->key < father->key){
        father->left = node;
    }else{
        father->right = node;
    }
    node->left = node->right = nil;
    node->color = RED;

    RBinsert_fixUp(node);
}

void RBTree::remove(const Tkey &key){
    Node* aux = root;
    
    while(aux != nil && aux->key != key){
        if(aux->key > key){
            aux = aux->left;
        }else{
            aux = aux->right;
        }
    }

    if(aux != nil){
        RBdelete(aux);
    }
}

void RBTree::RBdelete(Node* z){
    Node* y; // No que será removido
    Node* x; // No que vai tomar seu lugar

    if(z->left == nil || z->right == nil) y = z;
    else y = minimum(z->right);
    if(y->left != nil) x = y->left;
    else x = y->right;

    x->parent = y->parent;

    if(y->parent == nil){
        root = x;
    }else{
        if(y == y->parent->left) y->parent->left = x;
        else y->parent->right = x;
    }
    if(y != z){
        z->key = y->key;
        z->value = y->value;
    }
    if(y->color == BLACK){
        RBdelete_fixUp(x);
    }
    delete y;
}

Node* RBTree::minimum(Node* node){
    while (node->left != nil){
        node = node->left;
    }
    return node;
}

void RBTree::RBinsert_fixUp(Node* z){
    while (z->parent->color == RED){
        if(z->parent == z->parent->parent->left){
            Node* uncle = z->parent->parent->right;
            if(uncle->color == RED){
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }else{
                if(z == z->parent->right){
                    z = z->parent;
                    left_rotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(z->parent->parent);
            }
        }else{
            Node* uncle = z->parent->parent->left;
            if(uncle->color == RED){
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }else{
                if(z == z->parent->left){
                    z = z->parent;
                    right_rotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(z->parent->parent);
            }
        }
    }

    root->color = BLACK;
}

void RBTree::RBdelete_fixUp(Node* x){
    while(x != root && x->color == BLACK){
        if(x == x->parent->left){
            Node* w = x->parent->right;
            if(w->color == RED){
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(x->parent);
                w = x->parent->right; 
            }
            if(w->left->color == BLACK && w->right->color == BLACK){
                w->color = RED;
                x = x->parent;
            }else{
                if(w->right->color == BLACK){
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                left_rotate(x->parent);
                x = root;
            }
        }else{
            Node* w = x->parent->left;
            if(w->color == RED){
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(x->parent);
                w = x->parent->left;
            }
            if(w->left->color == BLACK && w->right->color == BLACK){
                w->color = RED;
                x = x->parent;
            }else{
                if(w->left->color == BLACK){
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                right_rotate(x->parent);
                x = root;
            }
        }
    }

    x->color = BLACK;
}