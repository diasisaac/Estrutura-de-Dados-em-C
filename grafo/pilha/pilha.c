#include "pilha.h"
#include <stdlib.h>

void pilha_inicializa(struct Pilha *pilha, int tamanho)
{
    pilha->topo = -1;

    pilha->valores = (int *)malloc(sizeof(tamanho));

    pilha->tamanho = tamanho;
}

void pilha_push(struct Pilha *p, int elementos)
{
    p->topo++;
    p->valores[p->topo] = elementos;
}

int pilha_pop(struct Pilha *p)
{
    int elemento = p->valores[p->topo];
    p->topo--;
    return elemento;
}

int pilha_isEmpty(struct Pilha p)
{
    return (p.topo == -1);
}

int pilha_isFull(struct Pilha p)
{
    return (p.topo == p.tamanho);
}

int pilha_top(struct Pilha p) // retorna quem ta no topo
{
    return p.topo;
}
