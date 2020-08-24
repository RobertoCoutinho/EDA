#include<stdio.h>
#include<stdlib.h>
#include "avl.h"
#include "avl.c"
int main(){
    ArvAVL* raiz = cria_ArvAVL();
    int a = insere_ArvAVL(raiz, 1);
    a = insere_ArvAVL(raiz, 2);
    a = insere_ArvAVL(raiz, 3);
    a = insere_ArvAVL(raiz, 4);
    a = insere_ArvAVL(raiz, 5);
    a = insere_ArvAVL(raiz, 6);
    a = insere_ArvAVL(raiz, 7);
    a = insere_ArvAVL(raiz, 8);
    preOrdem(raiz);
    return 0;
}
