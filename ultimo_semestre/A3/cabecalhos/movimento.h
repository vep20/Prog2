#ifndef MOVIMENTO_H
#define MOVIMENTO_H

struct movimentos {
    unsigned char esquerda;
    unsigned char direita;
    unsigned char pulando;
    unsigned char abaixando;
};

// Funcao para add valores de movimentos ao personagem
// Retorna a estrurura movimento preenchida em caso de sucesso
// Ou NULL em caso de falha 
struct movimentos *cria_movimentos ();

// Funcao para destruir uma estrutura movimento
void destroi_movimentos (struct movimentos *elemento);

// movimentacao basica do persongem
void esquerda(struct movimentos *elemento, int pressionada);
void direita(struct movimentos *elemento, int pressionada);
void pulando(struct movimentos *elemento, int pressionada);
void abaixando(struct movimentos *elemento, int pressionada);
void interagindo (struct movimentos *elemento);


#endif
