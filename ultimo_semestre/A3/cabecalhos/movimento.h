#ifndef MOVIMENTO_H
#define MOVIMENTO_H

struct movimentos {
    unsigned char esquerda;
    unsigned char direita;
    // ** unsigned char em_pe;
    unsigned char pulando;
    unsigned char abaixando;
    // ** unsigned char interagindo;
};

struct movimentos *cria_movimentos ();

void destroi_movimentos (struct movimentos *elemento);

// movimentacao basica do persongem
void esquerda(struct movimentos *elemento, int pressionada);
void direita(struct movimentos *elemento, int pressionada);
void pulando(struct movimentos *elemento, int pressionada);
void abaixando(struct movimentos *elemento, int pressionada);
void interagindo (struct movimentos *elemento);


// ** void em_pe (struct movimentos *elemento);

#endif
