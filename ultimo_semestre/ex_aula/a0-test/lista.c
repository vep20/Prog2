#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // biblioteca poara aleat

/* retorna um número aleatório entre min e max, inclusive. */
long aleat (long min, long max){
  long n_aleat; 

  /*Forma de gerar numeros aleatorios entre min e max includos eles mesmos*/
  n_aleat = min + rand() % (max - min + 1); 
  return n_aleat;
}

struct lista *cria_dia (){
    struct lista *aux;

    aux = malloc (sizeof (struct lista));
    if (!aux)
        return NULL;

    aux->qtd_maquina = aleat (1, 2); // qtd aleatoria de maquinas criadas no dia
    
    // inicializa um sentinela
    aux->senti = malloc (sizeof (struct maquina));
    if(!aux->senti){
        printf ("erro ao criar sentinela\n");
        return NULL;
    }
    aux->senti->id = 0;
    aux->senti->prob = 0;
    aux->senti->ant = aux->senti;
    aux->senti->prox = aux->senti;

    return aux;
}

struct maquina *cria_maquina (struct lista *dia_atual, int id){
    struct maquina *aux;

    aux = malloc (sizeof (struct maquina));
    if (!aux)
        return NULL;

    aux->id = id;
    aux->prob = aleat (0, 100);

    return aux;
}

void add_maquina (struct lista *dia_atual, struct maquina *maquina_atual){
    struct maquina *aux;

    aux = dia_atual->senti->prox;

    while (aux != dia_atual->senti && aux->prob >= maquina_atual->prob)
        aux = aux->prox;

    maquina_atual->prox = aux;
    maquina_atual->ant = aux->ant;

    aux->ant->prox = maquina_atual;
    aux->ant = maquina_atual;
}