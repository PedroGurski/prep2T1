#include <stdio.h>
#include <stdlib.h>
#include "liblista_circular.h"

void imprime_lista(lista_t *lista) {
    nodo_t *atual = lista->ini->prox;

    printf("\nLista: ");
    while (atual != lista->ini) {
        printf("%d ", atual->elemento->chave);
        atual = atual->prox;
    }
    printf("\n");
}

int main() {
    lista_t *lista = lista_cria();

    int opcao;
    while (1) {
        printf("\nEscolha uma opção:\n");
        printf("1. Inserir elemento\n");
        printf("2. Remover elemento\n");
        printf("3. Destruir lista e sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            elemento_t *elemento = malloc(sizeof(elemento_t));
            printf("Digite o valor do elemento: ");
            scanf("%d", &elemento->chave);
            lista_insere_ordenado(lista, elemento);
            imprime_lista(lista);
        } else if (opcao == 2) {
            if (lista_vazia(lista)) {
                printf("Lista vazia. Nenhum elemento para remover.\n");
                continue;
            }

            int chave_remover;
            printf("Digite o valor do elemento a ser removido: ");
            scanf("%d", &chave_remover);

            elemento_t *elemento_remover = malloc(sizeof(elemento_t));
            elemento_remover->chave = chave_remover;
            if (lista_remove_ordenado(lista, elemento_remover)) {
                printf("Elemento removido com sucesso.\n");
            } else {
                printf("Elemento não encontrado na lista.\n");
            }
            imprime_lista(lista);
            free(elemento_remover);
        } else if (opcao == 3) {
            lista_destroi(&lista);
            printf("Lista destruída. Saindo do programa.\n");
            break;
        } else {
            printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}