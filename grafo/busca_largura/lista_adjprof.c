#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_adj.h"
#include "fila.h"

lista *inserirInicio(lista *list, int v)
{
    lista *novo_no = (lista *)malloc(sizeof(lista));
    novo_no->valor = v;
    novo_no->proximo = list;
    return novo_no;
}

//Pra inicializar o grafo passa a quantidade de vertices
grafo *inicializar(int tam_vertice, int tam_arestas)
{
    //Aloca espaco pra o grafo
    grafo *g = (grafo *)malloc(sizeof(struct grafo));

    //Inicializa os atributos do grafo
    g->v = tam_vertice;
    g->i_v = 0;

    //Aloca o tamanho do mapa
    g->mapa = (char *)malloc(sizeof(char) * tam_vertice);

    //Aloca o tamanho das arestas
    g->arestas = (lista **)malloc(sizeof(lista *) * tam_arestas);

    //Inicializa todas as listas como listas vazias, ou seja, seta todas pra NULL
    for (int i = 0; i < tam_arestas; i++)
    {
        g->arestas[i] = NULL;
    }

    return g;
}

//Passa o grafo e o caracter, compara e retorna a posição

//Eu tenho um array e quero saber em qual posição um caracter está nesse array
int localizarVertice(grafo *grafo, char c)
{
    int encontrado = -1;
    int i;

    for (i = 0; i < grafo->v; i++)
    {
        if (grafo->mapa[i] == c)
        {
            encontrado = i;
            break;
        }
    }

    return encontrado;
}

void adicionarAresta(grafo *grafo, char aresta_a, char aresta_b)
{
    int posicao_aresta_a, posicao_aresta_b;

    //Localizar a posicao do vertice no grafo
    posicao_aresta_a = localizarVertice(grafo, aresta_a);
    posicao_aresta_b = localizarVertice(grafo, aresta_b);

    //Inserir na lista de A o elemento B e na lista de B o elemento A

    //O inserir é da lista encadeada

    //Vai ser inserido como inteiro mesmo porque vou tá colocando a posicao.
    grafo->arestas[posicao_aresta_a] = inserirInicio(grafo->arestas[posicao_aresta_a], posicao_aresta_b);

    grafo->arestas[posicao_aresta_b] = inserirInicio(grafo->arestas[posicao_aresta_b], posicao_aresta_a);

    /*
    Pra matriz é só juntar o codigo que o prof já fez de matriz e colcoar assim

    matriz[posicao_aresta_a][posicao_aresta_b] = 1
    matriz[posicao_aresta_b][posicao_aresta_a] = 1

    */
}

void adicionarVertice(grafo *grafo, char vertice)
{
    if (grafo->i_v < grafo->v)
    {
        //Isso aqui já enumera com os indices e os valores do array

        //Coloca o caracter dentro do mapa na posicao i_v
        grafo->mapa[grafo->i_v] = vertice;

        grafo->i_v++;
    }
}

void imprimir(grafo *graph)
{
    for (int i = 0; i < graph->v; i++)
    {

        printf("%c : ", graph->mapa[i]);

        lista *aux = graph->arestas[i];

        while (aux != NULL)
        {
            printf("-> %c ", graph->mapa[aux->valor]);
            aux = aux->proximo;
        }
        printf("\n-----\n");
    }
}

grafo *carregar_arquivo(char *nome, grafo *grafo)
{
    printf("Carregando...\n");
    FILE *arq;

    int num_vert, num_ares;
    int i = 0;
    char buffer[20];

    arq = fopen(nome, "r");

    fscanf(arq, "%d %d", &num_vert, &num_ares);

    //printf("Num vert: %d | ver arest: %d |\n", num_vert, num_ares);

    grafo = inicializar(num_vert, num_ares);

    printf("\n*** Lendo os vertices ***\n");
    for (i = 0; i < num_vert; i++)
    {
        fscanf(arq, "%s", buffer);

        printf("Vertice lido: %c\n", buffer[0]);

        adicionarVertice(grafo, buffer[0]);
    }

    for (i = 0; i < num_ares; i++)
    {

        printf("\n*** Lendo as arestas ***\n");
        fscanf(arq, "%s", buffer);

        printf("%c || %c\n", buffer[0], buffer[1]);

        adicionarAresta(grafo, buffer[0], buffer[1]);
    }

    return grafo;

    fclose(arq);
}
