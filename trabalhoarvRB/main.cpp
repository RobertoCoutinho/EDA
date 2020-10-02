#include <iostream>
#include "rbtree.h"
int main()
{
    //não consegui fazer para receber qualquer tipo do usuario,
    //mas se mudarmos o tipo aqui na main da certo, ja que
    //foi usado o Tamplete nas classe Node e rbtree

    RBTree<int, char> tree = RBTree<int, char>();
    int op = 0; //variavel
    do
    {
        cout << "---------------------------" << endl;
        cout << "IMPLEMENTAÇÃO DA ARVORE AVL" << endl;
        cout << "---------------------------" << endl;
        cout << "1 - Inserir No" << endl;
        cout << "2 - Apagar todos os Nos" << endl;
        cout << "3 - Imprimir(pre-ordem)" << endl;
        cout << "4 - Pesquisar chave" << endl;
        cout << "5 - Altura da arvore" << endl;
        cout << "6 - Apagar um no" << endl;
        cout << "7 - Sair" << endl;
        cin >> op;
        if (op == 1)
        {
            int chave;
            char valor;
            cin >> chave;
            cin >> valor;
            tree.insert(chave, valor);
        }
        else if (op == 2)
        {
            tree.clear(tree.getRoot());
        }
        else if (op == 3)
        {
            tree.preorder();
        }
        else if (op == 4)
        {
            int chave;
            cin >> chave;
            Node<int, char> *no = tree.search(chave);
            if (no == nullptr)
            {
                cout << "nao existe" << endl;
            }
            else
            {
                cout << tree.getValue(no) << endl;
            }
        }
        else if (op == 5)
        {
            cout << tree.height(tree.getRoot()) << endl;
        }
        else if (op == 6)
        {
            int chave;
            cin >> chave;
            tree.remove(chave);
        }

    } while (op != 7);

    tree.~RBTree();

    return 0;
}