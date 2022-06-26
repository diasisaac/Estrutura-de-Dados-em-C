#ifndef LISTA_ADJ_H_INCLUDED
#define LISTA_ADJ_H_INCLUDED

typedef struct no
{
    struct no *proximo;
    int valor;
} lista;

typedef struct grafo
{
    int v;
    //Localizar o indice do vertice
    int i_v;

    char *mapa;

    lista **arestas; //Um do ponteiros é pra trabalhar com array dinamico e o segundo é pra ponteiro pras listas

} grafo;

lista *inserirInicio(lista *list, int v);

grafo *inicializar(int tam_vertice, int tam_arestas);

//Passa o grafo e o caracter, compara e retorna a posição

//Eu tenho um array e quero saber em qual posição um caracter está nesse array
int localizarVertice(grafo *grafo, char c);

void adicionarAresta(grafo *grafo, char aresta_a, char aresta_b);

void adicionarVertice(grafo *grafo, char vertice);

void imprimir(grafo *graph);

grafo *carregar_arquivo(char *nome, grafo *g);

void bfs(grafo *grafo, int s);

#endif // LISTA_ADJ_H_INCLUDED
