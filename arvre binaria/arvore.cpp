#include <iostream>
#include "arvore.h"
using std::cout;
using std::endl;
using namespace std;

struct Node{
    int chave;
    Node* no_esq;
    Node* no_dir;
};

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

bool buscar(Node* node, int chave){
    if(vazia(node)){
        return false;
    }
    else{
        if(node->chave == chave || buscar(node->no_esq, chave) || buscar(node->no_dir, chave)){
            return true;
        }
        return false;
    }
}

Node* desalocar(Node* node){
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
        return 1+tamanho(node->no_esq)+tamanho(node->no_dir);
    }
}
