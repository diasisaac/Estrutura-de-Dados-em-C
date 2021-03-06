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

	//Quando eu inicializei o struct j?? inicializou todos os campos, Quero dizer, quando eu aloco o espa??o de um livro, eu j?? estou alocando o  espaco pra o t??tulo, auto, sbn...

	getchar();
	printf("Titulo: ");
	fgets(novo->titulo, 80, stdin);
	tirar_enter(novo->titulo); //Na linguagem C tem uma chatissezinha. QUando a gente faz a leitura pelo fgets, ele pega tudo inclusive o /n. Da?? pra tirar isso a gente usa essa fun????o criada.
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
	FILE *arq; // Isso ?? a defini????o do arquivo l??gico, eu n??o manipulo dados f??sicos no disco, aqui eu manipulo uma abstra????o *arq

	//Aqui eu fa??o a liga????o entre o arquivo l??gico 'arq' e o f??sico que t?? armazenado no caminho 'nome' do SO .

	//Se eu vou salvar um arquivo, eu vou abrir o modo de escrita "wb" que escreve por cima caso j?? exista ou se n existir vai ser criado.

	// Esse arquivo ?? escrito no modo bin??rio porque a gente pode salvar uma quantidade de bytes sem indicar se e um inteiro, caracterer ou algo do tipo. A gente n??o passa a m??scara de formata????o pra trabalahr com tamanho fixo ou indicador de tamanho.

	arq = fopen(nome, "wb");

	/*
	 Antes de abrir verifica se foi aberto com sucesso, porque se a gente tentar abrir um arquivo e o sistema operacional negar, isso pode acontecer de a gente tentar abrir um arquivo:
	  
	numa ??rea onde n??o temos permiss??o;
	em um dispositivo que t?? cheio;
	arquivo protegido contra grava????o;
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
		//Primerio a gente escreve, o fwrite ?? no modo bin??rio e ?? uma fun????o de baixo n??vel, fwrite e fread

		//Passa as informa????es raiz->dado e a quantidade de bytes sizeof(tipo_dado), 1 que ?? dada pela multiplica????o de sizeof(tipo_dado) * 1

		//Se isso fosse um array de livros de tamanho fixo, eu podia salvar em um comando s??. sizeof(tipo_dado) * 100

		//Como ?? uma estrutura que usa aloca????o din??mica, ent??o n??o temos os dados em posi????es consecutivas. Eles est??o espalhados pela mem??ria, da?? temos que seguir o encadedamento da ??rvore BST.

		//EU preciso salvar 1 por 1. Escolhi a ordem pre-order porqu??? Porque ao salvar e reconstrui a ??rvore, eu vou ter ela na mesma estrutura. ISSO ?? V??LIDO PRA BST

		//Na Vermelho e Preto e AVl n??o fica exatamente igual por causa das rota????es, mas isso n??o ?? problema.
		fwrite(raiz->dado, sizeof(tipo_dado), 1, arq);
		salvar_auxiliar(raiz->esq, arq); //Depois vai pra esquerda
		salvar_auxiliar(raiz->dir, arq); //DDepois vai pra direita
	}
}

arvore carregar_arquivo(char *nome, arvore a)
{
	FILE *arq;				 // Aqui eu abro o arquivo no modo leitura "rb"
	arq = fopen(nome, "rb"); // Reconstruir a ??rvore, struct por struct
	tipo_dado *temp;		 // Aqui eu fa??o a leitura do OBJETO tipo_dado que foi salvo com tamanho fixo seguindo a ordem do percurso pre-order
	if (arq != NULL)		 // Vou reconstruir a ??rvore
	{
		//Pra copiar de uma struct do disco pra uma struct na mem??ria RAM ?? preciso alocar espa??o suficente pra recceber esses dados
		temp = (tipo_dado *)malloc(sizeof(tipo_dado));
		//Fa??o a leitura struct por struct, e n??o bloco por bloco de disco.

		//O fread dentro do while vai retornar falso quando n??o conseguir fazer a leitura.

		//Com isso eu garanto a leitura do primerio at?? o ??ltimo. Porque do primeiro? Ao abrir um arquivo com "rb", arq = fopen(nome, "rb"), a gente j?? t?? posicionado no ponto 0

		while (fread(temp, sizeof(tipo_dado), 1, arq))
		{
			//EU leio os dados pra dentro de temp e utilizo a fun????o que j?? existia pra construir um n?? 'a' na ??rvore pra apontar para temp e depois disso eu adiciono
			a = adicionar(temp, a);

			//A?? quando eu for ler o pr???ximo dado eu tenho que ter uma nova ??rea de mem??ria pra n??o sobrescrever o 'temp'j?? lido.
			temp = (tipo_dado *)malloc(sizeof(tipo_dado));

			/*Ent??o eu:
			
			1) crio uma nova ??rea de mem??ria
			   temp = (tipo_dado *)malloc(sizeof(tipo_dado));
			
			2) copio:
			   fread(temp, sizeof(tipo_dado), 1, arq)
			
			3) por fim adiciono na ??vore que vai ter um n?? ponteiro 'a' pra o novo carinha, o 'temp'.
				a = adicionar(temp, a);
			*/
		}
		fclose(arq); // Depois de sair da repeti????o a gente fecha o arquivo
	}
	return a;
}
