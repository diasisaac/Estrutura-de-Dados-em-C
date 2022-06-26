#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main(int argc, char *argv[])
{
	arvore a;
	int opcao;
	int controleFB;
	int diminuiu; // Controle se diminuiu

	int qtd_par, encontrou, valores_negativos;

	inicializar(&a);

	while (1)
	{
		scanf("%d", &opcao);

		switch (opcao)
		{
			int valor;

		case 1:
			scanf("%d", &valor);
			a = adicionar(valor, a, &controleFB);
			break;
		case 2:
			pre_order(a);
			printf("\n");
			break;
		case 3:
			in_order(a);
			printf("\n");
			break;
		case 4:
			pos_order(a);
			printf("\n");
			break;

		case 5:
			reverso(a);
			printf("\n");
			break;

		case 6:

			qtd_par = qtdPar(a);
			printf("%d\n", qtd_par);
			break;

		case 7:

			valores_negativos = checa_positivo(a);

			if (valores_negativos == 0) //Caso va
			{
				func_quadrado(a);
			}

			break;

		case 8:
			scanf("%d", &valor);
			encontrou = se_existe(a, valor);
			printf("%d\n", encontrou);
			break;

		case 9:
			scanf("%d", &valor);
			a = remover(a, valor, &diminuiu);
			//a = fiscal_de_fb_pos_rotacao(a);
			break;

		case 99:
			exit(0);
		}
	}
}
