
#ifndef MAIN
#define MAIN
#include <iostream>
#include <bits/stdc++.h>
#include "node.h"
#include "pessoa.h"
#include "avl.h"
using namespace std;
int make_int(Pessoas *pessoa);

int main()
{
    int op = 0;

    ifstream myfile;
    string line;

    Pessoas *pessoa; // Objeto pessoa

    avl<string> *treeCPF = new avl<string>();
    avl<string> *treeNome = new avl<string>();
    avl<int> *treeData = new avl<int>();

    myfile.open("data.csv");
    getline(myfile, line);

    while (myfile.good())
    {
        pessoa = new Pessoas();
        getline(myfile, line);
        pessoa->set_pessoa(line);
        treeCPF->avlInsert(pessoa->cpf, pessoa);
        treeNome->avlInsert(pessoa->nome, pessoa);
        treeData->avlInsert(make_int(pessoa), pessoa);
    }

    do
    {
        cout << "*************************************************" << endl;
        cout << "* 1 - Pesquisar pessoa pelo CPF                 *" << endl;
        cout << "* 2 - Pesquisar pessoas pelo nome               *" << endl;
        cout << "* 3 - Pesquisar pessoas pela data de nascimento *" << endl;
        cout << "* 4 - Sair                                      *" << endl;
        cout << "*************************************************" << endl;
        cin >> op;
        if (op == 1)
        {
            cout << "   -> Digite o CPF a ser buscado";
            string cpf;
            cin >> cpf;
            cout << endl;
            treeCPF->avlSearch(cpf);
            else if (op == 2)
            {
            }
            else if (op == 3)
            {
            }
        }
        while (op == 4)
            ;
        cpf->~avl();
        nomes->~avl();
        datas->~avl();
        return 0;
    }

    int make_int(Pessoas * pessoa)
    {
        string str = to_string(pessoa->data.tm_year);

        if (pessoa->data.tm_mon < 10)
        {
            str += "0";
            str += to_string(pessoa->data.tm_mon);
        }
        else
        {
            str += to_string(pessoa->data.tm_mon);
        }
        if (pessoa->data.tm_mday < 10)
        {
            str += "0";
            str += to_string(pessoa->data.tm_mday);
        }
        else
        {
            str += to_string(pessoa->data.tm_mday);
        }

        return stoi(str);
    }