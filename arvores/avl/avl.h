#ifndef AVL_H
#define AVL_H

typedef struct no_avl
{
	int dado;
	int fb;
	struct no_avl *esq, *dir;
} no_avl;

typedef no_avl *arvore;

void inicializar(arvore *raiz);
void pre_order(arvore raiz);
void pos_order(arvore raiz);
void in_order(arvore raiz);
void reverso(arvore raiz);
void func_quadrado(arvore raiz);

int qtdPar(arvore raiz);
int se_existe(arvore raiz, int elemento);
int checa_positivo(arvore raiz);

arvore adicionar(int valor, arvore raiz, int *cresceu);
arvore fiscal_de_fb_pos_rotacao(arvore raiz);
arvore remover(arvore raiz, int valor, int *diminuiu);
arvore rotacionar(arvore raiz);
arvore rotacao_simples_direita(arvore raiz);
arvore rotacao_simples_esquerda(arvore raiz);
arvore rotacao_dupla_direita(arvore raiz);
arvore rotacao_dupla_esquerda(arvore raiz);

#endif
