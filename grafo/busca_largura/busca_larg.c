#include <stdio.h>
#include <stdlib.h>
#include "lista_adj.h"
#include "fila.h"

void bfs(grafo *grafo, int s)
{
    char *vetor_cor = (char *)malloc(sizeof(char) * grafo->v);
    int *vetor_ditancia = (int *)malloc(sizeof(sizeof(int) * grafo->v));
    int *vetor_pai = (int *)malloc(sizeof(int) * grafo->v);

    int u, v;
    int i = 0;

    for (i = 0; i < grafo->v; i++)
    {
        vetor_cor[i] = 'b';
        vetor_pai[i] = -1;
        vetor_ditancia[i] = -1;
    }

    vetor_cor[s] = 'c';
    vetor_ditancia[s] = 0;
    vetor_pai[s] = -1;

    Fila fila;
    fila_create(&fila, grafo->v);

    fila_push(&fila, s);

    printf("\n *** CHECAGEM DAS CORES INICIO ***\n");

    for (i = 0; i < grafo->v; i++)
    {

        printf("Setou cor do elemento %c pra '%c'\n", grafo->mapa[i], vetor_cor[i]);
    }

    while (!fila_isEmpty(fila))
    {
        u = fila_pop(&fila);

        printf("\nPercorra as arestas na lista encadeada de: %c\n", grafo->mapa[u]);

        lista *elem_adj; // Variavel v do pseudocódigo

        elem_adj = grafo->arestas[u];

        while (elem_adj != NULL) // cada v <- adj[u] PERCORE AS ADJACENCIAS DE U
        {
            printf("\n-> %c\n", grafo->mapa[elem_adj->valor]);
            printf("\nCor de %c = %c\n", grafo->mapa[elem_adj->valor], vetor_cor[elem_adj->valor]);
            if (vetor_cor[elem_adj->valor] == 'b')
            {
                vetor_cor[elem_adj->valor] = 'c';

                printf("Cor branca! Setou cor do elemento %c pra %c\n", grafo->mapa[elem_adj->valor], vetor_cor[elem_adj->valor]);

                vetor_ditancia[elem_adj->valor] = vetor_ditancia[u] + 1;

                vetor_pai[elem_adj->valor] = u;

                fila_push(&fila, elem_adj->valor);
            }
            else
            {
                printf("Cor diferente de branca! Nao mexe na cor!\n");
            }
            printf("\n");

            elem_adj = elem_adj->proximo;
        }
        vetor_cor[u] = 'p';
    }

    //Imprimir as cores pra checagem final
    printf("\nCHECAGEM FINAL\n");

    for (i = 0; i < grafo->v; i++)
    {
        printf("\nElemento: '%c'\n", grafo->mapa[i]);
        printf("Setou cor de '%c' pra '%c'\n", grafo->mapa[i], vetor_cor[i]);
        printf("Setou pai de '%c' pra '%c'\n", grafo->mapa[i], grafo->mapa[vetor_pai[i]]);
        printf("A distancia de '%c' pra seu pai '%c' eh: %d\n", grafo->mapa[i], grafo->mapa[vetor_pai[i]], vetor_ditancia[i]);
    }
}
