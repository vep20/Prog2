#include <stdio.h>
#include <math.h>
#include "obstaculo.h"

struct tipo_obstaculo {
    const char *arquivo;
    float posicao;          // fracao da largura da janela 
    int largura, altura;
    int distancia_chao;     // dos pes do obstaculo ate o chao 
    int amplitude;          // deslocamento horizontal em pixels 
};

static const struct tipo_obstaculo tipos[TOTAL_OBSTACULOS] = {
    {"espinhos",  0.19f, 45, 32,  0,  0},
    {"tronco",    0.32f, 42, 42,  0, 21},
    {"vespa",     0.46f, 50, 40, 88, 14},
    {"cogumelo",  0.60f, 36, 36,  0,  0},
    {"morcego",   0.74f, 60, 34, 88, 18},
    {"cobra",     0.88f, 40, 40,  0,  0}
};

int carrega_obstaculos (struct obstaculo lista[]){
    char caminho[128];

    for (int i = 0; i < TOTAL_OBSTACULOS; i++){
        
        snprintf(caminho, sizeof caminho, "recursos/imagens/obstaculo/%s.png", tipos[i].arquivo);
        lista[i].imagem = al_load_bitmap(caminho);

        if (!lista[i].imagem){
            fprintf(stderr, "Erro ao carregar %s\n", caminho);
            return 0;
        }
        lista[i].largura = tipos[i].largura;
        lista[i].altura = tipos[i].altura;
    }

    return 1;
}

void destroi_obstaculos (struct obstaculo lista[]){

    for (int i = 0; i < TOTAL_OBSTACULOS; i++){
        if (lista[i].imagem){
            al_destroy_bitmap(lista[i].imagem);
        }
    }
}

void atualiza_obstaculos (struct obstaculo lista[], int largura_tela, int chao, unsigned int quadro){
    float oscilacao;
    
    oscilacao = sinf((quadro % 120u) * (6.2831853f / 120.0f));

    for (int i = 0; i < TOTAL_OBSTACULOS; i++){
        lista[i].x = largura_tela * tipos[i].posicao - lista[i].largura / 2.0f
                     + tipos[i].amplitude * oscilacao;
        lista[i].y = chao - tipos[i].distancia_chao - lista[i].altura;
    }
}

void desenha_obstaculos (const struct obstaculo lista[]){

    for (int i = 0; i < TOTAL_OBSTACULOS; i++){
        const struct obstaculo *o = &lista[i];
        al_draw_scaled_bitmap(o->imagem, 0, 0, 
                              al_get_bitmap_width(o->imagem),
                              al_get_bitmap_height(o->imagem), 
                              o->x, o->y, o->largura, o->altura, 0);
    }
}

int tocou_obstaculo (const struct personagem *jogador, const struct obstaculo lista[]){
    float pes, topo, esquerda, direita;

    pes = jogador->altura + jogador->tamanho / 2.0f;

    if (jogador->controle->abaixando) {
        topo = pes - 75;
    } 
    else {
        topo = pes - 106;
    }
    
    esquerda = jogador->largura - 18;
    direita = jogador->largura + 18;

    for (int i = 0; i < TOTAL_OBSTACULOS; i++){
        const struct obstaculo *o = &lista[i];
        if (direita > o->x && esquerda < o->x + o->largura &&
            pes > o->y && topo < o->y + o->altura)
            return 1;
    }

    return 0;
}
