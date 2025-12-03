#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "arvore.h"

#define TAMANHO 10000

enum { _Lista, _Arvore };

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <nome_do_arquivo>.txt <tipo_de_índice>\n", argv[0]);
        exit(1);
    } 

    FILE *ENTRADA;
    printf("Arquivo: \'%s\'\n", argv[1]);
    printf("Tipo de indice: \'%s\'\n", argv[2]);
    ENTRADA = fopen(argv[1], "r");
    if (ENTRADA == NULL) {
        printf("Erro! Impossível abrir o arquivo de entrada!\n");
        exit(2);
    }

    int n_linhas = 0;
    int n_palavras = 0;
    int indice = strcasecmp(argv[2], "arvore") == 0 ? _Arvore : _Lista;
    Arvore *arvore = cria_arvore();
    char buffer[TAMANHO + 1];
    while (ENTRADA && fgets(buffer, TAMANHO, ENTRADA)) {
        n_linhas++;

        char *token = strtok(buffer, " -,./\n");
        while (token) {
            if (indice == _Arvore)
                insere_ord(arvore, token, n_linhas);
            token = strtok(NULL, " -,./\n");
        }
    }
    if (indice == _Arvore) {
        int n = contar(arvore);
        printf("Numero de linhas no arquivo: %d\n", n_linhas);
        printf("Total de palavras unicas indexadas: %05d\n", n);
        printf("Altura da arvore: %05d\n", altura(arvore->raiz));
    }

    char comando[100];
    bool fim = false;
    while (!fim) {
        printf("> ");
        scanf("%s", comando);
        if (strcmp(comando, "fim") == 0) fim = true;
        else if (strcmp(comando, "busca") == 0) {
            scanf("%s", comando);
            No *p = busca(arvore, comando);
            if (p) {
                rewind(ENTRADA);
                for (int i = 0; i < p->linha; i++)
                    fgets(buffer, sizeof(buffer), ENTRADA);
                printf("%04d: %s", p->linha, buffer);
            } else printf("Palavra \'%s\' nao encontrada.\n", comando);
        }
        else printf("Opcao invalida!\n");
    }
    fclose(ENTRADA);
    destroi_arvore(arvore);
    free(arvore);
}
