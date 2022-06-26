#include <stdio.h>
#include <stdlib.h>
#include "lista_adj.h"

int main()
{
    grafo *graph;

    int tam_vertice = 4;
    int tam_aresta = 4;

    graph = inicializar(tam_vertice, tam_aresta);

    adicionarVertice(graph, 'd');
    adicionarVertice(graph, 'a');
    adicionarVertice(graph, 'i');
    adicionarVertice(graph, 'l');

    adicionarAresta(graph, 'a', 'd');

    adicionarAresta(graph, 'a', 'i');

    adicionarAresta(graph, 'd', 'l');

    adicionarAresta(graph, 'i', 'd');

    imprimir(graph);
    return 0;
}
