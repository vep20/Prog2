#include <stdio.h>
#include <stdlib.h>
#include "movimento.h"


struct movimentos *cria_movimentos (){
    struct movimentos *elemento;

    elemento = (struct movimentos *) malloc (sizeof (struct movimentos));
    if (!elemento){
        fprintf (stderr, "Erro ao criar estrutura de movimentos para o elemento\n");
        return NULL;
    }

    // inicializa as variaveis de movimento do elemento
    elemento->esquerda = 0;
    elemento->direita = 0;
    // ** elemento->em_pe = 0;
    elemento->pulando = 0;
    elemento->abaixando = 0;
    // ** elemento->interagindo = 0;

    return elemento;
}

void destroi_movimentos (struct movimentos *elemento){

    free (elemento);
    elemento = NULL;
}

void esquerda(struct movimentos *elemento, int pressionada) {
    
    if (!elemento){
        fprintf (stderr, "Estrutura de elemento nao existe para movimentar\n");
        return;
    }

    elemento->esquerda = pressionada;
}

void direita(struct movimentos *elemento, int pressionada) {
    
    if (!elemento){
        fprintf (stderr, "Estrutura de elemento nao existe para movimentar\n");
        return;
    }

    elemento->direita = pressionada;
}

void pulando(struct movimentos *elemento, int pressionada) {
    
    if (!elemento){
        fprintf (stderr, "Estrutura de elemento nao existe para movimentar\n");
        return;
    }

    elemento->pulando = pressionada;
}

void abaixando(struct movimentos *elemento, int pressionada) {
    
    if (!elemento){
        fprintf (stderr, "Estrutura de elemento nao existe para movimentar\n");
        return;
    }

    elemento->abaixando = pressionada;
}


// ** void em_pe (struct movimentos *elemento){
//     elemento->em_pe = elemento->em_pe ^ 1; 
// }


// ** void interagindo (struct movimentos *elemento){
//     elemento->interagindo = elemento->interagindo ^ 1;
// }