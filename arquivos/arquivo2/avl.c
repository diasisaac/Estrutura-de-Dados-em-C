#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include <string.h>

void inicializar(arvore *raiz)
{
	*raiz = NULL;
}

/*----------
Adiciona um novo elemento à árvore e realiza as operações de balanceamento, se necessário
Parâmetros:
    valor   - elemento a ser inserido
    raiz    - raiz da árvore onde o elemento será inserido
    cresceu - variável de controle que ajuda a calcular o fator de balanço

Retorno:
    Raiz da árvore resultante da operação de adicionar
--*/

arvore adicionar(dado *valor, arvore raiz, int *cresceu)
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

/*----------
Só está implementada a "base" do remover da BST.
Incluir a variável de controle "diminuir" similar a "cresceu do adicionar.
------*/

/*
arvore remover(arvore raiz, int valor, int *diminuiu)
{
	//Remover da sub-arvore vazia e retorna uma sub-arvore vazia
	//Chega aqui quando se tenta remover um elemento que não existe
	if (raiz == NULL)
	{
		return NULL;
	}

	if (raiz->dado->codigo == valor) // CASO BASE
	{
		//caso 1 - 0 Filhos

		if (raiz->esq == NULL && raiz->dir == NULL)
		{
			free(raiz);
			*diminuiu = 1;
			return NULL;
		}

		//Caso 2a - exatamente 1 filho (dir)
		if (raiz->esq == NULL && raiz->dir != NULL)
		{
			arvore retorno = raiz->dir; // É o ponteiro que vai ser ligado
			free(raiz);
			*diminuiu = 1;
			return retorno;
		}

		//Caso 2b - exatamente 1 filho (esq)
		if (raiz->esq != NULL && raiz->dir == NULL)
		{
			arvore retorno = raiz->esq;
			free(raiz);
			*diminuiu = 1;
			return retorno;
		}

		else
		{

			arvore maior_dosmenores = raiz->esq;

			while (maior_dosmenores->dir != NULL) //enquanto houver filhos a dir
			{
				maior_dosmenores = maior_dosmenores->dir;
			}

			//Cheguei no ultimo cara
			//Troco os elementos da árvore

			//printf("Raiz para ser eliminada: %d\n", raiz->dado);

			raiz->dado->codigo = maior_dosmenores->dado; //O nó raiz que quero remover o elemento do maior dos menores
			//printf("Raiz copiada: %d e o elemento que quero remover: %d\n", raiz->dado, maior_dosmenores->dado);

			raiz->esq = remover(raiz->esq, raiz->dado->codigo, diminuiu);

			//O SWITH DO REMOVEU A ESQUERDA
			//Calcular o fator de balanco aqui agora
			if (*diminuiu) //Eu removi e só posso remover 1 elemento, daí a subarvore a direita dessa raiz relativa diminuiu em 1 elemento.
			{
				switch (raiz->fb)
				{
				case -1:

					raiz->fb = 0;
					break;

				case 0:

					raiz->fb = 1;
					break;
				case 1:
					*diminuiu = 1;
					raiz = rotacionar(raiz);
					break;
				}
			}
			return raiz;
		}
	}
	else
	{
		if (valor > raiz->dado->codigo) // Inserir a direita
		{
			//Se eu to inserindo na direita eu vou atualizar o ponteiro da direita com o resiltado do inserir pra fazer a ligação com quem tá chamando a função na arvore principal com essa nova caixinha
			raiz->dir = remover(raiz->dir, valor, diminuiu); // vai passando a variavel

			//Caso imediato após sair do caso base
			if (*diminuiu) // Só altera o fator de balanco da raiz relativa da arvore se diminuir, istp é, se for removido o filho de uma raiz relativa com 1 ou 0 filhos. Porque a raiz relativa que tem um filho que esse filho tem 2 filhos, o fb da raiz relativa (avó) não é alterado.
			{
				switch (raiz->fb)
				{
				case -1:
					*diminuiu = 1; //Nao é garantido que apos remover e rotacionar corrigiu todos os fb dos nós na arvore
					//printf("raiz dentro do caso -1: %d\n", raiz->dado);
					return rotacionar(raiz);
					break;
				case 0:
					raiz->fb = -1;
					*diminuiu = 0;
					break;

				case 1:
					raiz->fb = 0;
					*diminuiu = 1;
					break;
				}
			}
		}
		else
		{ // Se nao tá na direita, desce pra esquerda
			//Se eu to atualizando na esquerda, dai eu vou atualizar a subarvore a esquerda, ou seja, ligar esse o resultado que é a nova caixinha com o resultado da função inserir
			raiz->esq = remover(raiz->esq, valor, diminuiu); // vai passando a variavel

			//Caso imediato após sair do caso base
			if (*diminuiu) //Eu removi e só posso remover 1 elemento, daí a subarvore a direita dessa raiz relativa diminuiu em 1 elemento.
			{
				switch (raiz->fb)
				{
				case -1:
					*diminuiu = 1;
					raiz->fb = 0;
					break;

				case 0:
					*diminuiu = 0;
					raiz->fb = 1;
					break;
				case 1:
					*diminuiu = 1;
					return rotacionar(raiz);
					break;
				}
			}
		}			 //A cada passo a gente tá ficando mais próximo da altura zero
		return raiz; // E por fim eu tenho que retorna a raiz quando ela não foi modificada, quando a gente entra num caso recursivo, estamos apenas modificando abaixo da raiz
	}
}

*/

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

void imprimir_elemento(arvore raiz)
{
	printf("%s | %s | %s | %d \n", raiz->dado->titulo, raiz->dado->autor, raiz->dado->isbn, raiz->dado->codigo);
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

//***********ABAIXO TRABALHA COM ARQUIVOS *********

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

	int cresceu;

	FILE *arq = fopen("dados.txt", "r");
	dado *temp;

	if (arq != NULL)
	{
		temp = (dado *)malloc(sizeof(dado));

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

			cresceu = 1;
			a = adicionar(temp, a, &cresceu);

			temp = (dado *)malloc(sizeof(dado));
		}

		fclose(arq);
	}

	return a;
}
