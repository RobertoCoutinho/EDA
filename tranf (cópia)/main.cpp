#include <iostream>
#include "avl.h"
#include "avl.cpp"
using std::cout;
using std::cin;
using std::endl;
int main(){
    int op = 0;
    Node* raiz = criarVazia();
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
        switch (op){
        case 1:
            int valor;
            cout << "insira o valor";
            cin >> valor;
            raiz = inserir(raiz, valor);
            break;
        case 3:
            preOrdem(raiz);
        }
    }while(op!=8);
    
    
    raiz = inserir(raiz, 1);
    raiz = inserir(raiz, 2);
    raiz = inserir(raiz, 3);
    raiz = inserir(raiz, 4);
    raiz = inserir(raiz, 5);
    raiz = inserir(raiz, 6);
    raiz = inserir(raiz, 7);
    raiz = inserir(raiz, 8);
    preOrdem(raiz);
    return 0;
}
