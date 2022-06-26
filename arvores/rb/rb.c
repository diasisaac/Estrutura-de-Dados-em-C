#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

arvore no_null;

/*
Inicializa a árvore vazia com a raiz = null e inicializa o nó nulo duplo preto que será utilizado no método remover.
*/
void inicializar(arvore *raiz)
{
	*raiz = NULL;
	no_null = (arvore)malloc(sizeof(struct no_bst));
	no_null->cor = DUPLO_PRETO;
	no_null->dado = 0;
	no_null->esq = NULL;
	no_null->dir = NULL;
}

/* Adiciona um novo elemento na árvore.
Parâmetros:
    valor   - elemento a ser adicionado
    raiz    - árvore onde o elemento será adicionado. 
            Observe que este parâmetro é um ponteiro de ponteiro
*/
void adicionar(int valor, arvore *raiz)
{
	arvore posicao, pai, novo;
	//utiliza-se *raiz, por ser um ponteiro de ponteiro
	posicao = *raiz;
	pai = NULL;

	/*navega na árvore até encontrar a posição vaga apropriada para o elemento,
		nesta "descida" é necessário manter o ponteiro para o pai, pois após encontrar 
		a posição vaga (NULL) não seria possível navegar para o pai com o ponteiro posicao->pai porque não dá pra saber quem é o pai se não tiver uma variável ponteiro que diga que é o pai do elemento atual. Não dá pra simplismente dizer posicao->pai pq isso sem um nó pai n é ninguem.
		
		VOce precisa de um nó ponteiro do pai pra dizer que é o pai do elemento atual
		
		E tipo, se eu fizer
		
		posicao->pai, o nó "->pai" sabe que ele é pai da criança?
		
		eu não posso ter apenas posição->pai porque se eu apagar o pai, o elemento fica sem pai e o pai não é atualizado.
		
		Sendo assim, nas próximas linhas de código eu crio um ponteiro para o nó pai porque daí eu vou tá "registrando" um filho para o nó pai,, e um pai para o nó filho
		
		VOu tá apontando para cada nó e dizendo...
		Olha filho, aquele ali é teu novo pai
		
		OLha pai,aquele ali é teu novo filho
		
		HAHAHAHAHAHAHA 23/01/2021*/
	while (posicao != NULL)
	{
		pai = posicao;
		if (valor > posicao->dado)
			posicao = posicao->dir;
		else
			posicao = posicao->esq;
	}

	//Após achar a posição, inicializa o novo elemento
	novo = (arvore)malloc(sizeof(struct no_bst));
	novo->dado = valor;
	novo->esq = NULL;
	novo->dir = NULL;
	novo->pai = pai;
	novo->cor = VERMELHO;

	//Atualiza a raiz da árvore, caso esteja inserindo o primeiro elemento
	//Observe novamente o uso do ponteiro de ponteiro
	if (eh_raiz(novo))
		*raiz = novo;
	else
	{
		//Se não for a raiz, é preciso realizar a ligação do pai(direita ou esquerda) com o novo elemento
		if (valor > pai->dado)
			pai->dir = novo;
		else
			pai->esq = novo;
	}

	//Após inserir, verifica e ajusta a árvore resultante
	ajustar(raiz, novo);
}

/* Verifica se a árvore está obedecendo todas as regras da RB e aplica as correções necessárias após a inserção.
Parâmetros:
    raiz - raiz (absoluta) da árvore
    elemento - nó recentemente inserido que pode ter causado o desajuste da árvore
*/
void ajustar(arvore *raiz, arvore elemento)
{
	//A árvore está desajustada se tanto o elemento quanto o seu pai estiverem com a cor vermelha
	//Utilizamos um while para continuar a verificação até chegar a raiz, quando necessário
	while (cor(elemento->pai) == VERMELHO && cor(elemento) == VERMELHO)
	{
		//printf("ENTROU NO LACO\n");
		//caso 1: Cor do tio é vermelha, desce o preto do avô
		if (cor(tio(elemento)) == VERMELHO)
		{
			tio(elemento)->cor = PRETO;
			elemento->pai->cor = PRETO;
			elemento->pai->pai->cor = VERMELHO;
			//Continua a verificação a partir do avô, que mudou para vermelho e pode ter
			//gerado uma sequência vermelho-vermelho
			elemento = elemento->pai->pai;
			continue;
		}
		//Aqui é caso o tio seja preto
		//caso 2a: rotação simples direita
		//O elemento e o pai são filhos esquerdos
		if (eh_filho_esquerdo(elemento) && eh_filho_esquerdo(elemento->pai))
		{

			//Passa a arvore, e o avo
			rotacao_simples_direita(raiz, elemento->pai->pai);
			//printf("Saiu da rotacao simples direita\n");

			elemento->pai->cor = PRETO;
			elemento->pai->dir->cor = VERMELHO;
			continue;
			//Depois
			//A raiz atual fica preta, o antigo pai
			//E os filhos, o elemento e o antigo avo ficam vermelhos, como o o elemento inserido, o nó elemento, já era vermelho pela propriedade desse tipo de árvore, logo não precisa setar a cor dele pra vermelha
		}

		//caso 2b: rotação simples esquerda
		if (!eh_filho_esquerdo(elemento) && !eh_filho_esquerdo(elemento->pai))
		{
			//printf("caso 2b\n");
			rotacao_simples_esquerda(raiz, elemento->pai->pai);
			//printf("Saiu da rotação simples esquerda\n");
			elemento->pai->cor = PRETO;
			elemento->pai->esq->cor = VERMELHO;
			continue;
		}

		//caso 3a: rotação dupla direita
		if (eh_filho_esquerdo(elemento->pai) && !eh_filho_esquerdo(elemento))
		{
			rotacao_dupla_direita(raiz, elemento->pai->pai);
			//printf("raiz : %d\n", elemento->dado);
			//printf("filho direito %d\n", elemento->dir->dado);
			//Depois da rotação dupla direita temos que:

			//O elemento inserido agora é raiz.

			//Agora o elemento que foi inserido virou pai do avo e pai do seu pai. O avo é seu filho direito e o pai seu filho esquerdo.
			elemento->cor = PRETO;
			elemento->dir->cor = VERMELHO;
			continue;
		}

		//caso 3b: rotação dupla esquerda
		if (!eh_filho_esquerdo(elemento->pai) && eh_filho_esquerdo(elemento))
		{
			rotacao_dupla_esquerda(raiz, elemento->pai->pai);
			//printf("raiz : %d\n", elemento->dado);
			//printf("filho direito %d\n", elemento->dir->dado);
			//Depois da rotação dupla direita temos que:

			//O elemento inserido agora é raiz.

			//Agora o elemento que foi inserido virou pai do avo e pai do seu pai. O avo é seu filho direito e o pai seu filho esquerdo.
			elemento->cor = PRETO;
			elemento->esq->cor = VERMELHO;

			continue;
		}
	}
	//Após todas as correções a raiz pode ter ficado na cor vermelha, portanto passamos ela novamente para cor preta
	(*raiz)->cor = PRETO;
}

/* Realiza a rotação simples direita
Antes da rotação: 
cor(p) = Preto
cor(u) = cor(v) = Vermelho

       p             u
      / \           / \
     u  t2   =>    v   p
    / \               / \
   v  t1             t1 t2

Após aa rotação: 
cor(u) = Preto
cor(v) = cor(p) = Vermelho
*/
void rotacao_simples_direita(arvore *raiz, arvore pivo)
{
	//printf("Entrou na rotação simples direita, o pivo eh: %d\n", pivo->dado);

	arvore u, t1;
	u = pivo->esq;
	t1 = u->dir;

	/*Para fazer a ligação da raiz da sub-árvore resultante com o seu pai, é preciso saber se o pivo p era um filho esquerdo ou direito*/
	int posicao_pivo_esq = eh_filho_esquerdo(pivo);

	//Atualização dos ponteiros
	pivo->esq = t1;
	if (t1 != NULL)
		t1->pai = pivo;

	u->dir = pivo;

	u->pai = pivo->pai;
	pivo->pai = u;

	//Se não existir árvore acima de u, u passa a ser a raiz da árvore
	if (eh_raiz(u))
	{
		*raiz = u;
	}
	else
	{
		//Caso contrário (se existir) é preciso ligar o restante da árvore a esta sub-árvore, resultante da rotação
		if (posicao_pivo_esq)
			u->pai->esq = u;
		else
			u->pai->dir = u;
	}
}

/* Realiza a rotação simples esquerda
Antes da rotação: 
cor(p) = Preto
cor(u) = cor(v) = Vermelho

       p             u
      / \           / \
     t1  u   =>    p   v
    	/ \       / \
   	   t2  v     t1 t2

Após aa rotação: 
cor(u) = Preto
cor(v) = cor(p) = Vermelho
*/
void rotacao_simples_esquerda(arvore *raiz, arvore pivo)
{
	//printf("Entrou na rotacao esquerda\n");
	arvore u, t2;
	u = pivo->dir;
	t2 = u->esq;

	//Para fazer a ligação da raiz da subárvore resultante com o seu pai, é preciso saber se o pivo p era um filho esquerdo ou direito

	int posicao_pivo_esq = eh_filho_esquerdo(pivo);

	//Atualização de ponteiros
	pivo->dir = t2;

	if (t2 != NULL)
	{
		t2->pai = pivo;
	}

	u->esq = pivo;

	u->pai = pivo->pai;
	pivo->pai = u;

	//Se não existir árvore acima de u, u passa a ser a raiz da árvore
	if (eh_raiz(u))
	{
		*raiz = u;
	}
	else
	{
		//Caso contrário (se existir) é preciso ligar o restante da árvore a esta sub-árvore, resultante da rotação
		if (posicao_pivo_esq)
		{
			u->pai->esq = u;
		}
		else
		{
			u->pai->dir = u;
		}
	}
}

void rotacao_dupla_direita(arvore *raiz, arvore pivo)
{
	//printf("Rotação dupla direita\n");
	//printf("Pivo %d, pivo->esq: %d\n", pivo->dado, pivo->esq->dado);
	rotacao_simples_esquerda(raiz, pivo->esq);
	rotacao_simples_direita(raiz, pivo);
}

void rotacao_dupla_esquerda(arvore *raiz, arvore pivo)
{
	//printf("Rotação dupla esquerda\n");
	//printf("Pivo %d, pivo->esq: %d\n", pivo->dado, pivo->dir->dado);
	rotacao_simples_direita(raiz, pivo->dir);
	rotacao_simples_esquerda(raiz, pivo);
}
/*Retorna a cor de um nó. Observe que, por definição, o null é preto*/
enum cor cor(arvore elemento)
{
	enum cor c;
	if (elemento == NULL || elemento->cor == PRETO)
		c = PRETO;
	else
		c = VERMELHO;
	return c;
}
/*Verifica se um nó é a raiz da árvore*/
int eh_raiz(arvore elemento)
{
	return (elemento->pai == NULL);
}
/*Verifica se um nó é filho esquerdo*/
int eh_filho_esquerdo(arvore elemento)
{
	return (elemento->pai != NULL && elemento == elemento->pai->esq);
}

arvore tio(arvore elemento)
{
	return irmao(elemento->pai);
}

arvore irmao(arvore elemento)
{
	if (eh_filho_esquerdo(elemento))
		return elemento->pai->dir;
	else
		return elemento->pai->esq;
}
/*
void imprimir(arvore raiz)
{
	printf("(");
	if (raiz != NULL)
	{
		imprimir_elemento(raiz);
		imprimir(raiz->esq);
		imprimir(raiz->dir);
	}
	printf(")");
}
*/
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

int maior_elemento(arvore raiz)
{
	if (raiz == NULL)
		return -1;
	if (raiz->dir == NULL)
		return raiz->dado;
	else
		return maior_elemento(raiz->dir);
}

int menor_elemento(arvore raiz)
{
	if (raiz == NULL)
		return -1;
	if (raiz->esq == NULL)
		return raiz->dado;
	else
		return maior_elemento(raiz->esq);
}

void pre_order(arvore raiz)
{
	if (raiz != NULL)
	{
		printf("[%d]", raiz->dado);
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
		printf("[%d]", raiz->dado);
	}
}

void in_order(arvore raiz)
{
	if (raiz != NULL)
	{
		in_order(raiz->esq);
		printf("[%d]", raiz->dado);
		in_order(raiz->dir);
	}
}
/*
void imprimir_elemento(arvore raiz)
{
	switch (raiz->cor)
	{
	case PRETO:
		printf("\x1b[33m[%d]\x1b[0m", raiz->dado);
		break;
	case VERMELHO:
		printf("\x1b[31m[%d]\x1b[0m", raiz->dado);
		break;
	case DUPLO_PRETO:
		printf("\x1b[32m[%d]\x1b[0m", raiz->dado);
		break;
	}
}
*/
void remover(int valor, arvore *raiz)
{
	arvore posicao;
	posicao = *raiz;

	while (posicao != NULL)
	{
		if (valor == posicao->dado)
		{
			//elemento possui dois filhos
			if (posicao->esq != NULL && posicao->dir != NULL)
			{
				posicao->dado = maior_elemento(posicao->esq);
				remover(posicao->dado, &(posicao->esq));
				break;
			}

			//O elemento possui apenas um filho (direito)
			if (posicao->esq == NULL && posicao->dir != NULL)
			{
				//O seu filho direito sobe para a posição do elemento  a ser removido e recebe a cor preta
				posicao->dir->cor = PRETO;
				posicao->dir->pai = posicao->pai;

				if (eh_raiz(posicao))
				{
					*raiz = posicao->dir;
				}
				else
				{
					if (eh_filho_esquerdo(posicao))
					{
						posicao->pai->esq = posicao->dir;
					}
					else
					{
						posicao->pai->dir = posicao->dir;
					}
				}
				break;
			}

			//O elemento possui apenas um filho (esquerdo)
			if (posicao->esq != NULL && posicao->dir == NULL)
			{

				//O seu filho esquerdo sobe para a posição do elemento  a ser removido e recebe a cor preta

				posicao->esq->cor = PRETO;
				posicao->esq->pai = posicao->pai;

				if (eh_raiz(posicao))
				{
					*raiz = posicao->esq;
				}
				else
				{
					if (eh_filho_esquerdo(posicao))
					{
						posicao->pai->esq = posicao->dir;
					}
					else
					{
						posicao->pai->dir = posicao->dir;
					}
				}
				break;
			}

			//O elemento não possui filhos
			if (posicao->esq == NULL && posicao->dir == NULL)
			{
				//Remover raiz sem filhos
				if (eh_raiz(posicao))
				{
					*raiz = NULL;
					break;
				}

				//Remover elemento que não possui filhos e não é raiz
				//Se for vermelho, apenas remove atualizando o ponteiro
				//correspondente do pai
				if (posicao->cor == VERMELHO)
				{
					if (eh_filho_esquerdo(posicao))
						posicao->pai->esq = NULL;
					else
						posicao->pai->dir = NULL;
					break;
				}
				else
				{
					//Se o elemento for preto, substitui pelo duplo preto e depois ajusta a árvore
					no_null->pai = posicao->pai;
					if (eh_filho_esquerdo(posicao))
						posicao->pai->esq = no_null;
					else
						posicao->pai->dir = no_null;

					reajustar(raiz, no_null);
					break;
				}
			}
		}
		if (valor > posicao->dado)
			posicao = posicao->dir;
		else
			posicao = posicao->esq;
	}
}

/*Realiza a correção da árvore após a remoção de um elemento preto que não possui filhos, ou seja, elimina o nó null o duplo-preto.*/

void reajustar(arvore *raiz, arvore elemento)
{
	//	cor(irmao(elemento)->dir), cor(irmao(elemento)->esq));
	//caso 1
	if (eh_raiz(elemento))
	{
		//	printf("caso 1\n");
		elemento->cor = PRETO;
		/*Falta eliminar o nó duplo preto
        if(elemento == no_null)
            *raiz = NULL;*/

		retira_duplo_preto(raiz, elemento);

		return;
	}

	//caso 2
	if (cor(elemento->pai) == PRETO &&
		cor(irmao(elemento)) == VERMELHO &&
		cor(irmao(elemento)->dir) == PRETO &&
		cor(irmao(elemento)->esq) == PRETO)
	{
		//	printf("Remocao - caso 2\n");
		//Verifica se é o caso 2 esquerdo ou direito
		if (eh_filho_esquerdo(elemento))
			rotacao_simples_esquerda(raiz, elemento->pai);
		else
			rotacao_simples_direita(raiz, elemento->pai);
		elemento->pai->pai->cor = PRETO;
		elemento->pai->cor = VERMELHO;

		//Atenção à chamada recursiva do reajustar.
		//O caso 2 não remove o duplo-preto
		reajustar(raiz, elemento);

		return;
	}

	//caso 3
	if (cor(elemento->pai) == PRETO &&
		cor(irmao(elemento)) == PRETO &&
		cor(irmao(elemento)->dir) == PRETO &&
		cor(irmao(elemento)->esq) == PRETO)
	{
		//Verificar e remover o no_null

		//	printf("Remocao - caso 3\n");

		elemento->cor = PRETO;
		irmao(elemento)->cor = VERMELHO;
		elemento->pai->cor = DUPLO_PRETO;

		//Chamada recursiva para eliminar o duplo preto do elemento P

		retira_duplo_preto(raiz, elemento);
		reajustar(raiz, elemento->pai);
		return;
	}

	//caso 4
	if (cor(elemento->pai) == VERMELHO &&
		cor(irmao(elemento)) == PRETO &&
		cor(irmao(elemento)->dir) == PRETO &&
		cor(irmao(elemento)->esq) == PRETO)
	{

		//	printf("Remocao - caso 4\n");
		elemento->pai->cor = PRETO;
		irmao(elemento)->cor = VERMELHO;
		//Verificar e remover o no_null
		retira_duplo_preto(raiz, elemento);
		return;
	}

	//Casos 5 e 6 ficam mais fáceis separando o esquerdo do direito
	//caso 5a
	if (eh_filho_esquerdo(elemento) &&
		cor(irmao(elemento)) == PRETO &&
		cor(irmao(elemento)->dir) == PRETO &&
		cor(irmao(elemento)->esq) == VERMELHO)
	{
		//Aqui já assume que o elemento eh filho esquerdo

		//	printf("Remocao - caso 5a\n");
		rotacao_simples_direita(raiz, irmao(elemento));
		irmao(elemento)->cor = PRETO; //Agora o irmão é o X
		irmao(elemento)->dir->cor = VERMELHO;
		reajustar(raiz, elemento);

		return;
	}

	//caso 5b
	if (!eh_filho_esquerdo(elemento) &&
		cor(irmao(elemento)) == PRETO &&
		cor(irmao(elemento)->dir) == VERMELHO &&
		cor(irmao(elemento)->esq) == PRETO)
	{

		//	printf("\nRemocao - caso 5b\n");
		rotacao_simples_esquerda(raiz, irmao(elemento));

		irmao(elemento)->cor = PRETO;		  // Agora é o X
		irmao(elemento)->esq->cor = VERMELHO; // Agora é o S

		reajustar(raiz, elemento);

		return;
	}

	//caso 6a
	if (eh_filho_esquerdo(elemento) &&
		cor(irmao(elemento)) == PRETO &&
		cor(irmao(elemento)->dir) == VERMELHO)
	{

		//	printf("Remocao - caso 6a\n");
		rotacao_simples_esquerda(raiz, elemento->pai);

		elemento->pai->pai->cor = elemento->pai->cor;
		elemento->pai->cor = PRETO;
		tio(elemento)->cor = PRETO;
		retira_duplo_preto(raiz, elemento);
		return;
	}

	//caso 6b
	if (!eh_filho_esquerdo(elemento) &&
		cor(irmao(elemento)) == PRETO &&
		cor(irmao(elemento)->esq) == VERMELHO)
	{

		//	printf("Remocao - caso 6b\n");
		rotacao_simples_direita(raiz, elemento->pai);

		elemento->pai->pai->cor = elemento->pai->cor;
		elemento->pai->cor = PRETO;
		tio(elemento)->cor = PRETO;
		retira_duplo_preto(raiz, elemento);

		return;
	}
}

void retira_duplo_preto(arvore *raiz, arvore elemento)
{
	if (elemento == no_null)
		if (eh_filho_esquerdo(elemento))
			elemento->pai->esq = NULL;
		else
			elemento->pai->dir = NULL;
	else
		elemento->cor = PRETO;
}

void reverso(arvore raiz)
{
	if (raiz != NULL)
	{
		reverso(raiz->dir);
		//imprimir_elemento(raiz);
		printf("[%d]", raiz->dado);
		reverso(raiz->esq);
	}
}

int qtdPar(arvore raiz)
{
	int qtd_par = 0;
	if (raiz != NULL)
	{
		if (raiz->dado % 2 == 0)
		{
			qtd_par += 1;
		}
		qtd_par += qtdPar(raiz->esq);
		qtd_par += qtdPar(raiz->dir);

		return qtd_par;
	}
}

int se_existe(arvore raiz, int elemento)
{
	//printf("Raiz atual: %d\n", raiz->valor);
	int retorno = 0;

	if (raiz == NULL)
	{
		retorno = 0;
		return retorno;
	}
	else
	{
		if (raiz->dado == elemento)
		{
			retorno = 1;
			return retorno;
		}
		else if (elemento < raiz->dado)
		{
			if (raiz->esq != NULL)
			{
				se_existe(raiz->esq, elemento);
			}
			else
			{
				retorno = 0; // Para fins didáticos
				return retorno;
			}
		}

		else if (elemento > raiz->dado)
		{
			if (raiz->dir != NULL)
			{
				se_existe(raiz->dir, elemento);
			}
			else
			{
				retorno = 0;
				return retorno;
			}
		}
		else // Caso seja nulo
		{
			retorno = 0;
			return retorno;
		}
	}
}

int checa_positivo(arvore raiz)
{
	int valores_negativos = 0;
	if (raiz != NULL)
	{
		if (raiz->dado < 0)
		{
			valores_negativos = 1;
		}
		valores_negativos += checa_positivo(raiz->esq);
		valores_negativos += checa_positivo(raiz->dir);

		return valores_negativos;
	}
}

void func_quadrado(arvore raiz)
{
	if (raiz != NULL)
	{
		raiz->dado = raiz->dado * raiz->dado;
		func_quadrado(raiz->esq);
		func_quadrado(raiz->dir);
	}
}
