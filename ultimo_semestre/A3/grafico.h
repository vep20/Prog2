#ifndef GRAFICO_H
#define GRAFICO_H

#include <allegro5/allegro.h> // biblioteca principal de uso para allegro
#include <allegro5/allegro_image.h> // para imagens
#include <allegro5/allegro_audio.h> // para audio
#include <allegro5/allegro_font.h> // para texto 
#include <allegro5/allegro_primitives.h> // para formas
#include <stdbool.h>
#include "movimento.h"

#define TELA_LARGURA 1920 // definicao padrao, *** provavelmente sera removido para ajustar com funcao
#define TELA_ALTURA 1080
#define FPS 30.0
#define TAM_MOVIMENTO 10 // tamanho do movimento do personagem 

// estrutura padrao do personagem 
 struct personagem {
    unsigned char tamanho; // tamanho do personagem 
    unsigned short largura; 
    unsigned short altura;
    struct movimentos *controle; // elementos para controle do personagem 
};

// Funcao para criacao de um personagem seguindo valores pre definidos, 
// Devolve uma estrutura de personagem preenchida em caso de sucesso
// ou NULL em caso de falha
struct personagem *cria_personagem (unsigned char tamanho, unsigned short largura, 
                                    unsigned short altura, unsigned short max_largura,
                                    unsigned short max_altura);

// Funcao para controle dos movimentos do personagem 
// Realiza a movimentacao em caso de sucesso
// retorna mensagem de erro se algo ocorre de errado e finaliza o programa
void movimentos_personagem (struct personagem *jogador, unsigned char movimentos, unsigned char trajetoria,
                            unsigned short max_largura, unsigned short max_altura);

// Funcao para limpar e destruir uma estrutura personagem 
void destroi_personagem (struct personagem *jogador);

#endif