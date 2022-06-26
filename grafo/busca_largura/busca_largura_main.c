#include <stdio.h>
#include <stdlib.h>
#include "lista_adj.h"
#include "fila.h"

int main()
{
    grafo *graph;

    int elemento;

    char item;

    graph = carregar_arquivo("dados.txt", graph);

    printf("\n*** LISTA DE ADJACENCIA *** \n");

    imprimir(graph);

    //Seto o vertice que quero executar a busca
    printf("Digite o elemento a buscar: ");
    scanf(" %c", &item);

    printf("\nLocalizando vertice que vou trabalhar...\n");

    elemento = localizarVertice(graph, item);

    printf("\n *** RESULTADO ***\n");
    if (elemento == -1)
    {
        printf("Impossivel executar a busca pois o elemento nao existe\n");
    }
    else
    {

        printf("\n ***** CHAMANDO A BUSCA EM LARGURA *****\n");

        bfs(graph, elemento);
    }

    return 0;
}
