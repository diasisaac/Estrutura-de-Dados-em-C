#include <stdio.h>
#include <stdlib.h>
#include "matriz_adj.h"

void inicializar(grafo *g, int tamanho)
{
	int i, j;
	g->v = tamanho;
	g->i_v = 0;
	g->mapa = (char *)malloc(sizeof(char) * tamanho);
	g->matriz = (int **)malloc(sizeof(int) * tamanho);
	for (i = 0; i < tamanho; i++)
		g->matriz[i] = (int *)malloc(sizeof(int) * tamanho);

	for (i = 0; i < tamanho; i++)
	{
		for (j = 0; j < tamanho; j++)
		{
			if (i == j)
			{
				g->matriz[i][j] = 1;
			}
			else
			{
				g->matriz[i][j] = 0;
			}
		}
	}
}

//Eu tenho um array e quero saber em qual posição um caracter está nesse array
int localizarVertice(grafo *grafo, char c)
{
	int encontrado = 0;
	int i;

	for (i = 0; i < grafo->v; i++)
	{
		if (grafo->mapa[i] == c)
		{
			encontrado = i;
			break;
		}
	}

	printf("Vertice %c localizado na posicao: %d\n", grafo->mapa[i], i);

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

	//Coloca a adjacencia
	grafo->matriz[posicao_aresta_a][posicao_aresta_b] = 1;
	grafo->matriz[posicao_aresta_b][posicao_aresta_a] = 1;

	printf("\n ** Adicionados na matriz ** \n");
}

void adicionarVertice(grafo *grafo, char vertice)
{

	if (grafo->i_v < grafo->v)
	{
		//Isso aqui já enumera com os indices e os valores do array

		//Coloca o caracter dentro do mapa na posicao i_v
		grafo->mapa[grafo->i_v] = vertice;

		printf("Vertice %c adicionado na posicao: %d\n", grafo->mapa[grafo->i_v], grafo->i_v);

		grafo->i_v++;
	}
}

void imprimir_matriz(grafo *g)
{
	int i, j;

	printf("\n**** IMPRIMINDO A MATRIZ DE ADJACENCIAS ****\n");

	for (i = 0; i < g->v; i++)
	{

		for (j = 0; j < g->v; j++)
		{
			printf("%d ", g->matriz[i][j]);
		}
		printf("\n");
	}

	printf("************ \n");
}

void carregar_arquivo(char *nome, grafo *grafo)
{
	printf("Carregando...\n");
	FILE *arq;

	int num_vert, num_ares;
	int i = 0;
	char buffer[20];

	arq = fopen(nome, "r");

	fscanf(arq, "%d %d", &num_vert, &num_ares);

	printf("Num vert: %d | ver arest: %d |\n", num_vert, num_ares);

	inicializar(grafo, num_vert);

	for (i = 0; i < num_vert; i++)
	{
		fscanf(arq, "%s", buffer);

		printf("\nLENDO: Vertices: %c\n", buffer[0]);

		adicionarVertice(grafo, buffer[0]);
	}

	for (i = 0; i < num_ares; i++)
	{
		fscanf(arq, "%s", buffer);

		printf("\n LEU: %c || %c\n", buffer[0], buffer[1]);

		adicionarAresta(grafo, buffer[0], buffer[1]);
	}

	fclose(arq);
}
