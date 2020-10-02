#include <iostream>
#include "node.h"
#include <vector>     // for std::vector
#include <functional> // for std::hash
using std::cout;
using std::endl;
using std::hash;
using std::vector;

template <typename tkey, typename tvalue>

class tabela_hash
{
private:
    vector<Node<tkey, tvalue>> tabela;
    int tamanho;      //tamanho da tabela
    int qtd_elem = 0; //Quantidade de elementos inseridos

public:
    //construtor da tabela
    explicit tabela_hash(int tamanho = 101)
    {
        this->tamanho = tamanho;
        tabela.resize(tamanho);
    }

    //retorna tamanho da tabela
    int getTamanho()
    {
        return tamanho;
    }

    //retorna a quantidade de elementos inseridos na tabela
    int getQtdElem()
    {
        return qtd_elem;
    }

    //sondagem linar
    size_t tableSlotLinear(const tkey &x, int num_tentativa) const
    {
        std::hash<tkey> hf;
        return (hf(x) + num_tentativa) % tamanho; // método da divisão: g(x) = x % M;
    }

    //insert usando sondagem linear
    bool insertLinear(const tkey &x, const tvalue &v)
    {
        for (int i = 0; i < tamanho; i++)
        {
            size_t slot = tableSlotLinear(x, i);
            //se o espeço estiver vazio ou estiver sido deletado ele será usado
            if (tabela[slot].status != ACTIVE)
            {
                tabela[slot].key = x;
                tabela[slot].value = v;
                tabela[slot].status = ACTIVE;
                qtd_elem++;
                return true;
            }
        }
        //Se ao sair do for ainda não tiver retornado é porque a tabela esta cheia
        return false;
    }

    //recebo a chave para fazer a busca, caso ache, a função printa chave, valor e retorna verdadeiro, caso não ache retorna falso
    bool searchLinear(const tkey &x) //busca usando sondagem linar
    {
        for (int i = 0; i < tamanho; i++)
        {
            size_t slot = tableSlotLinear(x, i);
            if (tabela[slot].status == ACTIVE)
            {
                //se o campo for ativo e a chave igual a função, printa e retorna verdadeiro.
                if (x == tabela[slot].key)
                {
                    cout << "chave: " << tabela[slot].key << " valor: " << tabela[slot].value << endl;
                    return true;
                }
            }
            //se achar um campo vazio retorna falso,
            //no caso de um campo estar deletado o for continua, pois a chave podera estar mais a frente
            else if (tabela[slot].status == EMPTY)
            {
                return false;
            }
        }
        //se o for acabar retorna falso pois a chave não esta na tabela
        return false;
    }

    //função muito parecida com a busca, so que ao achar a chave o campo status recebe DELETED
    //Se a função achar a chave ela retorna verdadeira caso contrario retorna falso
    bool removeLinear(const tkey &x) //remove usando sondagem linear
    {
        for (int i = 0; i < tamanho; i++)
        {
            size_t slot = tableSlotLinear(x, i);
            if (tabela[slot].status == ACTIVE)
            {

                if (x == tabela[slot].key)
                {
                    tabela[slot].status = DELETED;
                    qtd_elem--;
                    return true;
                }
            }
            else if (tabela[slot].status == EMPTY)
            {
                return false;
            }
        }
        return false;
    }

    //sondagem dublo hash
    size_t tableSlotDuploHash(const tkey &x, int num_tentativa) const
    {
        std::hash<tkey> hf;
        return ((hf(x) % tamanho) + num_tentativa * (1 + (hf(x) % (tamanho - 1)))) % tamanho;
    }

    //insert usasndo sondagem duplohash, basicamente a mesma função insert linear, so muda que chama a função tableSlotDuploHash
    bool insertDuploHash(const tkey &x, const tvalue &v)
    {
        for (int i = 0; i < tamanho; i++)
        {
            size_t slot = tableSlotDuploHash(x, i);
            //se o espeço estiver vazio ou estiver sido deletado ele será usado
            if (tabela[slot].status != ACTIVE)
            {
                tabela[slot].key = x;
                tabela[slot].value = v;
                tabela[slot].status = ACTIVE;
                qtd_elem++;
                return true;
            }
        }
        return false;
    }

    //busca usando sondagem DuploHash, basicamente a mesma função search linear, so muda que chama a função tableSlotDuploHash
    bool searchDuploHash(const tkey &x)
    {
        for (int i = 0; i < tamanho; i++)
        {
            size_t slot = tableSlotDuploHash(x, i);
            if (tabela[slot].status == ACTIVE)
            {
                //se o campo for ativo e a chave igual, a função printa e retorna verdadeiro.
                if (x == tabela[slot].key)
                {
                    cout << "chave: " << tabela[slot].key << " valor: " << tabela[slot].value << endl;
                    return true;
                }
            }
            //se achar um campo vazio retorna falso,
            //no caso de um campo estar deletado o for continua, pois a chave podera estar mais a frente
            else if (tabela[slot].status == EMPTY)
            {
                return false;
            }
        }
        //se for acabar retorna falso pois a chave não esta na tabela
        return false;
    }

    //função muito parecida com a busca, so que ao achar a chave o campo status recebe DELETED
    //Se a função achar a chave ela retorna verdadeira caso contrario retona falso
    bool removeDuploHash(const tkey &x) //remove usando sondagem DuploHash
    {
        for (int i = 0; i < tamanho; i++)
        {
            size_t slot = tableSlotDuploHash(x, i);
            if (tabela[slot].status == ACTIVE)
            {

                if (x == tabela[slot].key)
                {
                    tabela[slot].status = DELETED;
                    qtd_elem--;
                    return true;
                }
            }
            else if (tabela[slot].status == EMPTY)
            {
                return false;
            }
        }
        return false;
    }

    //função que printa toda a tabela, da primeira a ultima posição
    void print()
    {
        for (int i = 0; i < tamanho; i++)
        {
            if (tabela[i].status == ACTIVE)
            {
                cout << "chave: " << tabela[i].key << " valor: " << tabela[i].value << endl;
            }
            else
            {
                cout << "Vazio" << endl;
            }
        }
    }
};