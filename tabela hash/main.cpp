#include "hash.h"
#include <iostream>
#include <fstream>
#include <sstream>
using std::cout;
using std::endl;
using std::string;
void trataDado(string dados, tabela_hash<string, string> *tabela);
int main()
{
    tabela_hash<string, string> *tabela = new tabela_hash<string, string>(601); //sempre iniciar tabela com tamanho primo.
    std::fstream myfile;
    string line;
    myfile.open("dados.csv");
    while (myfile.good())
    {
        getline(myfile, line);
        if (line != "") //comparação pode ser removida se o csv não tiver linha vazia
        {
            trataDado(line, tabela);
        }
    }
    tabela->print();
    cout << "tamanho: " << tabela->getTamanho() << endl;
    cout << "qtd elementos: " << tabela->getQtdElem() << endl;
    tabela->removeLinear("Choh4Eiz");
    cout << "tamanho: " << tabela->getTamanho() << endl;
    cout << "qtd elementos: " << tabela->getQtdElem() << endl;
    tabela->searchLinear("soo1ohWoh5");
    return 0;
}

void trataDado(string dados, tabela_hash<string, string> *tabela)
{
    string chave, valor;
    std::stringstream aux;
    aux << dados;
    getline(aux, dados, ',');
    chave = dados;
    getline(aux, dados, ';');
    valor = dados;
    tabela->insertLinear(chave, valor);
    //cout << "chave: " << chave << " valor: " << valor << endl;
}