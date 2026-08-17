#include "labrob.h"
#include <stdio.h>
#include <stdlib.h>

struct lab *crialab (){
    struct lab *aux;

    aux = malloc (sizeof (struct lab));
    if (!aux)
        return NULL;

    aux->robos = NULL;
    return aux;
}

void cadastrar_robo (struct lab *dinf, int id, int qtd_sensores){
    struct robo *aux;

    if (!dinf){
        printf ("lab nao existe\n");
        return;
    }

    aux = malloc (sizeof (struct robo));
    if (!aux){
        printf ("sem espaco para criar novo robo\n");
        return;
    }

    aux->id = id;
    aux->conj_sens = malloc (sizeof (int) * qtd_sensores);
    if (!aux->conj_sens){
        printf ("não há espaço para esta qtd de sensores");
    }

    aux->qtd_sens = qtd_sensores;
    for (int i = 0; i < qtd_sensores; i++){
        printf ("Forneca o valor do sensor %d\n", i);
        scanf ("%d",&aux->conj_sens[i]);
    }
    
    if (!dinf->robos)
        dinf->robos = aux;

    else{
        aux->prox = dinf->robos;
        dinf->robos = aux;
    }
}

void analisa_robos (struct lab *dinf){
    struct robo *aux;
    int soma_sens;// para calcular a soma dos valores dos sensores

    if (!dinf){
        printf ("lab nao existe\n");
        return;
    }

    if (!dinf->robos){
        printf ("\nNao há robos cadastrados\n\n");
        return;
    }

    aux = dinf->robos;
    soma_sens = 0;
    while (aux != NULL){
        printf ("ROBO: %d\n", aux->id);

        for (int i = 0; i < aux->qtd_sens; i++){
            soma_sens = soma_sens + aux->conj_sens[i];
        }
        printf ("soma dos seus sensores: %d\n", soma_sens);
        printf ("endereço na memoria: %d\n", *aux->conj_sens);
        soma_sens = 0;

        aux = aux->prox;
    }    
}

void att_robo (struct lab *dinf, int id){
    struct robo *aux;

    if (!dinf){
        printf ("lab nao existe\n");
        return;
    }

    aux = dinf->robos;
    while (aux != NULL && aux->id != id){
        aux = aux->prox;
    }

    if (!aux){
        printf ("Robos nao existe no lab\n");
        return;
    }

    for (int i = 0; i < aux->qtd_sens; i++){
        printf ("Forneca o novo valor do sensor %d\n", i);
        scanf ("%d",&aux->conj_sens[i]);
    }
}