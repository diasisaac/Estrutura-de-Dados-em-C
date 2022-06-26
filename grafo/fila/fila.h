#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

struct Fila
{
    int primeiro;
    int ultimo;
    int total;
    int *valores;
    int tamanho;
};

typedef struct Fila Fila;

void fila_create(Fila *f, int tamanho);
void fila_push(Fila *f, int elemento);
int fila_pop(Fila *f);
int fila_isFull(Fila f);
int fila_isEmpty(Fila f);
int total(Fila f);

#endif