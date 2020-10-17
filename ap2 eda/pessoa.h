#ifndef PESSOA
#define PESSOA

#include <iostream>
#include <sstream>
#include <time.h>

using namespace std;

class Pessoas
{
public:
    string cpf;
    string nome;
    string sobrenome;
    string cidade;
    struct tm data;
    /* pessoas();
    ~pessoas(); */
    void set_pessoa(string dados)
    {
        stringstream aux;
        aux << dados;

        getline(aux, dados, ',');
        this->cpf = dados;
        getline(aux, dados, ',');
        this->nome = dados;
        getline(aux, dados, ',');
        this->sobrenome = dados;
        getline(aux, dados, '/');
        this->data.tm_mon = stoi(dados);
        getline(aux, dados, '/');
        this->data.tm_mday = stoi(dados);
        getline(aux, dados, ',');
        this->data.tm_year = stoi(dados);
        getline(aux, dados, ';');
        this->cidade = dados;

        return;
    }
};

/* pessoas::pessoas(){
    
}

pessoas::~pessoas(){
    
}  */

#endif