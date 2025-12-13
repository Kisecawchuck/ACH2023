#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "arvore.h"
#include "lista.h"

enum { _Lista, _Arvore };

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <nome_do_arquivo>.txt <tipo_de_índice>\n", argv[0]);
        return 1;
    } 

    printf("Arquivo: \'%s\'\n", argv[1]);
    printf("Tipo de indice: \'%s\'\n", argv[2]);
    FILE *ENTRADA = fopen(argv[1], "r");
    if (!ENTRADA) {
        printf("Erro! Impossível abrir o arquivo de entrada!\n");
        return 2;
    }
    int indice;
    if (strcmp(argv[2], "arvore") == 0) indice = _Arvore;
    else if (strcmp(argv[2], "lista") == 0) indice = _Lista;
    else {
        printf("Erro! Tipo de índice inválido!\n");
        fclose(ENTRADA);
        return 3;
    }

    char *linha = NULL;
    size_t len = 0;
    int lidos;

    char **linhas = NULL;
    int n_linhas = 0;
    while ((lidos = getline(&linha, &len, ENTRADA)) != -1) {
        linhas = realloc(linhas, (n_linhas + 1) * sizeof(char *));
        linhas[n_linhas] = strdup(linha);
        n_linhas++;
    }
    free(linha);
    fclose(ENTRADA);

    if (indice == _Arvore) {
        Arvore *arvore = cria_arvore();
        for (int i = 0; i < n_linhas; i++) {
            char *tmp = strdup(linhas[i]);
            char *token = strtok(tmp, " -,./\n");
            while (token) {
                insere_ord(arvore, token, i);
                token = strtok(NULL, " -,./\n");
            }
            free(tmp);
        }

        int n = contar(arvore);
        int h = altura(arvore->raiz);
        printf("Total de palavras unicas indexadas: %05d\n", n);
        printf("Numero de linhas no arquivo: %d\n", n_linhas);
        printf("Altura da arvore: %05d\n", h);

        char comando[100];
        bool fim = false;
        while (!fim) {
            printf("> ");
            scanf("%s", comando);
            if (strcmp(comando, "fim") == 0) fim = true;
            else if (strcmp(comando, "busca") == 0) {
                scanf("%s", comando);
                No *p = busca_arvore(arvore, comando);
                if (p) {
                    printf("Existem %d ocorrências da palavra \'%s\' na(s) seguinte(s) linha(s):\n", p->n, comando);
                    Ocorrencia *o = p->ocorrencias;
                    while (o) {
                        printf("%05d: %s", o->linha + 1, linhas[o->linha]);
                        o = o->prox;
                    }
                    printf("Numero de comparacoes: %05d\n", h - altura(p) + 1);
                } else {
                    printf("Palavra \'%s\' nao encontrada.\n", comando);
                    printf("Numero de comparacoes: %05d\n", h + 1);
                }
            } else printf("Opcao invalida!\n");
        }
        destroi_arvore(arvore);
        free(arvore);
    } else {
        Lista *lista = cria_lista();
        for (int i = 0; i < n_linhas; i++) {
            char *tmp = strdup(linhas[i]);
            char *token = strtok(tmp, " -,./\n");
            while (token) {
                insere_lista(lista, token, i);
                token = strtok(NULL, " -,./\n");
            }

            free(tmp);
        }

        int n = tamanho(lista);

        printf("Total de palavras unicas indexadas: %05d\n", n);
        printf("Numero de linhas no arquivo: %d\n", n_linhas);

        char comando[100];
        bool fim = false;
        while (!fim) {
            printf("> ");
            scanf("%s", comando);
            if (strcmp(comando, "fim") == 0) fim = true;
            else if (strcmp(comando, "busca") == 0) {
                scanf("%s", comando);
                Nodo *p = busca_lista(lista, comando);
                Nodo *q = lista->primeiro;
                int idx;
                if (p) {
                    for (idx = 1; strcasecmp(p->palavra, q->palavra) != 0; idx++) q = q->proximo;
                    printf("Existem %d ocorrências da palavra \'%s\' na(s) seguinte(s) linha(s):\n", p->n, comando);
                    Ocorrencia *o = p->ocorrencias;
                    while (o) {
                        printf("%05d: %s", o->linha + 1, linhas[o->linha]);
                        o = o->prox;
                    }
                    printf("Numero de comparacoes: %05d\n", idx);
                } else {
                    printf("Palavra \'%s\' nao encontrada.\n", comando);
                    printf("Numero de comparacoes: %05d\n", n);
                }
            } else printf("Opcao invalida!\n");
        }
        destroi_lista(lista);
        free(lista);
    }
    for (int i = 0; i < n_linhas; i++) free(linhas[i]);
    free(linhas);
    return 0;
}
