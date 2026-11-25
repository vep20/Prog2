#ifndef GRAFICO_H
#define GRAFICO_H

#include <allegro5/allegro.h> // biblioteca principal de uso para allegro
#include <allegro5/allegro_image.h> // para imagens
#include <allegro5/allegro_audio.h> // para audio
#include <allegro5/allegro_font.h> // para texto 
#include <allegro5/allegro_primitives.h> // *** para formas. talvez removido
#include <allegro5/allegro_image.h> // para imagens
#include <allegro5/allegro_audio.h> // para sons
#include <stdbool.h>
#include "movimento.h"

#define FPS 30.0
#define TAM_MOVIMENTO 10 // tamanho do movimento do personagem 
#define LARGURA_FASE 6000 // tamanho total da fase
#define POSICAO_CHEGADA (LARGURA_FASE - 80)

// estrutura auxiliar para o componentes basicos e necessarios para utilizacao do allegro no projeto
struct componentes_allegro {
    ALLEGRO_DISPLAY *tela;
    ALLEGRO_TIMER *tempo;
    ALLEGRO_EVENT_QUEUE *f_eventos;
    ALLEGRO_FONT *texto;
};

// estrutura padrao do personagem 
 struct personagem {
    struct movimentos *controle; // elementos para controle do personagem 
    ALLEGRO_BITMAP *imagem_atual; // imagem atual que personagem possui
    float altura; // altura do personagem em relacao a tela
    float veloc_y; // velocidade do persoem para pulo
    unsigned char tamanho; // tamanho do personagem 
    unsigned short largura; 
    unsigned short vida;
};

// Funcao que incializa os componentes do allegro, 
// Retorna 1 em caso de sucesso e 0 em caso de falha
int inicia_allegro (struct componentes_allegro *al);

// Funcao para limpar e destruir uma estrutura allegro 
void destroi_allegro (struct componentes_allegro *al);

// Funcao para criacao de um personagem seguindo valores pre definidos, 
// Devolve uma estrutura de personagem preenchida em caso de sucesso
// ou NULL em caso de falha
struct personagem *cria_personagem (unsigned char tamanho, unsigned short largura, 
                                    float altura, unsigned short max_largura,
                                    unsigned short max_altura);

// Funcao para controle dos movimentos do personagem 
// Realiza a movimentacao em caso de sucesso
// retorna mensagem de erro se algo ocorre de errado e finaliza o programa
void movimentos_personagem (struct personagem *jogador,
                            unsigned char movimentos, unsigned char trajetoria,
                            unsigned short max_largura); 

// Funcao para limpar e destruir uma estrutura personagem 
void destroi_personagem (struct personagem *jogador);

#endif