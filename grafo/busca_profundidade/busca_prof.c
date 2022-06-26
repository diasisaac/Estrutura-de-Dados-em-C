#include <stdlib.h>
#include "matriz_adj.h"
#include <stdio.h>

void inicializa_vetores(grafo *grafo, vetores_grafo *vetores_grafo)
{
    vetores_grafo->vetor_cor = (char *)malloc(sizeof(char) * grafo->v);

    vetores_grafo->vetor_ditancia = (int *)malloc(sizeof(sizeof(int) * grafo->v));

    vetores_grafo->vetor_pai = (int *)malloc(sizeof(int) * grafo->v);

    vetores_grafo->vetor_fim = (int *)malloc(sizeof(int) * grafo->v);
}

void dfs(grafo *grafo, vetores_grafo *vetores_grafo)
{
    int u;
    int tempo;

    for (u = 0; u < grafo->v; u++)
    {

        vetores_grafo->vetor_cor[u] = 'b';
        vetores_grafo->vetor_pai[u] = -1;
        vetores_grafo->vetor_ditancia[u] = -1;
    }

    tempo = 0;

    printf("\nElemento inicial U: %c\n", grafo->mapa[0]);
    for (u = 0; u < grafo->v; u++)
    {

        if (vetores_grafo->vetor_cor[u] == 'b')
        {
            dfs_visit(grafo, u, vetores_grafo, &tempo);
        }
    }
}

void dfs_visit(grafo *grafo, int u, vetores_grafo *vetores_grafo, int *tempo)
{
    /* char *vetor_cor = (char *)malloc(sizeof(char) * grafo->v);
    int *vetor_ditancia = (int *)malloc(sizeof(sizeof(int) * grafo->v));
    int *vetor_pai = (int *)malloc(sizeof(int) * grafo->v);
    int *vetor_fim = (int *)malloc(sizeof(int) * grafo->v);
     
    int tempo;
    */

    int v;

    vetores_grafo->vetor_cor[u] = 'c';

    *tempo = *tempo + 1;

    vetores_grafo->vetor_ditancia[u] = *tempo;

    printf("valor de tempo: %d\n", *tempo);

    for (v = 0; v < grafo->v; v++)
    {
        if (grafo->matriz[u][v] == 1) //Tem adjacencia
        {
            if (vetores_grafo->vetor_cor[v] == 'b')
            {

                vetores_grafo->vetor_pai[v] = u;
                dfs_visit(grafo, v, vetores_grafo, tempo);
            }
        }
    }

    vetores_grafo->vetor_cor[u] = 'p';

    *tempo = *tempo + 1;
    vetores_grafo->vetor_fim[u] = *tempo;
}

void imprimir_busca(grafo *g, vetores_grafo *vetores_grafo)
{
    int i, j;

    char cor;

    for (i = 0; i < g->v; i++)
    {

        cor = vetores_grafo->vetor_cor[i];

        printf("\n**************\n");
        printf("Elemento em analise: %c", g->mapa[i]);

        if (cor == 'p')
        {
            printf("\ncor de %c: %c - de preto \n", g->mapa[i], vetores_grafo->vetor_cor[i]);

            printf("pai de %c eh %c\n", g->mapa[i], g->mapa[vetores_grafo->vetor_pai[i]]);

            printf("Marcacao tempo inicial de %c = %d\n", g->mapa[i], vetores_grafo->vetor_ditancia[i]);

            printf("Marcacao tempo final de %c = %d", g->mapa[i], vetores_grafo->vetor_fim[i]);
            printf("\n**************\n");
        }
        else
        {
            printf("Tem algo errado com esse elemento, favor checar\n");
        }
    }
}