#ifndef AVL_H
#define AVL_H
//#include <bits/stdc++.h>
#include <vector>
#include <list>
#include "node.h"
#include "pessoa.h"

using namespace std;
template <typename Tkey>

class avl
{
private:
    Node<Tkey> *root;

protected:
    Node<Tkey> *left_rotate(Node<Tkey> *node)
    {
        // Rotaciona os elementos
        Node<Tkey> *aux = node->right; // Auxi vai receber a sub-arvore direita do no
        node->right = aux->left;       // A sub-arvore esquerda do no vai ser a sub-arvore direita do meu aux
        aux->left = node;              // O meu aux passa a ter o nó e seus filhos como filhos da direita
        // Atualiza a altura dos nos
        node->height = 1 + max(avl_height(node->left), avl_height(node->right));
        aux->height = 1 + max(avl_height(aux->left), avl_height(aux->right));

        return aux;
    }

    Node<Tkey> *right_rotate(Node<Tkey> *node)
    {
        // Rotacionando os elementos
        Node<Tkey> *aux = node->left; // Aux vai receber a sub-arvore esquerda do meu no
        node->left = aux->right;      // A sub-arvore esquerda do no vai ser a sub-arvore direita do aux
        aux->right = node;            // O meu auxiliar passa a ter o no e seus filhos (que são maiores que ele) como sub-arvore a direita
        // Atualizar a aultura dos nos
        node->height = 1 + max(avl_height(node->left), avl_height(node->right));
        aux->height = 1 + max(avl_height(aux->left), avl_height(aux->right));

        return aux;
    }

    Node<Tkey> *avl_insert(Node<Tkey> *node, Tkey key, Pessoas *value)
    {
        // Se eu chegar em uma posição nula eu crio o novo nó com a key passada e a pessoa
        if (node == nullptr)
        {
            Node<Tkey> *novo = new Node<Tkey>();
            novo->key = key;
            novo->value.push_back(value);
            novo->height = 1;
            novo->left = novo->right = nullptr;
            return novo;
        }
        // Busca a pessoa na arvore
        if (node->key > key)
        {
            node->left = avl_insert(node->left, key, value);
        }
        else if (node->key < key)
        {
            node->right = avl_insert(node->right, key, value);
        }
        else
        {
            node->value.push_back(value); // Se já existir um nó com aquela chave ele coloca a nova pessoa no vector de pessoas
            return node;
        }
        // Atualiza a altura da arvore e arruma o seu balanceamento
        node->height = 1 + max(avl_height(node->left), avl_height(node->right));
        node = avlinsert_fixup(node, key);
        return node;
    }

    Node<Tkey> *avlinsert_fixup(Node<Tkey> *node, Tkey key)
    {
        int equi = avl_balance(node);

        if (equi < -1 && key < node->left->key)
        { // Caso 4(A)
            node = right_rotate(node);
        }
        else if (equi < -1 && key > node->left->key)
        { // Caso 4(B)
            node->left = left_rotate(node->left);
            node = right_rotate(node);
        }
        else if (equi > 1 && key > node->right->key)
        { // Simetrico do 4(A)
            node = left_rotate(node);
        }
        else if (equi > 1 && key < node->right->key)
        { // Simetrico do 4(B)
            node->right = right_rotate(node->right);
            node = left_rotate(node);
        }

        return node;
    }

    void avl_searchCPF(Node<Tkey> *node, Tkey key)
    {
        // Busca um cpf na arvore
        Node<Tkey> *aux = root;
        while (aux != nullptr)
        {
            if (aux->key > key)
            {
                aux = aux->left;
            }
            else if (aux->key < key)
            {
                aux = aux->right;
            }
            else
            {
                avl_cout(aux); // Imprimi o nó do cpf buscado  //correção de BUG
                return;
            }
        }
        cout << "O CPF passado nao esta no documento" << endl;
        return;
    }

    string nome_(string nome, int aux)
    { // Retorna uma string de tamanho igual a que o usuario passou para comparar
        string str;
        for (int i = 0; i < aux; i++)
        {
            str += nome[i];
        }
        return str;
    }

    void nome_inorder(Node<Tkey> *node, string key)
    {
        // Percorre a arvore em busca dos nós que começam com a string passada pelo usuario
        if (node == nullptr)
        {
            return;
        }

        if (nome_(node->key, key.size()) > key)
        {
            nome_inorder(node->left, key);
        }
        else if (nome_(node->key, key.size()) == key)
        {
            avl_cout(node);
            nome_inorder(node->left, key);
            nome_inorder(node->right, key);
        }
        else
        {
            nome_inorder(node->right, key);
        }
    }

    void avl_searchDate(Node<Tkey> *node, Tkey data1, Tkey data2)
    {
        // Busca por nós que estejam entre as datas passadas
        if (node == nullptr)
        {
            return;
        }

        if (node->key >= data1 && node->key <= data2)
        {
            avl_searchDate(node->left, data1, data2);
            avl_cout(node);
            avl_searchDate(node->right, data1, data2);
        }
        else if (node->key < data1)
        {
            avl_searchDate(node->right, data1, data2);
        }
        else if (node->key > data2)
        {
            avl_searchDate(node->left, data1, data2);
        }
    }

    void avl_cout(Node<Tkey> *node)
    { // Imprimi o nó
        for (int i = 0; i < node->value.size(); i++)
        {
            cout << node->value[i]->cpf << ",";
            cout << node->value[i]->nome << ",";
            cout << node->value[i]->sobrenome << ",";
            cout << node->value[i]->data.tm_mon << "/";
            cout << node->value[i]->data.tm_mday << "/";
            cout << node->value[i]->data.tm_year << ",";
            cout << node->value[i]->cidade << endl;
        }
    }

    int avl_height(Node<Tkey> *node)
    {
        // Altura do nó
        if (node == nullptr)
        {
            return 0;
        }

        return node->height;
    }

    int avl_balance(Node<Tkey> *node)
    {
        // Balanço do nó
        if (node == nullptr)
        {
            return 0;
        }

        return avl_height(node->right) - avl_height(node->left);
    }

    Node<Tkey> *avl_clear(Node<Tkey> *node)
    {
        // Limpando a arvore
        if (node != nullptr)
        {
            node->left = avl_clear(node->left);
            node->right = avl_clear(node->right);
            delete node;
        }

        return nullptr;
    }

public:
    avl(void)
    {
        root = nullptr;
    }

    ~avl(void)
    {
        avl_clear(root);
        root = nullptr;
    }

    void avlInsert(Tkey key, Pessoas *value)
    {
        root = avl_insert(root, key, value);
    }

    void avlSearch_data(Tkey data1, Tkey data2)
    {
        avl_searchDate(root, data1, data2);
        return;
    }

    void avlSearch_nome(string key)
    {
        nome_inorder(root, key);
        return;
    }

    void avlSearch_CPF(Tkey key)
    {
        avl_searchCPF(root, key);
        return;
    }

    void avl_inorder(Node<Tkey> *root)
    {
        if (root == nullptr)
        {
            return;
        }

        avl_inorder(root->left);
        cout << root->key << endl;
        avl_inorder(root->right);
    }
};

#endif