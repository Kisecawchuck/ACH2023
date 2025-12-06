#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

Arvore *cria_arvore() {
    Arvore *arvore = malloc(sizeof(Arvore));
    arvore->raiz = NULL;
    return arvore;
}

No *insere_ord_rec(No *raiz, No *novo){
    if (raiz) {
        if (strcasecmp(novo->palavra, raiz->palavra) != 0) {
            if (strcasecmp(novo->palavra, raiz->palavra) < 0) raiz->esq = insere_ord_rec(raiz->esq, novo);
            else raiz->dir = insere_ord_rec(raiz->dir, novo);
        }
        return raiz;
    }
    return novo;
}

No *busca_rec(No * no, char *e){
    if (no) {
        if (strcasecmp(no->palavra, e) > 0) return busca_rec(no->esq, e);
        if (strcasecmp(no->palavra, e) < 0) return busca_rec(no->dir, e);
        return no;
    }
    return NULL;
}

No *busca(Arvore * arvore, char *e){
    return busca_rec(arvore->raiz, e);	
}

void adiciona_linha(No *no, int linha) {
    Ocorrencia *novo = malloc(sizeof(Ocorrencia));
    if (!novo) return;
    novo->linha = linha;
    novo->prox = NULL;

    if (!no->ocorrencias)
        no->ocorrencias = novo;
    else {
        Ocorrencia *p = no->ocorrencias;
        Ocorrencia *tmp;
        while (p) {
            if (p->linha == linha) {
                no->n++;
                free(novo);
                return;
            }
            tmp = p;
            p = p->prox;
        }
        tmp->prox = novo;
        no->n++;
    }
}

bool insere_ord(Arvore *arvore, char *e, int l) {
    No *p = busca(arvore, e);
    if (p) {
        adiciona_linha(p, l);
        return false;
    }
    No * novo = malloc(sizeof(No));
    if (!novo) return false;

    strcpy(novo->palavra, e);
    novo->esq = novo->dir = NULL;
    novo->ocorrencias = NULL;
    novo->n = 1;
    adiciona_linha(novo, l);

    arvore->raiz = insere_ord_rec(arvore->raiz, novo);
    return true;
}


int contar_rec(No * no) {
    if (no)
        return contar_rec(no->esq) + contar_rec(no->dir) + 1;
    return 0;
}

int contar(Arvore * arvore) {
    return contar_rec(arvore->raiz);
}

int max(int a, int b) { return a > b ? a : b; } 

int altura(No * no) {
    if (no) {
        return max(altura(no->esq), altura(no->dir)) + 1;
    }
    return -1;
}

void destroi_ocorrencias(Ocorrencia *ocorrencia) {
    if (!ocorrencia) return;

    destroi_ocorrencias(ocorrencia->prox);
    free(ocorrencia);
}

void destroi_arvore_rec(No *no) {
    if (!no) return;

    destroi_arvore_rec(no->esq);
    destroi_arvore_rec(no->dir);
    destroi_ocorrencias(no->ocorrencias);
    free(no);

}

void destroi_arvore(Arvore *arvore) {
    destroi_arvore_rec(arvore->raiz);
}
