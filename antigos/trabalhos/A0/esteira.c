#include <stdio.h>
#include <stdlib.h>
#include "esteira.h"

long aleat (long min, long max){

    return min + rand () % (max - min + 1);
}

struct esteira *esteira_cria (){
    struct esteira *nova_esteira;

    nova_esteira = malloc (sizeof (struct esteira));

    if (!nova_esteira)
        return NULL;

    nova_esteira->tam = 0;
    nova_esteira->prim = NULL;

    return nova_esteira;
    
}

struct esteira *esteira_destroi (struct esteira *e){
    int aux_id;

    if (!e)
        return NULL;
    
    aux_id = 0;
    while (e->prim)
        retira_porcao (e, aux_id);

    return NULL;
}

struct porcao *cria_porcao (int uni){ //ID SERA ADICIONADO DEPOIS 
    struct porcao *nova_porcao;

    nova_porcao = mallloc (sizeof(struct porcao));
    if (!nova_porcao)
        return NULL;

    nova_porcao->uni = uni;
    nova_porcao->prox = NULL;
}

void cadastra_porcao (struct esteira *e, struct porcao *p){

    if (!e)
        return NULL;

    if (e->prim)

    
}

void retira_porcao (struct esteira *e, int id);

void imprime_esteira (struct esteira *e);

int esteira_tamanho (struct esteira *e);

long aleat (long min, long max);