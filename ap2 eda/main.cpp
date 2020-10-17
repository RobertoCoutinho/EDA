#include <iostream>
#include <bits/stdc++.h>
#include "node.h"
#include "pessoa.h"
#include "avl.h"
using namespace std;
int make_int(Pessoas *pessoa);
int make_int(string data);

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
            cout << "-> Digite o CPF a ser buscado: ";
            string cpf;
            cin >> cpf;
            cout << "----------------------------------------------------------------" << endl;
            treeCPF->avlSearch_CPF(cpf);
            cout << "----------------------------------------------------------------" << endl;
        }
        else if (op == 2)
        {
            cout << "-> Digite o nome(ou inicial) a ser buscado: ";
            string nome;
            cin >> nome;
            cout << "----------------------------------------------------------------" << endl;
            treeNome->avlSearch_nome(nome);
            cout << "----------------------------------------------------------------" << endl;
        }
        else if (op == 3)
        {
            string dataInicial, dataFinal;
            cout << "-> OBS: Obdeça o formato DD-MM-AAAA (ex.: 23-02-2010)." << endl;
            cout << "-> Digite a data inicial da busca (DD-MM-AAAA): ";
            cin >> dataInicial;
            cout << "-> Digite a data final da busca (DD-MM-AAAA): ";
            cin >> dataFinal;
            cout << "----------------------------------------------------------------" << endl;
            treeData->avlSearch_data(make_int(dataInicial), make_int(dataFinal));
            cout << "----------------------------------------------------------------" << endl;
        }

    } while (op != 4);
    return 0;
}

int make_int(Pessoas *pessoa)
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

int make_int(string data)
{
    string dia;
    dia += data[0];
    dia += data[1];
    string mes;
    mes += data[3];
    mes += data[4];
    string ano;
    ano += data[6];
    ano += data[7];
    ano += data[8];
    ano += data[9];
    string dataFormatada;
    dataFormatada += ano;
    dataFormatada += mes;
    dataFormatada += dia;
    return stoi(dataFormatada);
}