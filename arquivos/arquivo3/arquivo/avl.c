#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include "avl.h"
#include <string.h>

void inicializar(arvore *raiz)
{
	*raiz = NULL;
}

int inicializarTabela(tabela *tab)
{

	//tab->arquivo_dados GUARDA AS INFORMAÇÕES COMPLETAS DOS LIVRO
	//tab->arvore_de_indices GUARDA A POSICAO DO LIVRO NO ARQUIVO ( INDICE ) E A CHAVE ( O CODIGO DO LIVRO)

	inicializar(&tab->arvore_de_indices);
	tab->arquivo_dados = fopen("dados.txt", "a+b");
	tab->arvore_de_indices = carregar_arquivo("indices.txt", tab->arvore_de_indices);
	if (tab->arquivo_dados != NULL)
		return 1;
	else
		return 0;
}

// ***************** EEIII !! OBSERVE QUE OS INDICES SÃO SALVOS AQUI***********
void finalizar(tabela *tab)
{
	fclose(tab->arquivo_dados);
	//salvar_indices("indices.txt", tab->arvore_de_indices); //Deixei comentado pra salvear só quando mandar
}

/*

Adicionar um livro agora consiste em 2 etapas

1 - adicionar as informações completas no arquivo
2 - salvar a chave no índice

A cada adicionar já manda pra o arquivo
*/
void adicionarLivro(tabela *tab, dado *livro)
{
	int cresceu;
	//tab->arquivo_dados GUARDA AS INFORMAÇÕES COMPLETAS DOS LIVRO
	//tab->arvore_de_indices GUARDA A POSICAO DO LIVRO NO ARQUIVO E O SEU INDICE ( O CODIGO DO LIVRO)
	if (tab->arquivo_dados != NULL) //Ve se foi aberto pra poder manipular
	{
		//Vou salvar lá no final do arquivo
		fseek(tab->arquivo_dados, 0L, SEEK_END);

		/* A função fseek salta dentro do arquivo, configura o ponteiro, a referencia. Não opera no disco, só aponta. 

		Eu configurei o ponteiro tab->arquivo_dados pra apontar pra primeira posição a partir do final do disco. Mas eu ainda não sei qual é a posição númerica. Só estou lá.

		Daí vou precisar da função ftell pra poder me dizer qual é a posição númerica.

		Vou salta pra posição 0 ( 0L ) a partir do fim( SEEK_END ).
		*/

		tipo_dado *novo = (tipo_dado *)malloc(sizeof(tipo_dado));

		/* A função ftell me diz qual é a posição apontada no disco pelo ponteiro 
		tab->arquivo_dados e vai guardar isso no indice
			
		
		Ela vai pegar o arquivo e indicar qual a posicao do curso daquele arquivo.

		Se eu saltei pra o fim do arquivo, então a posição apontada vai ser a do último registro.

		A função ftell descobre qual é a posição.
		*/

		/*
			Os 2 elementos que formam a estrutura de dados do indíce são:

			chave
			-  que foi pegada na função ler registro como vemos em livro->codigo.

			novo->chave = livro->codigo;

			E a posição do indice
			-  que peguei a partir da posição onde ele vai ser armazenado lá do arquivo.

			novo->indice = ftell(tab->arquivo_dados);

			A PARTE DO FTELL, FSEEK E O NÓ NOVO, que guarda a chave e o indice do livro salvo no arquivo É PRA SER GGUARDADO NA ÁRVORE QUE FICA NA MEMÓRIA RAM
		*/

		//O struct de dado satélites em sizeof(dado) vai ser escrita no arquivo de dados de nome livro e vai salvar na posição final apontada por tab->arquivo_dados regida pela função seek.

		//Essa operação manipula a estrutura na árvore da memória RAM para o arquivo no disco.

		//SÓ PRECISA MODIFICAR AQUI PRA IMPLEMENTAR COM A SEPARAÇÃO DE CAMPOS
		//PEA AQUELA PARTE DO FOR LÁ OU FAZ UMA FUNCAO BEM ENCAPSULADA E CHAMA AQUI

		//fwrite(livro, sizeof(dado), 1, tab->arquivo_dados);

		//Leia com separacao de campos a ordem : titulo | autor | isbn | codigo

		fprintf(tab->arquivo_dados, "%s|%s|%s|%d|\n", livro->titulo, livro->autor, livro->isbn, livro->codigo);

		//	Daqui pra baixo salva na árvpre o indice e a chave do lviro que vai ser lido em outra funcao

		novo->chave = livro->codigo;
		novo->indice = ftell(tab->arquivo_dados);

		//Agora, as informações de posição do indice e a chave, armazenadas em tipo_dado *novo, vão ser adicionadas na árvore de índices.

		/*O struct novo com as informações da chave (codigo do livro) e indice da posicao buscada no arquivo
		
		função ftell(tab->arquivo_dados) 
		
		que já foi salvo do livro atual como vemos em fscanf(...) aqui em cima  
		
		vão ser adicionadox na árvore tab->arvore_de_indices

		*/

		//Essas informações de chave e indice serão salvadas na próxima linha na memória RAM que posteriormente na função salvar_elemento() serão salvadas em um arquvio chamado indicex.txt  que está no disco e ...

		//Essa operação manipula a estrutura na árvore que está na memória RAM.
		// O ADICIONAR PRA SUBSTITUIR A BST É SO CHAMAR O ADCIONAR DA ARVORE QUE VAI USAR

		cresceu = 1;
		tab->arvore_de_indices = adicionar(novo, tab->arvore_de_indices, &cresceu);

		novo = (tipo_dado *)malloc(sizeof(tipo_dado));
	}
}

arvore adicionar(tipo_dado *valor, arvore raiz, int *cresceu)
{
	//Caso base da recursão: ou a árvore está vazia ou chegou em uma folha
	if (raiz == NULL)
	{
		arvore novo = (arvore)malloc(sizeof(struct no_avl));
		novo->dado = valor;
		novo->esq = NULL;
		novo->dir = NULL;
		novo->fb = 0; // Quando insere sempre o fator de balanco é 0
		*cresceu = 1; // Porque na subárvore onde foi inserido cresceu
		return novo;
	}

	//Casos recursivos, se a raiz (relativa) não for NULL,
	//acrescenta-se o elemento na sub-árvore direita ou esquerda,
	//dependendo do valor a ser inserido. Elementos maiores vão
	//para direita, menores para esquerda.
	if (valor > raiz->dado)
	{
		//Elemento maior => adicionar na direita
		raiz->dir = adicionar(valor, raiz->dir, cresceu);
		//Após adicionar o elemento na direita,
		//verifica se a sub-árvore da direita cresceu.
		//Em caso afirmativo, ajusta-se o fator de balanço
		//da raiz relativa
		if (*cresceu)
		{
			//Chegando neste ponto, sabe se que:
			//a) O elemento foi inserido na sub-árvore direita; e
			//b) A sub-árvore a direita cresceu
			switch (raiz->fb)
			{
			case 0:
				raiz->fb = 1;
				*cresceu = 1;
				break;
			case -1:
				raiz->fb = 0;
				*cresceu = 0;
				break;
			case 1:
				*cresceu = 0;
				//o fator de balanço passaria ao valor 2,
				return rotacionar(raiz);
			}
		}
	}
	else
	{
		//Elemento menor que raiz relativa, fazer o caso simétrico
		raiz->esq = adicionar(valor, raiz->esq, cresceu);

		if (*cresceu)
		{
			switch (raiz->fb)
			{
			case 0:

				raiz->fb = -1;
				*cresceu = 1;
				break;
			case 1:
				raiz->fb = 0;
				*cresceu = 0;
				break;

			case -1:
				*cresceu = 0;
				return rotacionar(raiz);
				break;
			}
		}
	}
	//Se tirar isso, caga a árvore toda
	return raiz;
}

/*----------
Verifica o tipo de rotação que deve ser aplicado para reajustar a árvore
Parâmetros:
    raiz - pivô (ou raiz da sub-árvore que se encontra 
    com o |fb| = 2 ) 
Retorno:
    raiz da sub-árvore resultante
---*/
arvore rotacionar(arvore raiz)
{
	//fb maior que zero => rotação para a esquerda porque a subárvore da direita tem mais "peso"
	if (raiz->fb > 0)
	{
		switch (raiz->dir->fb)
		{
		//o zero "conta" como rotação simples.
		//Só ocorre no remover
		case 0:
		case 1: // Mesmo sinal do filho direito, rotação simples para a esquerda pra balancear
			return rotacao_simples_esquerda(raiz);
		case -1: // SInal diferente do filho direito, dispara a rotação dupla pra balancear
			return rotacao_dupla_esquerda(raiz);
		}
	}
	else
	{
		//printf("Quando fb(raiz) < 0 : raiz->fb = %d\n", raiz->fb);
		//implementar o simétrico
		switch (raiz->esq->fb) // Olha o filho esquerdo dela
		{
		case -1:
			return rotacao_simples_direita(raiz);

		case 0: //Sinal positivo, o sinal tá diferente, dispara a rotação dupla para a direita
		case 1:
			return rotacao_dupla_direita(raiz);
		}
	}
}

arvore fiscal_de_fb_pos_rotacao(arvore raiz_nutella) //Vai checar se tem alguma raiz nutella, isto é, com um fb +- 2 depois da rotacao haha pq não é raiz raiz
{
	if (raiz_nutella != NULL)
	{
		if ((raiz_nutella->fb >= 2) || (raiz_nutella->fb <= 2))
		{
			raiz_nutella = rotacionar(raiz_nutella);
		}

		fiscal_de_fb_pos_rotacao(raiz_nutella->esq);
		fiscal_de_fb_pos_rotacao(raiz_nutella->dir);
	}
}

/*-------
Realiza a rotação simples esquerda sobre o pivô "raiz" e 
retorna a raiz relativa da árvore resultante 

      p
     / \
    t1  u
       / \
      t2 t3

     =>

      u
     / \
    p  t3
   / \
  t1 t2


-------*/
arvore rotacao_simples_esquerda(arvore raiz)
{
	arvore p, u, t1, t2, t3;
	//inicializa os ponteiros
	p = raiz;
	u = raiz->dir;
	t1 = p->esq;
	//t2 e t3 não estão sendo modificados.
	//só estão aqui por questões didáticas
	t2 = u->esq;
	t3 = u->dir;

	//Atualiza os ponteiros
	p->dir = t2;
	u->esq = p;

	//Atualiza os fatores de balanço de acordo com o fb de u
	//Esses valores vieram dos cálculos demonstrados na aula
	//printf("u = %d, fb(u) = %d", u->dado, u->fb);
	if (u->fb == 1)
	{
		p->fb = 0;
		u->fb = 0;
	}
	else
	{
		p->fb = 1;
		u->fb = -1;
	}

	//Retorna a raiz da sub-árvore resultante, ou seja "u".
	return u;
}

arvore rotacao_dupla_esquerda(arvore raiz)
{

	/*//AO fazer desse modo tinha erro no fator de balaco
	raiz->dir = rotacao_simples_direita(raiz->dir);
	raiz = rotacao_simples_esquerda(raiz);
	return raiz;
	
	*/
	arvore p, u, v, t1, t2, t3, t4;

	p = raiz;
	u = raiz->dir;
	v = u->esq;
	t2 = v->esq;
	t3 = v->dir;

	//Só estão aqui por questões didáticas
	t1 = p->esq;
	t4 = u->dir;

	//Atualiza os ponteiros
	u->esq = t3;
	p->dir = t2;
	v->esq = p;
	v->dir = u;

	if (u->fb == -1)
	{
		u->fb = 0;
		p->fb = -1;
		v->fb = 0;
	}

	return v;
}

/*-------
Realiza a rotação simples direita sobre o pivô "raiz" e 
retorna a raiz relativa da árvore resultante 

      p
     / \
    u  t3
   / \
  t1 t2
	
     =>

      u
     / \
	t1	p  
  	   / \
	  t2 t3


-------*/
arvore rotacao_simples_direita(arvore raiz)
{
	arvore p, u, t1, t2, t3;

	p = raiz;
	u = raiz->esq;
	t3 = p->dir;
	t1 = u->esq;
	t2 = u->dir;

	//Atualiza os ponteiros

	p->esq = t2;
	u->dir = p;

	if (u->fb == -1)
	{
		p->fb = 0;
		u->fb = 0;
	}

	return u;
}
arvore rotacao_dupla_direita(arvore raiz)
{
	arvore p, u, v, t1, t2, t3, t4;

	p = raiz;
	u = raiz->esq;
	v = u->dir;

	t1 = u->esq; // Nao muda
	t2 = v->esq;
	t3 = v->dir;
	t4 = p->dir; // Nao muda

	//Atualia os ponteiros
	u->dir = t2;
	p->esq = t3;
	v->dir = p;
	v->esq = u;

	if (u->fb == 1)
	{
		u->fb = 0;
		p->fb = 0;
		v->fb = 0;
	}

	return v;
}

// FIM DE ADICIONAR A ARVORE AVL

int altura(arvore raiz)
{
	if (raiz == NULL)
	{
		return 0;
	}
	return 1 + maior(altura(raiz->dir), altura(raiz->esq));
}

FILE *procurarLivro(tabela *tab, int chave)
{
	if (tab->arquivo_dados != NULL)
	{
		no_avl *temp;
		temp = tab->arvore_de_indices;

		while (temp != NULL)
		{
			if (temp->dado->chave == chave)
			{
				//dado *encontrado = (dado *)malloc(sizeof(dado));
				fseek(tab->arquivo_dados, temp->dado->indice, SEEK_SET);
				//fread(encontrado, sizeof(dado), 1, tab->arquivo_dados);
				printf("Encontrou\n");
				return tab->arquivo_dados;
			}
			else
			{
				if (chave > temp->dado->chave)
					temp = temp->dir;
				else
					temp = temp->esq;
			}
		}
	}
	return NULL;
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

void pre_order(arvore raiz, tabela *tab)
{
	if (raiz != NULL)
	{
		imprimir_elemento(raiz, tab);
		pre_order(raiz->esq, tab);
		pre_order(raiz->dir, tab);
	}
}

void pos_order(arvore raiz, tabela *tab)
{
	if (raiz != NULL)
	{
		pos_order(raiz->esq, tab);
		pos_order(raiz->dir, tab);
		imprimir_elemento(raiz, tab);
	}
}

void in_order(arvore raiz, tabela *tab)
{
	if (raiz != NULL)
	{
		in_order(raiz->esq, tab);
		imprimir_elemento(raiz, tab);
		in_order(raiz->dir, tab);
	}
}

//Na hora de imprimir elemento eu vou ter que buscar as informações no meu arquivo que está no disco
void imprimir_elemento(arvore raiz, tabela *tab)
{
	char entrada[256];
	char buffer[256];
	int codigo;
	int i, j;

	printf("\nEntrou em imprimir\n");
	//ACREIDTO QUE AQUI VAI CHAMAR A FUNCAO PROCURAR LIVRO E SALVAR ESSAS INFOMRÇÃOES NA STRUCT dado *livro criada aqui em baixo

	//Pra buscar as informações que estão no arquivo eu preciso reservar espaço de memória
	dado *temp = (dado *)malloc(sizeof(dado));

	printf("\nProcurando pelo elemento de chave: %d\n", raiz->dado->chave);

	tab->arquivo_dados = procurarLivro(tab, raiz->dado->chave);

	while (fgets(entrada, 256, tab->arquivo_dados) != NULL)
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
		printf("\n*** IMPRIMINDO ***\n");
		printf("Titulo: %s\n", temp->titulo);
		printf("Autor: %s\n", temp->autor);
		printf("isdbn: %s\n", temp->isbn);
		printf("Codigo: %d\n", temp->codigo);
		printf("\n");
	}

	printf("\nSaindo de imprimir\n");

	//fprintf(tab->arquivo_dados, "[ titulo: %s,  autor: %s, isbn: %s, chave(codigo): %d ]\n", livro->titulo, livro->autor, livro->isbn, raiz->dado->chave);

	//Antes de fazer a leitura eu dou um salto pra posição adequada que vou ler.

	//A partir do elemento arvore raiz eu vou saber pra onde saltar.

	//Pra onde? Pra posição do indíce que foi guardada na função adicionar. O raiz->dado->indice

	//E como eu estou saltando pra uma posição específica eu uso o SEEK_SET. Vou setar o cursor de leitura e escrita

	//fseek(tab->arquivo_dados, raiz->dado->indice, SEEK_SET);

	//Com o curso de leitura e escrita já posicionado, entãp agora eu ler o bloco do struct.

	//SUBSTITUIR PELA ESTRATEGIA DE SEPARACAO DE CAMPOS PASSAR O SFACNF AQUI
	//fread(livro, sizeof(dado), 1, tab->arquivo_dados);

	//fscanf(tab->arquivo_dados, "%s", livro->titulo);
	//E agora é só imprimir

	//A informação está no indice, e a partir dele eu vou buscar no arquivo com a função fseek pra depois poder imprimir os dados satélites com a função fread
	//printf("[ titulo: %s,  autor: %s, isbn: %s, chave(codigo): %d ]\n", livro->titulo, livro->autor, livro->isbn, raiz->dado->chave);

	free(temp);
}

arvore remover(int valor, arvore raiz)
{
	if (raiz == NULL)
		return NULL;

	if (raiz->dado->chave == valor)
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
		raiz->esq = remover(raiz->dado->chave, raiz->esq);
		return raiz;
	}
	if (valor > raiz->dado->chave)
	{
		raiz->dir = remover(valor, raiz->dir);
	}
	else
	{
		raiz->esq = remover(valor, raiz->esq);
	}
	return raiz;
}

dado *ler_dados()
{
	//Quando eu aloco espaço pra um livro quando uso caracteres de tamanho variável na struct livro, eu aloco espaço pra ponteiiro
	dado *novo = (dado *)malloc(sizeof(dado));

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

//Ideia e passar aqui a tabela inteira pra n ter que reabrir o arquivo e mexer só com a arvore de indices, mas também com o o arquivo de dados inicializado em inicializar()
void salvar_indices(char *nome, arvore a)
{
	FILE *arq;
	//arq = fopen(nome, "wb");
	arq = fopen(nome, "a+b");

	if (arq != NULL)
	{
		salvar_auxiliar_indices(a, arq);
		fclose(arq);
	}
}

void salvar_auxiliar_indices(arvore raiz, FILE *arq)
{
	if (raiz != NULL)
	{

		//	fscanf(tab->arquivo_dados, "%s|%s|%s|%d|\n", livro->titulo, livro->autor, livro->isbn, livro->codigo);
		printf("Salvou os indices\n");

		//Salvar arquivo de indices
		fprintf(arq, "%d|%d|\n", raiz->dado->chave, raiz->dado->indice);

		//fwrite(raiz->dado, sizeof(tipo_dado), 1, arq);
		salvar_auxiliar_indices(raiz->esq, arq);
		salvar_auxiliar_indices(raiz->dir, arq);
	}
} // FIM SALVAR INDICES

//Carrega apenas os indices porque na hora de imprimir/printar vai ser buscado a partir do indice, sai da memória RAM vai lá no disco e printa

///Aqui só deve ler o codigo e o indice
arvore carregar_arquivo(char *nome, arvore a)
{
	printf("Carregando...\n");

	//OBESERVE SE VAI LER UM LIVRO COM TODAS AS INFORMACOES OU APENAS A CHAVE E O CODIGO PRA NA HORA DE IMPRIMIR USAR A FUNCAO PROCURAR_LIVRO PRA IMPRIMIR COM A RESPECITCA CHAVE LIDA NESSA FUNCAO

	char entrada[256];
	char buffer[256];
	int codigo;
	int i, j;

	int cresceu;

	FILE *arq = fopen(nome, "r");

	dado *temp;

	tipo_dado *novo;

	if (arq != NULL)
	{
		novo = (tipo_dado *)malloc(sizeof(tipo_dado));

		while (fgets(entrada, 256, arq) != NULL)
		{
			for (i = 0; entrada[i] != '|'; i++)
			{
				buffer[i] = entrada[i];
				//printf("%c", entrada[i]);
			}
			//printf("|");
			buffer[i] = '\0';
			novo->chave = atoi(buffer);

			i++;

			for (j = 0; entrada[i] != '|'; j++, i++)
			{
				buffer[j] = entrada[i];
				//	printf("%c", entrada[i]);
			}
			//printf("|");
			buffer[j] = '\0';
			novo->indice = atoi(buffer);

			printf("novo->chave: %d\n", novo->chave);
			printf("novo->indice: %d\n", novo->indice);

			printf("\n");

			cresceu = 1;
			a = adicionar(novo, a, &cresceu);

			novo = (tipo_dado *)malloc(sizeof(tipo_dado));
		}

		fclose(arq);
	}

	return a;
}
