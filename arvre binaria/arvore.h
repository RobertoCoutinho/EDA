#ifndef ARVOREBIN_H
#define ARVOREBIN_H

struct Node;

Node* criar_vazia(); //verifica se arvore é vazia, retornando nullcaso seja

Node* criar(int chave, Node* no_esq, Node* no_dir); //cria um no

bool vazia(Node* node);//árvoreenraizadaemnóestávazia?

void imprimir(Node* node);//imprimir chave

bool buscar(Node* node, int chave); //verifica se a chave existe na arvore

Node* desalocar(Node* node); //desaloca todos os espaços alocados para arvore

int bt_size(Node* node);

int tamanho(Node* node);
#endif