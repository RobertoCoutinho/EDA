typedef struct  NO* ArvAVL;
ArvAVL* cria_ArvAVL();
int alt_NO(struct NO* no);
int fatorBalanceamento(struct NO* no);
int maior(int x, int y);
void rotacaoLL(ArvAVL *raiz);
void rotacaoRR(ArvAVL *raiz);
void rotacaoLR(ArvAVL *raiz);
void rotacaoRL(ArvAVL *raiz);
int insere_ArvAVL(ArvAVL *raiz, int valor);
void preOrdem(ArvAVL *raiz);