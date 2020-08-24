#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
struct NO{
    int info;
    int alt;
    struct NO *esq;
    struct NO *dir;
};
ArvAVL* cria_ArvAVL(){
    ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}
int alt_NO(struct NO* no){
    if(no==NULL)
        return -1;
    else{
        return no->alt;
    }
}
int fatorBalanceamento(struct NO* no){
    return labs(alt_NO(no->esq) - alt_NO(no->dir));
}
int maior(int x, int y){
    if(x > y){
        return x;
    }
    else{
        return y;
    }
}
void rotacaoLL(ArvAVL *raiz){
    struct NO *no;
    no = (*raiz)->esq;
    (*raiz)->alt = maior(alt_NO((*raiz)->esq),
                            alt_NO((*raiz)->dir))
                            +1;
    no->alt = maior(alt_NO(no->esq),
                        (*raiz)->alt) + 1;
    *raiz = no;
}
void rotacaoRR(ArvAVL *raiz){
    struct NO *no;
    no = (*raiz)->dir;
    (*raiz)->dir = no->esq;
    no->esq = (*raiz);
    (*raiz)->alt = maior(alt_NO((*raiz)->esq),
                            alt_NO((*raiz)->dir)) 
                            + 1;
    no->alt = maior(alt_NO(no->dir),
                        (*raiz)->alt) + 1;
    (*raiz) = no;
}
void rotacaoLR(ArvAVL *raiz){
    rotacaoRR(&(*raiz)->esq);
    rotacaoLL(raiz);
}
void rotacaoRL(ArvAVL *raiz){
    rotacaoLL(&(*raiz)->dir);
    rotacaoRR(raiz);
}

int insere_ArvAVL(ArvAVL *raiz, int valor){
    int res;
    if(*raiz == NULL){
        struct NO *novo;
        novo = (struct NO*)malloc(sizeof(struct NO));
        if(novo == NULL)
            return 0;
        novo->info = valor;
        novo->alt = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }
    struct NO *atual = *raiz;
    if(valor < atual->info){
        if((res=insere_ArvAVL(&(atual->esq), valor)) ==1){
            if(fatorBalanceamento(atual) >= 2){
                if(valor < (*raiz)->esq->info){
                    rotacaoLL(raiz);
                }
                else{
                    rotacaoLR(raiz);
                }
            }
        }
    }
    else{
        if(valor > atual->info){
            if((res = insere_ArvAVL(&(atual->dir), valor))==1){
                if(fatorBalanceamento(atual) >= 2){
                    if((*raiz)->dir->info < valor){
                        rotacaoRR(raiz);
                    }
                    else{
                        rotacaoRL(raiz);
                    }
                }
            }
        }
        else{
            printf("Valor duplicado\n");
            return 0;
        }
    }
    atual->alt= maior(alt_NO(atual->esq),
                        alt_NO(atual->dir)) + 1;
    return res;
}
void preOrdem(ArvAVL *raiz){
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        printf("%d\n", (*raiz)->info);
        preOrdem(&((*raiz)->esq));
        preOrdem(&((*raiz)->dir));
    }
}










int inserir(Node *raiz, int valor){
    
    int res;
    if(raiz == nullptr){
       // cout << "entrou";
        Node *novo = new Node{};
        novo->info = valor;
        novo->alt = 0;
        novo->esq = nullptr;
        novo->dir = nullptr;
        raiz = novo;
        cout << raiz->info;
        return 1;
    }
    Node *atual = raiz;
    if(valor < atual->info){
        if((res=inserir(atual->esq, valor)) == 1){
            if(fatorBalanceamento(atual) >= 2){
                if(valor < raiz->esq->info){
                    rotacaoLL(raiz);
                }
                else{
                    rotacaoLR(raiz);
                }
            }
        }
    }
    else{
        if(valor > atual->info){
            if((res = inserir(atual->dir, valor))==1){
                if(fatorBalanceamento(atual) >= 2){
                    if(raiz->dir->info < valor){
                        rotacaoRR(raiz);
                    }
                    else{
                        rotacaoRL(raiz);
                    }
                }
            }
        }
        else{
            cout << "Valor duplicado";
            return 0;
        }
    }
    atual->alt= maior(getAltura(atual->esq),
                        getAltura(atual->dir)) + 1;
    return res;
}