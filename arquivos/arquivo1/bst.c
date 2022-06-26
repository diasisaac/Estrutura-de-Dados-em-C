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
	printf("[%d - %s] ", raiz->dado->codigo, raiz->dado->titulo);
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

tipo_dado *ler_dados()
{
	tipo_dado *novo = (tipo_dado *)malloc(sizeof(tipo_dado));
	//Em caracteres de tamanhho fixo eu tenho que:

	//Quando eu inicializei o struct já inicializou todos os campos, Quero dizer, quando eu aloco o espaço de um livro, eu já estou alocando o  espaco pra o título, auto, sbn...

	getchar();
	printf("Titulo: ");
	fgets(novo->titulo, 80, stdin);
	tirar_enter(novo->titulo); //Na linguagem C tem uma chatissezinha. QUando a gente faz a leitura pelo fgets, ele pega tudo inclusive o /n. Daí pra tirar isso a gente usa essa função criada.
	printf("Autor: ");
	fgets(novo->autor, 50, stdin);
	printf("Isbn: ");
	fgets(novo->isbn, 20, stdin);
	printf("Codigo: ");
	scanf("%d", &novo->codigo);
	return novo;
}

void tirar_enter(char *string)
{
	string[strlen(string) - 1] = '\0';
}

void salvar_arquivo(char *nome, arvore a)
{
	FILE *arq; // Isso é a definição do arquivo lógico, eu não manipulo dados físicos no disco, aqui eu manipulo uma abstração *arq

	//Aqui eu faço a ligação entre o arquivo lógico 'arq' e o físico que tá armazenado no caminho 'nome' do SO .

	//Se eu vou salvar um arquivo, eu vou abrir o modo de escrita "wb" que escreve por cima caso já exista ou se n existir vai ser criado.

	// Esse arquivo é escrito no modo binário porque a gente pode salvar uma quantidade de bytes sem indicar se e um inteiro, caracterer ou algo do tipo. A gente não passa a máscara de formatação pra trabalahr com tamanho fixo ou indicador de tamanho.

	arq = fopen(nome, "wb");

	/*
	 Antes de abrir verifica se foi aberto com sucesso, porque se a gente tentar abrir um arquivo e o sistema operacional negar, isso pode acontecer de a gente tentar abrir um arquivo:
	  
	numa área onde não temos permissão;
	em um dispositivo que tá cheio;
	arquivo protegido contra gravação;
	dispositivo somente leitura;
	*/

	if (arq != NULL) // Checa antes de tentar abrir o arquivo
	{
		salvar_auxiliar(a, arq); //Implementa o pre-order
		fclose(arq);			 //Sempre feche o arquivo
	}
}

void salvar_auxiliar(arvore raiz, FILE *arq) // Construindo o arquivo
{
	if (raiz != NULL)
	{
		//Primerio a gente escreve, o fwrite é no modo binário e é uma função de baixo nível, fwrite e fread

		//Passa as informações raiz->dado e a quantidade de bytes sizeof(tipo_dado), 1 que é dada pela multiplicação de sizeof(tipo_dado) * 1

		//Se isso fosse um array de livros de tamanho fixo, eu podia salvar em um comando só. sizeof(tipo_dado) * 100

		//Como é uma estrutura que usa alocação dinâmica, então não temos os dados em posições consecutivas. Eles estão espalhados pela memória, daí temos que seguir o encadedamento da árvore BST.

		//EU preciso salvar 1 por 1. Escolhi a ordem pre-order porquê? Porque ao salvar e reconstrui a árvore, eu vou ter ela na mesma estrutura. ISSO É VÁLIDO PRA BST

		//Na Vermelho e Preto e AVl não fica exatamente igual por causa das rotações, mas isso não é problema.
		fwrite(raiz->dado, sizeof(tipo_dado), 1, arq);
		salvar_auxiliar(raiz->esq, arq); //Depois vai pra esquerda
		salvar_auxiliar(raiz->dir, arq); //DDepois vai pra direita
	}
}

arvore carregar_arquivo(char *nome, arvore a)
{
	FILE *arq;				 // Aqui eu abro o arquivo no modo leitura "rb"
	arq = fopen(nome, "rb"); // Reconstruir a árvore, struct por struct
	tipo_dado *temp;		 // Aqui eu faço a leitura do OBJETO tipo_dado que foi salvo com tamanho fixo seguindo a ordem do percurso pre-order
	if (arq != NULL)		 // Vou reconstruir a árvore
	{
		//Pra copiar de uma struct do disco pra uma struct na memória RAM é preciso alocar espaço suficente pra recceber esses dados
		temp = (tipo_dado *)malloc(sizeof(tipo_dado));
		//Faço a leitura struct por struct, e não bloco por bloco de disco.

		//O fread dentro do while vai retornar falso quando não conseguir fazer a leitura.

		//Com isso eu garanto a leitura do primerio até o último. Porque do primeiro? Ao abrir um arquivo com "rb", arq = fopen(nome, "rb"), a gente já tá posicionado no ponto 0

		while (fread(temp, sizeof(tipo_dado), 1, arq))
		{
			//EU leio os dados pra dentro de temp e utilizo a função que já existia pra construir um nó 'a' na árvore pra apontar para temp e depois disso eu adiciono
			a = adicionar(temp, a);

			//Aí quando eu for ler o prṕximo dado eu tenho que ter uma nova área de memória pra não sobrescrever o 'temp'já lido.
			temp = (tipo_dado *)malloc(sizeof(tipo_dado));

			/*Então eu:
			
			1) crio uma nova área de memória
			   temp = (tipo_dado *)malloc(sizeof(tipo_dado));
			
			2) copio:
			   fread(temp, sizeof(tipo_dado), 1, arq)
			
			3) por fim adiciono na ávore que vai ter um nó ponteiro 'a' pra o novo carinha, o 'temp'.
				a = adicionar(temp, a);
			*/
		}
		fclose(arq); // Depois de sair da repetição a gente fecha o arquivo
	}
	return a;
}
