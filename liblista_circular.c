#include <stdlib.h>
#include "liblista_circular.h"
/* 
 * Cria uma Lista vazia 
*/
lista_t *lista_cria ()
{
    lista_t *l;
    nodo_t *sent;

    if (! (l = malloc(sizeof(lista_t))))
        return 0;
    
    if (! (sent = malloc(sizeof(nodo_t))))
        return 0;

    l->ini = sent;
    sent->prev = sent;
    sent->prox = sent;
    sent->elemento = NULL;

    return l;
}

/* 
 * Destroi a Lista e a aponta para NULL
*/ 
void lista_destroi (lista_t **l)
{
    nodo_t *aux;

    while (!lista_vazia(*l))
    {
        aux = (*l)->ini->prox;
        (*l)->ini->prox = aux->prox;
        aux->prox->prev = (*l)->ini;
        free (aux->elemento);
        free (aux);
    }
    free ((*l)->ini->elemento);
    free ((*l)->ini);
    free (l);
}

/* 
 * Adiciona um elemento em ordem de acordo com o valor elemento->chave na Lista. 
 * Retorna 1 em caso de sucesso e 0 caso contrario.
*/
int lista_insere_ordenado (lista_t *l, elemento_t *elemento)
{
    nodo_t *novo;
    nodo_t *aux;

    if (! (novo = malloc(sizeof(nodo_t))))
        return 0;

    novo->elemento = elemento;
    /* Sentinela recebe elemento */
    l->ini->elemento = elemento;
    aux = l->ini->prox;

    while (elemento->chave > aux->elemento->chave)
        aux = aux->prox;

    novo->prev = aux->prev;
    novo->prox = aux;

    aux->prev = novo;
    novo->prev->prox = novo;

    return 1;
}

/* 
 * Retira o elemento da Lista e a mantem em ordem.
 * Retorna 1 em caso de sucesso e 0 caso elemento nao esteja na Lista.
*/
int lista_remove_ordenado (lista_t *l, elemento_t *elemento)
{
    nodo_t *aux;

    /* Sentinela recebe elemento */
    l->ini->elemento = elemento;

    aux = l->ini->prox;

    while (elemento->chave != aux->elemento->chave)
        aux = aux->prox;
    
    if (elemento->chave == l->ini->elemento->chave)
        return 0;

    aux->prev->prox = aux->prox;
    aux->prox->prev = aux->prev;

    free (aux->elemento);
    free (aux);

    return 1;
}

/* Retorna 1 se a lista esta vazia e 0 caso contrario */
int lista_vazia (lista_t *l)
{
    if (l->ini->prox != l->ini->prev)
        return 0;

    return 1;
}