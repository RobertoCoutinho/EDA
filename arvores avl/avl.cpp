#include <iostream>
#include "item.h"
#include "avl.h"
using std::cout;
using std::endl;

struct Node{
    Tkey key;
    Tvalue value;
    int height;
    Node* esq;
    Node* dir;
}

Tkey avl_getKey(Node* node){
    Tkey key;
    key = node->key;
    return key;
}

Tvalue avl_getValue(Node* node){
    Tvalue value;
    value = node->value;
    return value;
}

Node* criar_vazia(){
    return nullptr;
}

Node* criar(int chave, Node* no_esq, Node* no_dir){
    Node* novo_no = new Node{};
    novo_no->chave = chave;
    novo_no->no_esq = no_esq;
    novo_no->no_dir = no_dir;
    return novo_no;
}

bool vazia(Node* node){
    if(node == nullptr){
        return true;
    }
    return false;
}

void imprimir(Node *node){
    if(!vazia(node)){
        cout << node->chave << endl;
        imprimir(node->no_esq);
        imprimir(node->no_dir);
    }
}

Node* buscar(Node* node, int chave){
    if(node == nullptr){
        return nullptr;
    }
    if(key < node->key){
        return buscar(node->esq, key);
    }
    else if(key > node->key, key){
        return buscar(node->dir, key);
    }
    else{
        return node;
    }

Node* desalocar(Node* node){ //deixa
    if(node != nullptr){
        node->no_esq = desalocar(node->no_esq);
        node->no_dir = desalocar(node->no_dir);
        cout <<"Deleting"<< node->chave << endl;
        delete node;
    }
    return nullptr;
}

int tamanho(Node* node){
    if(node == nullptr){
        return 0;
    }
    else{
        return 1+tamanho(node->esq)+tamanho(node->dir);
    }
}

int getAltura(Node* node){
    if(node == nullptr){
        return -1;
    }
    else{
        return node->height;
    }

}

int fatorBalanceamento(Node* node){
    return labs(getAltura(node->esq) - getAltura(node->dir));
}

int comparaMaior(int x, Nnt y){
    if(x > y){
        return x;
    }
    return y;
}
void rotacaoLL(Node* node){
    Node* aux;
    aux = (*node)->esq;
    (*node)->esq = aux->dir;
    aux->dir = *node;
    (*node)->height = comparaMaior(getAltura((*node)->esq), getAltura((*node)->dir)) + 1;

    aux->height = comparaMaior(getAltura(aux->esq), (*node)->height) + 1;
    *node = aux;
}

void rotacaoRR(Node* node){
    Node* aux;
    aux = (*node)->dir;
    (*node)->dir = aux->esq;
    aux->esq = *node;
    (*node)->height = comparaMaior(getAltura((*node)->esq), getAltura((*node)->dir)) + 1;

    aux->height = comparaMaior(getAltura(aux->dir), (*node)->height) + 1;
    (*node) = aux;
}

void rotacaoLR(Node* node){
    rotacaoRR(&(*node)->esq);
    rotacaoLL(node);
}

void rotacaoLR(Node* node){
    rotacaoLL(&(*node)->dir);
    rotacaoRR(node);
}

int iserir(Node* node, int valor){
    int res;
    if(node == nullptr){
        
    }
}