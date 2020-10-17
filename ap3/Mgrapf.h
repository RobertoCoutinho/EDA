#ifndef mgrapf_h
#define mgrapf_h
#include <stdexcept>
#include <list>
#include <queue>

using namespace std;

/**
 * Class MGraph : implementação de um grafo com matriz
*/

class MGraph : public Graph
{
private:
    int N;        // Vertices
    int M;        // Arestas
    int **matrix; // Matriz
    int *mark;    // Caso marque um vertice

    void checkVertex(int v)
    {
        if (v < 0 || v > N - 1)
        {
            throw runtime_error("Intervalo de valor de vertice invalido");
        }
    }

public:
    // Construtor
    MGraph(int n)
    {
        if (n <= 0)
        {
            throw runtime_error("Tamanho Invalido");
        }
        N = n;
        M = 0;
        mark = new int[n];
        matrix = new int *[n];
        for (int i = 0; i <= n - 1; i++)
        {
            matrix[i] = new int[n];
        }

        for (int i = 0; i <= n - 1; i++)
        {
            for (int j = 0; j <= n - 1; j++)
            {
                matrix[i][j] = 0;
            }
        }
    }

    // Destrutor
    ~MGraph()
    {
        delete[] mark;
        for (int i = 0; i < N; i++)
        {
            delete[] matrix[i];
        }
        delete matrix;
    }

    // Retorna o numero de vertices e arestas da matriz
    int n()
    {
        return N;
    }
    int m()
    {
        return M;
    }

    // Retorna a lista de vizinhos de um vertice
    list<int> &neighbors(int v)
    {
        list<int> *lis = new list<int>();
        for (int i = 0; i < N; i++)
        {
            if (matrix[v][i] != 0)
            {
                lis->push_back(i);
            }
        }
        return *lis;
    }

    // Setando o peso de uma aresta
    void setEdgeWeight(int v1, int v2, int wgt)
    {
        if (wgt < 0)
        {
            throw runtime_error("Peso negativo");
        }
        if (!isEdge(v1, v2))
        {
            ++M;
        }
        matrix[v1][v2] = wgt;
        matrix[v2][v1] = wgt;
    }

    // Adicionando uma nova aresta entre os vertices
    void addEdge(int v1, int v2)
    {
        setEdgeWeight(v1, v2, 1);
    }

    // Deletando a aresta entre os vertices
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

    // Retorna o peso de uma aresta e 0 caso não exista essa aresta
    int weight(int v1, int v2)
    {
        if (isEdge(v1, v2))
        {
            return matrix[v1][v2];
        }
        else
        {
            return 0;
        }
    }

    // Retorna a marca de um vertice
    int getMark(int v)
    {
        return mark[v];
    }

    // Setando a marca de um vertice
    void setMark(int v, int value)
    {
        checkVertex(v);
        mark[v] = value;
    }

    // Retorna a lista de arestas que chegam naquele vertice
    list<Edge> &incidentEdges(int v)
    {
        list<Edge> *lis = new list<Edge>();
        for (int i = 0; i < N; i++)
        {
            if (matrix[v][i] != 0)
            {
                lis->push_back(Edge(i, matrix[v][i]));
            }
        }
        return *lis;
    }

    bool isBipartiteUTIl()
    {
        int color[N];
        for (int i = 0; i < N; ++i)
        {
            color[i] = -1;
        }
        for (int i = 0; i < N; i++)
        {
            if (color[i] == -1)
            {
                if (isBipartite(i, color) == false)
                {
                    cout << "NAO" << endl;
                    return false;
                }
            }
        }
        cout << "SIM" << endl;
        for (int i = 0; i < N; i++)
        {
            if (color[i] == 1)
            {
                cout << i << " R" << endl;
            }
            else
            {
                cout << i << " B" << endl;
            }
        }

        return true;
    }

    bool isBipartite(int src, int color[])
    {
        // Create a color array to store colors
        // assigned to all veritces. Vertex
        // number is used as index in this array.
        // The value '-1' of colorArr[i]
        // is used to indicate that no color
        // is assigned to vertex 'i'. The value 1
        // is used to indicate first color
        // is assigned and value 0 indicates
        // second color is assigned.
        color[src] = 1;
        // Assign first color to source

        // Create a queue (FIFO) of vertex
        // numbers and enqueue source vertex
        // for BFS traversal
        queue<int> q;
        q.push(src);

        // Run while there are vertices
        // in queue (Similar to BFS)
        while (!q.empty())
        {
            // Dequeue a vertex from queue ( Refer http://goo.gl/35oz8 )
            int u = q.front();
            q.pop();

            // Return false if there is a self-loop
            if (isEdge(u, u))
                return false;

            // Find all non-colored adjacent vertices
            for (int v = 0; v < N; ++v)
            {
                // An edge from u to v exists and
                // destination v is not colored
                if (isEdge(u, v) && color[v] == -1)
                {
                    // Assign alternate color to this adjacent v of u
                    color[v] = 1 - color[u];
                    q.push(v);
                }

                // An edge from u to v exists and destination
                // v is colored with same color as u
                else if (isEdge(u, v) && color[v] == color[u])
                    return false;
            }
        }

        // If we reach here, then all adjacent
        // vertices can be colored with alternate color
        return true;
    }
};

#endif