#ifndef OBSTACULO_H
#define OBSTACULO_H
#include "grafico.h"

#define TOTAL_OBSTACULOS 6

struct obstaculo {
    ALLEGRO_BITMAP *imagem;
    float x; 
    float y;
    int largura;
    int altura;
};

// Funcao para carregar imagem do obstaculo
// Retorna 1 em caso de sucesso e 0 caso nao consiga carregar
int carrega_obstaculos (struct obstaculo lista[]);

// funcao para destruir o bitmap dos obstaculos
void destroi_obstaculos (struct obstaculo lista[]);

// funcao para att os obstaculos
void atualiza_obstaculos (struct obstaculo lista[], int largura_tela, int chao, unsigned int quadro);

// funcao para desenhar os obstaculos na fase
void desenha_obstaculos (const struct obstaculo lista[]);

// funcao para verificar se tocou o obstaculo 
int tocou_obstaculo (const struct personagem *jogador, const struct obstaculo lista[]);

#endif
