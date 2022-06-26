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

	grafo->matriz[posicao_aresta_a][posicao_aresta_b] = 1;
	grafo->matriz[posicao_aresta_b][posicao_aresta_a] = 1;
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

	for (i = 0; i < g->v; i++)
	{

		for (j = 0; j < g->v; j++)
		{
			printf("%d ", g->matriz[i][j]);
		}
		printf("\n");
	}
}

int main(int argc, int *argv)
{
	grafo g;

	inicializar(&g, 4);

	adicionarVertice(&g, 'd');

	adicionarVertice(&g, 'a');

	adicionarVertice(&g, 'i');

	adicionarVertice(&g, 'l');

	adicionarAresta(&g, 'a', 'd');

	adicionarAresta(&g, 'a', 'i');

	adicionarAresta(&g, 'd', 'l');

	adicionarAresta(&g, 'i', 'd');

	imprimir_matriz(&g);
}
