#include <iostream>
#include "mgraph.h"
#include "Mgrapf.h"
#include <fstream>
#include <sstream>
#define BLACK 3
#define RED 4

using namespace std;

void trataDado(string dados, Graph *grafo);

void DFS_VISIT(Graph *G, int v, int *d, int *f, int &tempo)
{
    tempo++;
    d[v] = tempo;
    G->setMark(v, RED);
    cout << " Vertex " << v << " visited " << endl;
    for (int &w : G->neighbors(v))
        if (G->getMark(w) == BLACK)
            DFS_VISIT(G, w, d, f, tempo);
    G->setMark(v, RED);
    tempo++;
    f[v] = tempo;
}

void DFS(Graph *G)
{

    for (int v = 0; v < G->n(); v++)
    {
        if (G->getMark(v) != RED && G->getMark(v) != BLACK)
        {
            G->setMark(v, RED);
        }
        for (int j : G->neighbors(v))
        {
            for (int z = 0; z < G->n(); z++)
            {
                if (G->getMark(j) != RED && G->getMark(j) != BLACK)
                {
                    if (j == z)
                    {
                        if (G->getMark(v) == RED)
                        {
                            G->setMark(z, BLACK);
                        }
                        else
                        {
                            G->setMark(z, RED);
                        }
                    }
                }
            }
        }
    }
}

bool verifica(Graph *G)
{
    bool ver = true;

    for (int i = 0; i < G->n(); i++)
    {
        if (!G->neighbors(i).empty())
        {
            for (int vizinhos : G->neighbors(i))
            {
                if (G->getMark(i) == G->getMark(vizinhos))
                {
                    ver = false;
                    return ver;
                }
            }
        }
    }

    return ver;
}

int main()
{
    Graph *grafo;
    fstream myfile;
    string line;
    myfile.open("grafos.txt");
    //loop que manda as linhas do csv para a função trataDado
    getline(myfile, line);
    int n = stoi(line);
    grafo = new MGraph(n);
    int cont = 1;
    while (myfile.good())
    {
        getline(myfile, line);
        if (line != "") //comparação pode ser removida se o csv não tiver linha vazia
        {

            if (line != "0 0")
            {

                trataDado(line, grafo);
            }
            else
            {
                grafo->isBipartiteUTIl();
                grafo->~Graph();
                getline(myfile, line);
                int n = stoi(line);
                if (n != 0)
                {
                    grafo = new MGraph(n);
                }
                else
                {
                    getline(myfile, line);
                }
            }
        }
        cont++;
    }
    return 0;
}

void trataDado(string dados, Graph *grafo)
{

    int n1, n2;
    std::stringstream aux;
    aux << dados;
    getline(aux, dados, ' ');
    n1 = stoi(dados);
    getline(aux, dados, '\n');
    n2 = stoi(dados);
    //cout << n1 << " " << n2 << endl;
    grafo->addEdge(n1, n2);
    grafo->addEdge(n2, n1);
}