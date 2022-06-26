#ifndef AVL_H
#define AVL_H

typedef struct livro
{
	//Caracteres de tamanho variável
	char *titulo;
	char *autor;
	char *isbn;
	int codigo;
} dado;

typedef struct no_avl
{
	dado *dado;
	//int dado;
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

arvore adicionar(dado *valor, arvore raiz, int *cresceu);
arvore fiscal_de_fb_pos_rotacao(arvore raiz);
arvore remover(arvore raiz, int valor, int *diminuiu);
arvore rotacionar(arvore raiz);
arvore rotacao_simples_direita(arvore raiz);
arvore rotacao_simples_esquerda(arvore raiz);
arvore rotacao_dupla_direita(arvore raiz);
arvore rotacao_dupla_esquerda(arvore raiz);

dado *ler_dados();
void tirar_enter(char *string);

void salvar_arquivo(char *nome, arvore a);
void salvar_auxiliar(arvore raiz, FILE *arq);
arvore carregar_arquivo(char *nome, arvore a);

#endif
