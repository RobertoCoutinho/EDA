void DFS(Graph &G); //  prototipos  das  funcoes
void DFS_VISIT(Graph &G, int v, int *d, int *f, int &t);
#define BRANCO
#define CINZA
#define PRETO
#define BLACK
#define RED

void DFS(Graph &G)
{
    int d[G.n()];  //  tempo  de  descoberta
    int f[G.n()];  //  tempo  de  finalizacao
    int tempo = 0; //  variavel  para o tempo
    for (int v = 0; v < G.n(); ++v)
        G.setMark(v, BRANCO);
    for (int v = 0; v < G.n(); ++v)
        if (G.getMark(v) == BRANCO)
            DFS_VISIT(G, v, d, f, tempo);
}

void DFS_VISIT(Graph &G, int v, int *d, int *f, int &tempo)
{
    tempo++;
    d[v] = tempo;
    G.setMark(v, CINZA);
    cout << "Vertex " << v << " visited" << endl;
    for (int &w : G.neighbors(v))
        if (G.getMark(w) == BRANCO)
            DFS_VISIT(G, w, d, f, tempo);
    G.setMark(v, PRETO);
    tempo++;
    f[v] = tempo;
}

int bfs(grafo p[], int atual, int anterior, int corA[])
{

    if (!corA[atual])
    {
        corA[atual] = (corA[anterior] % 2) + 1;
    }
    else if (corA[atual] == corA[anterior])
    {
        return FALSE;
    }
    int bipartido = TRUE;
    Node *vertice = p[atual].inicio;
    while (vertice != NULL)
    {
        if (!corA[vertice->vizinho])
        {
            if (bfs(p, vertice->vizinho, atual, corA))
                return FALSE;
        }
        vertice = vertice->proximo;
    }
    return bipartido;
}