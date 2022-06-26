#ifndef AVL_H
#define AVL_H

typedef struct livro
{
	char *titulo;
	char *autor;
	char *isbn;
	int codigo;
} dado;

typedef struct indice
{
	int chave;
	int indice;
} tipo_dado;

typedef struct no_avl
{
	tipo_dado *dado;
	int fb;
	struct no_avl *esq, *dir;
} no_avl;

typedef no_avl *arvore;

typedef struct tabela
{
	FILE *arquivo_dados;
	arvore arvore_de_indices;
} tabela;

int inicializarTabela(tabela *tab);
void finalizar(tabela *tab);
void adicionarLivro(tabela *tab, dado *livro);

void inicializar(arvore *raiz);

int altura(arvore raiz);
int maior(int a, int b);
tipo_dado *maior_elemento(arvore raiz);
tipo_dado *menor_elemento(arvore raiz);
void pre_order(arvore raiz, tabela *tab);
void pos_order(arvore raiz, tabela *tab);
void in_order(arvore raiz, tabela *tab);

void imprimir_elemento(arvore raiz, tabela *tab);
dado *ler_dados();
void tirar_enter(char *string);

FILE *procurarLivro(tabela *tab, int chave);

//SALVAR DADOS SATELITES NO ARQUIVO DADOS.TXT
//SALVAR INDICE NO ARQUIVO INDICES.TXT

void salvar_indices(char *nome, arvore a);
void salvar_auxiliar_indices(arvore raiz, FILE *arq);

void salvar_dados_satelites(char *nome, FILE *a);
void salvar_auxiliar_dados_satelites(FILE *arq); // chama a funcao Procurar LivrO

arvore carregar_arquivo(char *nome, arvore a);

arvore adicionar(tipo_dado *valor, arvore raiz, int *cresceu);
arvore fiscal_de_fb_pos_rotacao(arvore raiz);

arvore rotacionar(arvore raiz);
arvore rotacao_simples_direita(arvore raiz);
arvore rotacao_simples_esquerda(arvore raiz);
arvore rotacao_dupla_direita(arvore raiz);
arvore rotacao_dupla_esquerda(arvore raiz);

#endif
