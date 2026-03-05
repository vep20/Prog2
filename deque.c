#include "deque.h"

struct deque *cria(){
    struct deque *aux;

    aux = malloc (sizeof (struct deque));
    if (!aux)
        return NULL;

    aux->tam = 0;
    aux->pri = NULL;
    aux->ult = NULL;

    return aux;
}

void insere_inicio (struct deque *d, char item){
    struct deque_nodo *aux;

    if (!d)
        return;

    aux = malloc (sizeof (struct deque_nodo));
    if (!aux)
        return;

    aux->item = item;    
    aux->ant = NULL;

    if (d->tam == 0){
        aux->prox = NULL;
        d->pri = aux;
        d->ult = aux;
    }

    else {
        aux->prox 
    }
    
    d->pri++;
}