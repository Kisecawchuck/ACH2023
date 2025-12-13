#ifndef LISTA_H
#define LISTA_H

#include "arvore.h"
typedef struct _NODO {
    char palavra[46];
    int n;
    Ocorrencia *ocorrencias;
    struct _NODO *proximo;
} Nodo;

typedef struct {
    Nodo *primeiro;
} Lista;

Lista *cria_lista();
bool insere_lista(Lista *lista, char *s, int l);
void destroi_lista(Lista *lista);
int tamanho(Lista *lista);
Nodo *busca_lista(Lista *lista, char *s);

#endif
