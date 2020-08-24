#include <iostream>
#include "arvore.h"
#include "arvore.cpp"
int main(){
    Node* a1 = criar(34, nullptr, nullptr);
    Node* a2 = criar(21, nullptr, nullptr);
    Node* a3 = criar(76, a1, a2);
    Node* a4 = criar(55, nullptr, nullptr);
    Node* raiz = criar(1, a3, a4);

    //imprimir(raiz);
    int a = tamanho(raiz);
    std::cout << a; 

    return 0;
}