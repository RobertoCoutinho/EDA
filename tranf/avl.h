#include "item.h"
#ifndef AVL_H
#define AVL_H
struct  Node;
Node* criarVazia();
int getAltura(Node* node);
int fatorBalanceamento(Node* no);
int maior(int x, int y);
Node* rotacaoLL(Node *node);
Node* rotacaoRR(Node *node);
Node* inserir(Node *no, Tkey chave, Tvalue valor);
void preOrdem(Node *raiz);
Node* fixup_node(Node* no, Tkey chave);
Node* alocar(Tkey chave, Tvalue value);
Node* apagar(Node* raiz);
void emOrdem(Node *raiz);
void posOrdem(Node *raiz);
void pesquisar(Node* raiz, Tkey chave);
void menu();
#endif