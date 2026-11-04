#include <stdio.h>
#include "movimento.h"


struct movimentos *cria_movimentos (){
    struct movimentos *elemento;

    elemento = (struct movimentos *) malloc (sizeof (struct movimentos));
    if (!elemento){
        fprintf (stderr, "erro ao criar estrutura de movimentos para o elemento\n");
    }

    // inicializa as variaveis de movimento do elemento
    elemento->direita = 0;
    elemento->esquerda = 0;
    elemento->em_pe = 0;
    elemento->pulando = 0;
    elemento->abaixando = 0;
    elemento->interagindo = 0;

    return elemento;
}

void destroi_movimentos (struct movimentos *elemento){
    free (elemento);
}

void direita (struct movimentos *elemento){
    elemento->direita = elemento->direita ^ 1;
}

void esquerda (struct movimentos *elemento){
    elemento->esquerda = elemento->esquerda ^ 1;
}


void pulando (struct movimentos *elemento){
    elemento->pulando = elemento->pulando ^ 1;
}

void em_pe (struct movimentos *elemento){
    elemento->em_pe = elemento->em_pe ^ 1; 
}

void abaixando (struct movimentos *elemento){
    elemento->abaixando = elemento->abaixando ^ 1;
}

void interagindo (struct movimentos *elemento){
    elemento->interagindo = elemento->interagindo ^ 1;
}