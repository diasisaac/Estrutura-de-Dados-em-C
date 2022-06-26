#include "fila.h"
#include <stdlib.h>
#include <stdio.h>

void fila_create(Fila *fila, int tamanho)
{
    fila->primeiro = 0;
    fila->ultimo = 0;
    fila->total = 0;
    fila->tamanho = tamanho;

    fila->valores = (int *)malloc(sizeof(tamanho));
}

void fila_push(Fila *f, int elementos)
{
    f->valores[f->ultimo] = elementos;

    //Desse modo o ultimo sempre vai variar entre 0 e tamaho - 1
    f->ultimo = (f->ultimo + 1) % f->tamanho;

    f->total++;
}

int fila_pop(Fila *f)
{
    int e = f->valores[f->primeiro];
    f->primeiro = (f->primeiro + 1) % f->tamanho;
    f->total--;
    return e;
}

int fila_isFull(Fila f)
{
    return (f.total == f.tamanho);
}

int fila_isEmpty(Fila f)
{
    return (f.total == 0);
}

int total(Fila f)
{
    return f.total;
}
