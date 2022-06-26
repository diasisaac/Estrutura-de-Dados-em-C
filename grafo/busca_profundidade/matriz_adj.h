#ifndef GRAFO_H
#define GRAFO_H

typedef struct grafo
{
	int v;
	int i_v;
	char *mapa;
	int **matriz;
} grafo;

typedef struct vetores_grafo
{
	struct grafo grafo;
	char *vetor_cor;
	int *vetor_ditancia;
	int *vetor_pai;
	int *vetor_fim;
	int tempo;
} vetores_grafo;

void inicializar(grafo *g, int tamanho);

void inicializa_vetores(grafo *grafo, vetores_grafo *vetores_grafo);

void imprimir_matriz(grafo *g);

void adicionarAresta(grafo *g, char v1, char v2);

void adicionarVertice(grafo *grafo, char vertice);

int localizarVertice(grafo *grafo, char c);

void dfs(grafo *grafo, vetores_grafo *vetores_grafo);

void dfs_visit(grafo *grafo, int u, vetores_grafo *vetores_grafo, int *tempo);

void imprimir_busca(grafo *g, vetores_grafo *vetores_grafo);

void carregar_arquivo(char *nome, grafo *g);
#endif
