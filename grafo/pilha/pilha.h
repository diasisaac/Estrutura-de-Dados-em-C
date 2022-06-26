#ifndef MESSEGE_H_INCLUDED
#define MESSEGE_H_INCLUDED

struct Pilha
{
    int topo;
    int *valores;
    int tamanho;
};

void pilha_inicializa(struct Pilha *p, int tamanho);
void pilha_push(struct Pilha *p, int elementos);
int pilha_pop(struct Pilha *p);
int pilha_isEmpty(struct Pilha p);
int pilha_isFull(struct Pilha p);
int pilha_top(struct Pilha p);

void retornar(struct Pilha *p, struct Pilha *v);
#endif // MESSEGE_H_INCLUDED
