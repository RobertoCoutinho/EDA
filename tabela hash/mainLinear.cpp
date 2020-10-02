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
    tabela_hash<string, string> *tabela = new tabela_hash<string, string>(601); //sempre iniciar tabela com tamanho primo maior que a quantidade de elementos a serem cadastrados.
    std::fstream myfile;
    string line;
    myfile.open("dados.csv");
    //loop que manda as linhas do csv para a função trataDado
    while (myfile.good())
    {
        getline(myfile, line);
        if (line != "") //comparação pode ser removida se o csv não tiver linha vazia
        {
            trataDado(line, tabela);
        }
    }

    //------teste da tabela com sondagem linear--------

    tabela->print();                                                     //printar toda tabela, deve ficar apenas uma posição vazia, ja que o csv tem 600 linhas e a tabela 601
    cout << "Tamanho: " << tabela->getTamanho() << endl;                 //printar o tamanho geral da tabela(numero de espaços no vector, nesse caso 601)
    cout << "Quantidade de elementos: " << tabela->getQtdElem() << endl; //printar a quantidade de elementos cadastrados na tabela, nesse caso 600
    if (!tabela->searchLinear("soo1ohWoh5"))                             //faço a busca da chave "soo1ohWoh5", e printa caso ela seja encontrada, nesse caso ela sera encontrada
    {
        cout << "CHAVE NAO ENCONTRADA" << endl;
    }
    tabela->removeLinear("soo1ohWoh5");      //removo a chave buscada anteriormente
    if (!tabela->searchLinear("soo1ohWoh5")) //faço a busca da chave "soo1ohWoh5" novamente, dessa vez ela não sera encontrada pois foi removida anteriomente
    {
        cout << "CHAVE NAO ENCONTRADA" << endl;
    }
    cout << "Tamanho: " << tabela->getTamanho() << endl;                 //printar novamente o tamanho da tabela, que devera ser o mesmo
    cout << "Quantidade de elementos: " << tabela->getQtdElem() << endl; //printar novamente a quantidade de elementos, que devera ser 599, um a menos ja que teve uma remoção
    delete tabela;
    return 0;
}

//função que recebe uma linha do csv divide em chave e valor e manda para o insert
void trataDado(string dados, tabela_hash<string, string> *tabela)
{
    string chave, valor;
    std::stringstream aux;
    aux << dados;
    getline(aux, dados, ',');
    chave = dados;
    getline(aux, dados, ';');
    valor = dados;
    if (!tabela->insertLinear(chave, valor))
    {
        cout << "ERRO AO INSERIR, TABELA CHEIA" << endl;
    }
}