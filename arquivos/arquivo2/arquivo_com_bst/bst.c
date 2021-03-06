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
	//Quando eu aloco espa??o pra um livro quando uso caracteres de tamanho vari??vel na struct livro, eu aloco espa??o pra ponteiiro
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

	novo->titulo = strdup(buffer); // A fun????o strdup(buffer) j?? reserva espa??o e faz a c??pia.

	// 1) Descubriu quantas letras foram digitadas
	// 2) Reserva o espa??o EXATO
	// 3) Faz a c??pia

	/*Quando foi feita reserva do espa??o e feita a c??pia

	novo->titulo = strdup(buffer);
	
	EU disse: 
	
	Agora eu vou copiar, vou criar uma ??rea de tamanho espec??fico,
	
	 Se eu reservei 256 caracteres e usei somente 5, ent??o a partir do buffer grande (256) caracteres, eu fa??o uma c??pia somente doque eu usei, ou seja, s?? oque pessoa digitou(5 caracteres). Pra depois usar o restante do buffer, 249 caracteres, pra ler o pr??ximo campo.
******
	 Manualmente, eu sei quantos caracteres foram digitados atrav??s do strlen(buffer), e sei que a linguagem C requer um terminador \0, por isso o +1. stlen(buffer) + 1. 

	novo->titulo = (char *) malloc ((strlen(buffer) + 1) * sizeof(char));

	Reserva, e depois eu copio.

	strcpy(novo->titulo, buffer);

	OU eu fa??o a atribui????o do novo->titulo com a fun????o strdup()

	novo->titulo = strdup(buffer) 

	Pois j?? implemnta esse 2 passos em uma chamada s??.

******

	 Eu n??o posso reservar o tamaho exato antes der ler no fgets porque eu n??o fa??o ideia de quantos caracteres a pessoa vai digitar pra o t??tulo e nem vou ficar perguntando porque isso ?? chato.

	 Por isso que a gente usa o buffer, uma ??rea grande, ?? pra o usu??rio digitar ?? vontade porque a gente vai saber quantos caracteres ele digitou, logo a gente reserva exatamente essa quantidade e depois copia isso pra dentro do buffer original porque assim o resto do espa??o que sobrar dentro desse buffer original vai servir pra os outros campos.

	 Pra quando completar esse buffer toda a informa????o vai ser armazenada dentro do disco.

	*/

	printf("Autor: ");

	//Depois de fazer a c??pia eu reutilizo O MESMO BUFFER pra receber as informa????es do pr??ximo campo
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
	Quando chega aqui, aquele buffer usado pra fazer as opera????es j?? n??o ?? mais necess??rio, ent??o eu libero o espa??o dele da mem??ria. Isso torna a fun????o extremamente eficiente quanto ao uso da mem??ria RAM
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
