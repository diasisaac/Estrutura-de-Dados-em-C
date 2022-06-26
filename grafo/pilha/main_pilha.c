#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include <string.h>

int main(int argc, char *argv[])
{
    struct Pilha stack;

    int pilha_tamanho, elemento_acrescentado, i;

    printf("Digite o tamanho da pilha: ");
    scanf("%d", &pilha_tamanho);

    pilha_inicializa(&stack, pilha_tamanho);

    for (i = 0; i < pilha_tamanho; i++)
    {
        printf("Digite o elemento da pilha: ");
        scanf("%d", &elemento_acrescentado);
        //Funcao de empilhar
        pilha_push(&stack, elemento_acrescentado);

        printf("\n");
    }

    //E desempilhar a pilha 'stack'
    while (!pilha_isEmpty(stack))
    {
        elemento_acrescentado = pilha_pop(&stack);
        printf("Desempilhei: %d\n", elemento_acrescentado);
    }
    return 0;
}
