#ifndef graphm_h
#define graphm_h
#include <stdexcept>
#include <list>
#include <vector>
#include "graph.h"

/**
 * Class GraphM: implementation of a graph as an adjacency matrix 
 */
class GraphM : public Graph
{
private:
    int N;
    int M;
    int **matrix;
    int *mark;

    // Check if a vertex v is valid ( 0 <= v <= N-1 )
    void checkVertex(int v)
    {
        if (v < 0 || v > N - 1)
            throw std::runtime_error("Intervalo de valor de vertice invalido");
    }

public:
    // Constructor
    GraphM(int n)
    {
        if (n <= 0)
            throw std::runtime_error("Tamanho invalido");
        N = n;
        M = 0;
        // Aloccate memory for mark array
        mark = new int[n];
        // Allocate memory for a matrix n x n
        matrix = new int *[n];
        for (int i = 0; i <= n - 1; ++i)
        {
            matrix[i] = new int[n];
        }
        // Initialize matrix with 0's
        for (int i = 0; i <= n - 1; ++i)
            for (int j = 0; j <= n - 1; ++j)
                matrix[i][j] = 0;
    }

    // Destructor
    ~GraphM()
    {
        delete[] mark;
        for (int i = 0; i < N; i++)
            delete[] matrix[i];
        delete[] matrix;
    }

    // Return: the number of vertices and edges respectively
    int n() { return N; }
    int m() { return M; }

    // Return a list containing v's incident edges
    std::list<Edge> &incidentEdges(int v)
    {
        std::list<Edge> *lst = new std::list<Edge>();
        for (int i = 0; i < N; ++i)
        {
            if (matrix[v][i] != 0)
            {
                lst->push_back(Edge(i, matrix[v][i]));
            }
        }
        return *lst;
    }

    // Return a list containing vertex v's neighbors
    std::list<int> &neighbors(int v)
    {
        std::list<int> *lst = new std::list<int>();
        for (int i = 0; i < N; ++i)
        {
            if (matrix[v][i] != 0)
            {
                lst->push_back(i);
            }
        }
        return *lst;
    }

    void setEdgeWeight(int v1, int v2, int wgt)
    {
        if (wgt <= 0)
            throw std::runtime_error("Peso negativo ou igual a zero");
        if (!isEdge(v1, v2))
            ++M;
        matrix[v1][v2] = wgt;
    }

    // Add an edge
    void addEdge(int v1, int v2)
    {
        setEdgeWeight(v1, v2, 1);
    }

    // Delete an edge
    void delEdge(int v1, int v2)
    {
        if (isEdge(v1, v2))
        {
            M--;
            matrix[v1][v2] = 0;
        }
    }

    // Determine if an edge is in the graph
    bool isEdge(int v1, int v2)
    {
        return (matrix[v1][v2] > 0);
    }

    int weight(int v1, int v2)
    {
        checkVertex(v1);
        checkVertex(v2);
        if (isEdge(v1, v2))
            return matrix[v1][v2];
        else
            return 0;
    }

    int getMark(int v)
    {
        checkVertex(v);
        return mark[v];
    }

    void setMark(int v, int value)
    {
        checkVertex(v);
        mark[v] = value;
    }
};

#endif