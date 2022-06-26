#include <stdio.h>
#include <stdlib.h>
#include "matriz_adj.h"

int main(int argc, int *argv)
{
	grafo g;

	vetores_grafo vetores_grafo;

	carregar_arquivo("dados.txt", &g);

	inicializa_vetores(&g, &vetores_grafo);

	imprimir_matriz(&g);

	dfs(&g, &vetores_grafo);

	imprimir_busca(&g, &vetores_grafo);
	return 0;
}