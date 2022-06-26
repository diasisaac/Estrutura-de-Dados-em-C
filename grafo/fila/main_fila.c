#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

int main(int argc, char const *argv[])
{
    int tamanho_fila = 5;
    int x;

    Fila nova_fila;

    fila_create(&nova_fila, tamanho_fila);

    fila_push(&nova_fila, 1);
    fila_push(&nova_fila, 2);
    fila_push(&nova_fila, 3);

    while (!fila_isEmpty(nova_fila))
    {
        x = fila_pop(&nova_fila);
        printf("Elemento retirado %d\n", x);
    }
    printf("FIM\n");
    return 0;
}
