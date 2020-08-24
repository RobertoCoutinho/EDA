#include <iostream>
#include<string>
#include "avl.h"

using std::cout;
using std::endl;
using std::cin;

//struct que vai ser os Nos da arvore
struct Node{
    Tkey chave;
    Tvalue valor;
    int alt;
    Node *esq;
    Node *dir;
};
//função apenas para definir a raiz como null
Node* criarVazia(){
    return nullptr;
}
//função que retorna o campo altura de um determinado No
int getAltura(Node* node){
    if(node == nullptr)
        //caso o No não exista retorna 0
        return 0;
    else{
        return node->alt;
    }
}
//função que retorna o balanço de um determinado No
int fatorBalanceamento(Node* node){
    if(node == nullptr){
        return 0;
    }
    //subtrai o no da direita pelo da esquerda para definir o balanço
    return getAltura(node->dir) - getAltura(node->esq);
}
//função que aloca um novo No para arvore
Node* alocar(Tkey chave, Tvalue valor){
    Node *node = new Node;//aloca espaço para o No
    node->chave = chave;
    node->valor = valor;
    node->alt = 1;//ao ser criado o No tem altura 1
    node->esq = nullptr;
    node->dir = nullptr;
    return node;
}
//funçao que retorna maior, usado na rotação
int maior(int x, int y){
    if(x > y){
        return x;
    }
    else{
        return y;
    }
}
//rotação a esquerda
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
//rotaçao a direita
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
//função que insere um novo No a arvore
Node* inserir(Node *no, Tkey chave, Tvalue valor){
    if(no == nullptr){
        //ao percorrer a arvore ate o local correto chama a funçaõ alocar para criar o novo no
        return alocar(chave, valor);
    }
    if(chave < no->chave){//se for menor vai oara esquerda
        no->esq = inserir(no->esq, chave, valor);
    }
    else if(chave > no->chave){//se for maior vai para a direita
        no->dir = inserir(no->dir, chave, valor);
    }
    else{//se for igua retorna sem inserir pois a arvore nao pode ter 2 chaves iguais, 2 valores sim mas não 2 chaves
        return no;
    }
    no->alt = 1 + maior(getAltura(no->esq), getAltura(no->dir));
    no = fixup_node(no, chave);
    return no;
}
//função que defini qual rotaçaõ vai ser usada dependendo do desbalanceamento
Node* fixup_node(Node* no, Tkey chave){
    int bal = fatorBalanceamento(no);//chama essa função auxiliar para calcular o balanço do No
    if(bal < -1 && chave < no->esq->chave){
        return rotacaoRR(no);
    }
    else if(bal > 1 && chave > no->dir->chave){
        return rotacaoLL(no);
    }
    else if(bal < -1 && chave > no->esq->chave){
        no->esq = rotacaoLL(no->esq);
        return rotacaoRR(no);
    }
    else if(bal > 1 && chave < no->dir->chave){
        no->dir = rotacaoRR(no->dir);
        return rotacaoLL(no);
    }
    return no; //caso não seja preciso rebalancear apenas retorna 
}
//imprimi arvore na preordem
void preOrdem(Node *raiz){
    if(raiz != nullptr){
        cout << endl;
        cout << "chave -> " << raiz->chave << " valor -> " << raiz->valor << endl;
        preOrdem(raiz->esq);
        preOrdem(raiz->dir);
    }
}
//imprimi arvore em ordem
void emOrdem(Node *raiz){
    if(raiz != nullptr){
        preOrdem(raiz->esq);
        cout << endl;
        cout << "chave -> " << raiz->chave << " valor -> " << raiz->valor << endl;
        preOrdem(raiz->dir);
    }
}
//imprime arvor na pos ordem
void posOrdem(Node *raiz){
    if(raiz != nullptr){
        preOrdem(raiz->esq);
        preOrdem(raiz->dir);
        cout << endl;
        cout << "chave -> " << raiz->chave << " valor -> " << raiz->valor << endl;
    }
}
//desaloca os espaços alocados para os Nos
Node* apagar(Node* raiz){
    if(raiz != nullptr){
        raiz->esq = apagar(raiz->esq);
        raiz->dir = apagar(raiz->dir);
        delete raiz;
    }
    return nullptr;
}

//imprimi o valor pesquisando pela chave
void pesquisar(Node* raiz, Tkey chave){
    if(raiz == nullptr){
        cout << endl;
        cout << "Chave nao encontrada" << endl;
    }
    else if(raiz->chave == chave){
        cout << endl;
        cout << "Valor -> " << raiz->valor << endl;
    }
    else if(chave < raiz->chave){
        pesquisar(raiz->esq, chave);
    }
    else{
        pesquisar(raiz->dir, chave);
    }
}
//função menu que permite usar o sistema
void menu(){
    int op = 0;//variavel
    Tkey chave;//criaçao de chave e valor que serão usados no menu
    Tvalue valor;
    Node* raiz = criarVazia(); //so para definir a raiz com nullptr
    do{
        cout << "---------------------------" << endl;
        cout << "IMPLEMENTAÇÃO DA ARVORE AVL" << endl;
        cout << "---------------------------" << endl;
        cout << "1 - Inserir No" << endl;
        cout << "2 - Apagar todos os Nos" << endl;
        cout << "3 - Imprimir(pre-ordem)" << endl;
        cout << "4 - Imprimir(em ordem)" << endl;
        cout << "5 - Imprimir(pos-ordem)" << endl;
        cout << "6 - Pesquisar chave" << endl;
        cout << "7 - Altura da arvore" << endl;
        cout << "8 - Sair" << endl;
        cin >> op;
        if(op == 1){
            cout << "insira a chave" << endl;
            cin >> chave;
            cout << "insira o valor" << endl;
            cin >> valor;
            raiz = inserir(raiz, chave, valor);
        }
        else if(op == 2){
            raiz = apagar(raiz);
        }
        else if(op == 3){
            preOrdem(raiz);
        }
        else if(op == 4){
            emOrdem(raiz);
        }
        else if(op == 5){
            posOrdem(raiz);
        }
        else if(op == 6){
            cout << endl << "Digite a chave a ser buscada" << endl;
            cin >> chave;
            pesquisar(raiz, chave);
        }
        else if(op == 7){
            //ja que a altura da arvore é a altura da raiz então basta usar a função getAltura na raiz
            cout << endl << "altura ->" << getAltura(raiz) << endl;
        }
        
        
    }while(op!=8);
}