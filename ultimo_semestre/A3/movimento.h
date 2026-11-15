#ifndef MOVIMENTO_H
#define MOVIMENTO_H

struct movimentos {
    unsigned char esquerda;
    unsigned char direita;
    // ** unsigned char em_pe;
    unsigned char pulando;
    unsigned char abaixando;
    unsigned char interagindo;
};

struct movimentos *cria_movimentos ();

void destroi_movimentos (struct movimentos *elemento);

void esquerda (struct movimentos *elemento);

void direita (struct movimentos *elemento);

void pulando (struct movimentos *elemento);

// ** void em_pe (struct movimentos *elemento);

void abaixando (struct movimentos *elemento);

void interagindo (struct movimentos *elemento);

#endif
