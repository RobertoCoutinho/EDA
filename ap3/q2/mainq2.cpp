#include <iostream>
#include "graph.h"
#include "graphm.h"
#include <list>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void trataDado(string dados, Graph *grafo, vector<string> &nomes);
int melhor_caso(Graph *grafo);

int main()
{
    Graph *grafo;
    fstream myfile;
    string line;
    myfile.open("grafoq2.txt");

    while (myfile.good())
    {
        getline(myfile, line);
        int n = stoi(line);
        if (n != 0)
        {
            vector<string> nomes;
            grafo = new GraphM(n);
            //cout << n << endl;
            if (line != "")
            {
                for (int i = 0; i < n; i++)
                {
                    getline(myfile, line);
                    trataDado(line, grafo, nomes);
                }
                int res = melhor_caso(grafo);
                cout << res << endl;
                grafo->~Graph();
            }
        }
    }
    return 0;
}

void trataDado(string dados, Graph *grafo, vector<string> &nomes)
{

    string p1, p2;
    int i_p1 = -1, i_p2 = -1;
    std::stringstream aux;
    aux << dados;
    getline(aux, dados, ' ');
    p1 = dados;
    getline(aux, dados, '\n');
    p2 = dados;
    //cout << p1 << " " << p2 << endl;

    for (int i = 0; i < nomes.size(); i++)
    {
        if (nomes[i] == p1)
        {
            i_p1 = i;
        }
    }
    if (i_p1 == -1)
    {
        nomes.push_back(p1);
    }
    for (int i = 0; i < nomes.size(); i++)
    {
        if (nomes[i] == p1)
        {
            i_p1 = i;
        }
        if (nomes[i] == p2)
        {
            i_p2 = i;
        }
    }
    grafo->addEdge(i_p2, i_p1);
}

int melhor_caso(Graph *grafo)
{
    list<int> *irao = new list<int>();

    for (int i = 0; i < grafo->n(); i++)
    {
        if (grafo->neighbors(i).empty())
        {
            irao->push_back(i);
        }
    }

    for (int i = 0; i < grafo->n(); i++)
    {
        if (grafo->getMark(i) != 5 && !grafo->neighbors(i).empty())
        {
            list<int> vizinhos = grafo->neighbors(i);
            for (list<int>::iterator it = vizinhos.begin(); it != vizinhos.end(); ++it)
            {
                for (list<int>::iterator at = irao->begin(); at != irao->end(); ++at)
                {
                    if (*it == *at)
                    {
                        grafo->setMark(i, 5);
                    }
                }
            }
            if (grafo->getMark(i) != 5)
            {
                for (list<int>::iterator it = vizinhos.begin(); it != vizinhos.end(); it++)
                {
                    grafo->setMark(*it, 5);
                }
                irao->push_back(i);
            }
        }
    }

    int resultado = irao->size();
    delete irao;
    return resultado;
}