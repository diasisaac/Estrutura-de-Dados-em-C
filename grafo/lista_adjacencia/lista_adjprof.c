#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_adj.h"

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
    int encontrado = 0;
    grafo->i_v = 0;

    for (int i = 0; i < grafo->v; i++)
    {
        if (grafo->mapa[grafo->i_v] == c)
        {
            encontrado = grafo->i_v;
            break;
        }
        grafo->i_v++;
    }

    printf("Vertice %c localizado na posicao: %d\n", grafo->mapa[grafo->i_v], grafo->i_v);

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

void carregar_arquivo(char *nome, grafo *grafo)
{
    printf("Carregando...\n");

    char entrada[256];
    char buffer[256];
    char a, b;
    int codigo;
    int i, j;

    int numero_vertices, numero_arestas;
    int cresceu;

    int u;
    FILE *arq = fopen("dados.txt", "r");
    i = 0;

    fgets(entrada, 256, arq);
    if (arq != NULL)
    {
        for (i = 0; entrada[i] != '|'; i++)
        {
            buffer[i] = entrada[i];
        }

        numero_vertices = atoi(buffer);
        printf("Numero de vertices: %d\n", numero_vertices);
        i++;

        while (entrada[i] != '|')
        {
            printf("arestas: %c", entrada[i]);
            i++;
            j++;
        }
        i++;

        //i = 0;
        while (fgets(entrada, 256, arq) != NULL)
        {
            i++;
            printf("vertice: %c", entrada[i]);

            /* 
            for (j = 0; entrada[i] != '|'; i++, j++)
            {
                buffer[j] = entrada[i];
            }
            buffer[j] = '\0';
            numero_arestas = atoi(buffer);
            i++;

            printf("Numero de arestas: %d\n", numero_arestas);

 */
            break;
        }

        /* 
        for (i = 0; entrada[i] != '|'; i++)
        {
            buffer[i] = entrada[i];
        }

        numero_vertices = atoi(buffer);
        printf("Numero de vertices: %d\n", numero_vertices);
        i++;

        for (j = 0; entrada[i] != '|'; i++, j++)
        {
            buffer[j] = entrada[i];
        }
        buffer[j] = '\0';
        numero_arestas = atoi(buffer);
        i++;

        printf("Numero de arestas: %d\n", numero_arestas);
 */
    }

    grafo = inicializar(numero_vertices, numero_arestas);

    fclose(arq);
}
