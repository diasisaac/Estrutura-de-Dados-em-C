#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include <string.h>

void inicializar(arvore *raiz)
{
	*raiz = NULL;
}

arvore adicionar(tipo_dado *valor, arvore raiz)
{
	if (raiz == NULL)
	{
		arvore novo = (arvore)malloc(sizeof(struct no_bst));
		novo->dado = valor;
		novo->esq = NULL;
		novo->dir = NULL;
		return novo;
	}

	if (valor->codigo > raiz->dado->codigo)
	{
		raiz->dir = adicionar(valor, raiz->dir);
	}
	else
	{
		raiz->esq = adicionar(valor, raiz->esq);
	}
	return raiz;
}

int altura(arvore raiz)
{
	if (raiz == NULL)
	{
		return 0;
	}
	return 1 + maior(altura(raiz->dir), altura(raiz->esq));
}

int maior(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

tipo_dado *maior_elemento(arvore raiz)
{
	if (raiz == NULL)
		return NULL;
	if (raiz->dir == NULL)
		return raiz->dado;
	else
		return maior_elemento(raiz->dir);
}

tipo_dado *menor_elemento(arvore raiz)
{
	if (raiz == NULL)
		return NULL;
	if (raiz->esq == NULL)
		return raiz->dado;
	else
		return maior_elemento(raiz->esq);
}

void pre_order(arvore raiz)
{
	if (raiz != NULL)
	{
		imprimir_elemento(raiz);
		pre_order(raiz->esq);
		pre_order(raiz->dir);
	}
}

void pos_order(arvore raiz)
{
	if (raiz != NULL)
	{
		pos_order(raiz->esq);
		pos_order(raiz->dir);
		imprimir_elemento(raiz);
	}
}

void in_order(arvore raiz)
{
	if (raiz != NULL)
	{
		in_order(raiz->esq);
		imprimir_elemento(raiz);
		in_order(raiz->dir);
	}
}

void imprimir_elemento(arvore raiz)
{
	printf("%s | %s | %s | %d \n", raiz->dado->titulo, raiz->dado->autor, raiz->dado->isbn, raiz->dado->codigo);
}

arvore remover(int valor, arvore raiz)
{
	if (raiz == NULL)
		return NULL;

	if (raiz->dado->codigo == valor)
	{
		if (raiz->esq == NULL)
		{
			return raiz->dir;
		}
		if (raiz->dir == NULL)
		{
			return raiz->esq;
		}
		raiz->dado = maior_elemento(raiz->esq);
		raiz->esq = remover(raiz->dado->codigo, raiz->esq);
		return raiz;
	}
	if (valor > raiz->dado->codigo)
	{
		raiz->dir = remover(valor, raiz->dir);
	}
	else
	{
		raiz->esq = remover(valor, raiz->esq);
	}
	return raiz;
}

//***********ABAIXO TRABALHA COM ARQUIVOS *********

tipo_dado *ler_dados()
{
	//Quando eu aloco espaço pra um livro quando uso caracteres de tamanho variável na struct livro, eu aloco espaço pra ponteiiro
	tipo_dado *novo = (tipo_dado *)malloc(sizeof(tipo_dado));

	//EU definio um buffer de tamanho grande
	char *buffer = (char *)malloc(256 * sizeof(char));

	getchar();
	printf("Titulo: ");

	//Pra ler o titulo eu coloco dentro do buffer
	fgets(buffer, 255, stdin);

	//Retiro o enter do buffer
	tirar_enter(buffer);

	/*	novo->titulo = (char *) malloc ((strlen(buffer) + 1) * sizeof(char));
	strcpy(novo->titulo, buffer);*/

	novo->titulo = strdup(buffer); // A função strdup(buffer) já reserva espaço e faz a cópia.

	// 1) Descubriu quantas letras foram digitadas
	// 2) Reserva o espaço EXATO
	// 3) Faz a cópia

	/*Quando foi feita reserva do espaço e feita a cópia

	novo->titulo = strdup(buffer);
	
	EU disse: 
	
	Agora eu vou copiar, vou criar uma área de tamanho específico,
	
	 Se eu reservei 256 caracteres e usei somente 5, então a partir do buffer grande (256) caracteres, eu faço uma cópia somente doque eu usei, ou seja, só oque pessoa digitou(5 caracteres). Pra depois usar o restante do buffer, 249 caracteres, pra ler o próximo campo.
******
	 Manualmente, eu sei quantos caracteres foram digitados através do strlen(buffer), e sei que a linguagem C requer um terminador \0, por isso o +1. stlen(buffer) + 1. 

	novo->titulo = (char *) malloc ((strlen(buffer) + 1) * sizeof(char));

	Reserva, e depois eu copio.

	strcpy(novo->titulo, buffer);

	OU eu faço a atribuição do novo->titulo com a função strdup()

	novo->titulo = strdup(buffer) 

	Pois já implemnta esse 2 passos em uma chamada só.

******

	 Eu não posso reservar o tamaho exato antes der ler no fgets porque eu não faço ideia de quantos caracteres a pessoa vai digitar pra o título e nem vou ficar perguntando porque isso é chato.

	 Por isso que a gente usa o buffer, uma área grande, é pra o usuário digitar à vontade porque a gente vai saber quantos caracteres ele digitou, logo a gente reserva exatamente essa quantidade e depois copia isso pra dentro do buffer original porque assim o resto do espaço que sobrar dentro desse buffer original vai servir pra os outros campos.

	 Pra quando completar esse buffer toda a informação vai ser armazenada dentro do disco.

	*/

	printf("Autor: ");

	//Depois de fazer a cópia eu reutilizo O MESMO BUFFER pra receber as informações do próximo campo
	fgets(buffer, 255, stdin);

	tirar_enter(buffer);
	novo->autor = strdup(buffer);

	printf("Isbn: ");
	fgets(buffer, 255, stdin);
	tirar_enter(buffer);
	novo->isbn = strdup(buffer);

	printf("Codigo: ");
	scanf("%d", &novo->codigo);

	/*
	Quando chega aqui, aquele buffer usado pra fazer as operações já não é mais necessário, então eu libero o espaço dele da memória. Isso torna a função extremamente eficiente quanto ao uso da memória RAM
	*/
	free(buffer);

	return novo;
}

void tirar_enter(char *string)
{
	string[strlen(string) - 1] = '\0';
}

void salvar_arquivo(char *nome, arvore a)
{
	FILE *arq;
	//arq = fopen(nome, "wb");
	arq = fopen(nome, "w");

	if (arq != NULL)
	{
		salvar_auxiliar(a, arq);
		fclose(arq);
	}
}

void salvar_auxiliar(arvore raiz, FILE *arq)
{
	if (raiz != NULL)
	{
		fprintf(arq, "%s|%s|%s|%d|\n", raiz->dado->titulo, raiz->dado->autor, raiz->dado->isbn, raiz->dado->codigo);

		//fwrite(raiz->dado, sizeof(tipo_dado), 1, arq);
		salvar_auxiliar(raiz->esq, arq);
		salvar_auxiliar(raiz->dir, arq);
	}
}

arvore carregar_arquivo(char *nome, arvore a)
{
	printf("Carregando...\n");

	char entrada[256];
	char buffer[256];
	int codigo;
	int i, j;

	FILE *arq = fopen(nome, "r");
	tipo_dado *temp;

	if (arq != NULL)
	{
		temp = (tipo_dado *)malloc(sizeof(tipo_dado));

		while (fgets(entrada, 256, arq) != NULL)
		{

			for (i = 0; entrada[i] != '|'; i++)
			{
				buffer[i] = entrada[i];
				//printf("%c", entrada[i]);
			}
			//printf("|");
			buffer[i] = '\0';
			temp->titulo = strdup(buffer);

			i++;

			for (j = 0; entrada[i] != '|'; j++, i++)
			{
				buffer[j] = entrada[i];
				//	printf("%c", entrada[i]);
			}
			//printf("|");
			buffer[j] = '\0';
			temp->autor = strdup(buffer);

			i++;

			for (j = 0; entrada[i] != '|'; j++, i++)
			{
				buffer[j] = entrada[i];
				//	printf("%c", entrada[i]);
			}
			//printf("|");

			buffer[j] = '\0';
			temp->isbn = strdup(buffer);

			i++;

			for (j = 0; entrada[i] != '|'; j++, i++)
			{
				buffer[j] = entrada[i];
				//	printf("%d", entrada[i]);
			}
			//printf("|");

			buffer[j] = '\0';
			temp->codigo = atoi(buffer);

			printf("Titulo: %s\n", temp->titulo);
			printf("Autor: %s\n", temp->autor);
			printf("isdbn: %s\n", temp->isbn);
			printf("Codigo: %d\n", temp->codigo);
			printf("\n");

			a = adicionar(temp, a);

			temp = (tipo_dado *)malloc(sizeof(tipo_dado));
		}

		fclose(arq);
	}

	return a;
}
