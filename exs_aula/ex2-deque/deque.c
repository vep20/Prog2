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

struct deque *destroi_deque (struct deque *d){

    if (!d)
        return NULL;

    while (tam (d))
        remove_ini (d);

    free(d);
    return NULL;
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

    //verifica se há itens no deque
    if (d->tam == 0){
        aux->prox = NULL;
        d->pri = aux;
        d->ult = aux;
    }

    //insere no inicio
    else{
        aux->prox = d->pri;
        d->pri->ant = aux;
        d->pri = aux;//atualiza a primeira posição
    }
    
    d->tam++;
}

void insere_fim (struct deque *d, char item){
    struct deque_nodo *aux;

    if (!d)
        return;

    aux = malloc (sizeof (struct deque_nodo));
    if (!aux)
        return;

    aux->item = item;    
    aux->prox = NULL;

    //verifica se há itens no deque
    if (d->tam == 0){
        aux->ant = NULL;
        d->pri = aux;
        d->ult = aux;
    }

    //insere no fim
    else{
        aux->ant = d->ult;
        d->ult->prox = aux;
        d->ult = aux;//atualiza a ultima posição 
    }
    
    d->tam++;
}

int tam (struct deque *d){

    if(!d)
        return -1;
    return d->tam;
}

void remove_ini (struct deque *d){
    struct deque_nodo *aux;

    if (!d || !d->pri)
        return;

    aux = d->pri;
    d->pri = d->pri->prox;
    d->tam--;
    
    free (aux);
}

void remove_fim (struct deque *d){
    struct deque_nodo *aux;

    if (!d || !d->ult)
        return;

    aux = d->ult;
    d->ult = d->ult->ant;
    d->tam--;

    free(aux);
}