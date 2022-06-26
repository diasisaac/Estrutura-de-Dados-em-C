#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main(int argc, char *argv[])
{
	tabela tab;
	int opcao;
	inicializarTabela(&tab);

	while (1)
	{
		scanf("%d", &opcao);

		switch (opcao)
		{
			int valor;
		case 1:
			printf("%d\n", altura(tab.arvore_de_indices));
			break;
		case 2:
			adicionarLivro(&tab, ler_dados());
			break;
		case 3:
			printf("%d\n", maior_elemento(tab.arvore_de_indices));
			break;
		case 4:
			printf("%d\n", menor_elemento(tab.arvore_de_indices));
			break;
		case 5:
			pre_order(tab.arvore_de_indices, &tab);
			printf("\n");
			break;
		case 6:
			in_order(tab.arvore_de_indices, &tab);
			printf("\n");
			break;
		case 7:
			pos_order(tab.arvore_de_indices, &tab);
			printf("\n");
			break;

		case 10:
			salvar_indices("indices.txt", tab.arvore_de_indices);
			break;

		case 99:
			finalizar(&tab);
			exit(0);
		}
	}
}
