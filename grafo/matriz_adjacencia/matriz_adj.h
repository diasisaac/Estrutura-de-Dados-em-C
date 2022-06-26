#ifndef GRAFO_H
#define GRAFO_H

typedef struct grafo
{
	int v;
	int i_v;
	char *mapa;
	int **matriz;
} grafo;

void inicializar(grafo *g, int tamanho);

void imprimir_matriz(grafo *g);

void adicionarAresta(grafo *g, char v1, char v2);

void adicionarVertice(grafo *grafo, char vertice);

int localizarVertice(grafo *grafo, char c);

#endif
