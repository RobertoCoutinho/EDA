#include<iostream>
#include"rbtree.cpp"
int main(){
    RBTree tree = RBTree();

    tree.insert(1, "a");
    tree.insert(2, "b");
    tree.insert(3, "c");
    tree.insert(4, "d");
    tree.insert(5, "e");
    tree.preorder();
    std::cout << "-----------------------------------" << std::endl;
    tree.~RBTree();


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





    return 0;
}