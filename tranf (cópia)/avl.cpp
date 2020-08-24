#include <iostream>
#include "avl.h"
using std::cout;
using std::endl;

struct Node{
    int info;
    int alt;
    Node *esq;
    Node *dir;
};

Node* criarVazia(){
    return nullptr;
}

int getAltura(Node* node){
    if(node == nullptr)
        return 0;
    else{
        return node->alt;
    }
}
int fatorBalanceamento(Node* node){
    if(node == nullptr){
        return 0;
    }
    return getAltura(node->dir) - getAltura(node->esq);
}

Node* alocar(int info){
    Node *node = new Node;
    node->info = info;
    node->alt = 1;
    node->esq = nullptr;
    node->dir = nullptr;
    return node;
}

int maior(int x, int y){
    if(x > y){
        return x;
    }
    else{
        return y;
    }
}
Node* rotacaoLL(Node *node){
    Node *u = node->dir;
    node->dir = u->esq;
    u->esq = node;
    node->alt = 1 + maior(getAltura(node->esq),
                        getAltura(node->dir));
    u->alt = 1 + maior(getAltura(u->esq),
                        getAltura(u->dir));
    return u;
}
Node* rotacaoRR(Node *node){
    Node *u = node->esq;
    node->esq = u->dir;
    u->dir = node;
    node->alt = 1 + maior(getAltura(node->esq),
                        getAltura(node->dir));
    u->alt = 1 + maior(getAltura(u->esq),
                        getAltura(u->dir));
    return u;
}
void rotacaoLR(Node *raiz){
    rotacaoRR(raiz->esq);
    rotacaoLL(raiz);
}
void rotacaoRL(Node *raiz){
    rotacaoLL(raiz->dir);
    rotacaoRR(raiz);
}

Node* inserir(Node *no, int valor){
    if(no == nullptr){
        return alocar(valor);
    }
    if(valor < no->info){
        no->esq = inserir(no->esq, valor);
    }
    else if(valor > no->info){
        no->dir = inserir(no->dir, valor);
    }
    else{
        return no;
    }
    no->alt = 1 + maior(getAltura(no->esq), getAltura(no->dir));
    no = fixup_node(no, valor);
    return no;
}
Node* fixup_node(Node* no, int valor){
    int bal = fatorBalanceamento(no);
    if(bal < -1 && valor < no->esq->info){
        return rotacaoRR(no);
    }
    else if(bal < -1 && valor > no->esq->info){
        no->esq = rotacaoLL(no->esq);
        return rotacaoRR(no);
    }
    else if(bal > 1 && valor > no->dir->info){
        return rotacaoLL(no);
    }
    else if(bal > 1 && valor < no->dir->info){
        no->dir = rotacaoRR(no->dir);
        return rotacaoLL(no);
    }
    return no;
}

void preOrdem(Node *raiz){
    if(raiz == nullptr){
        return;
    }
    else{
        cout << raiz->info;
        preOrdem(raiz->esq);
        preOrdem(raiz->dir);
    }
}