#ifndef GRAFICO_H
#define GRAFICO_H

#include <allegro5/allegro.h> // biblioteca principal de uso para allegro
#include <allegro5/allegro_image.h> // para imagens
#include <allegro5/allegro_audio.h> // para audio
#include <allegro5/allegro_font.h> // para texto 
#include <allegro5/allegro_primitives.h> // para formas
#include <stdbool.h>
#include "movimento.h"

#define TELA_LARGURA 1920
#define TELA_ALTURA 1080
#define FPS 30.0
#define MOVIMENTO 20 // tamanho do movimento do personagem 
struct personagem {
    unsigned char tamanho; // tamanho do personagem 
    unsigned short largura; 
    unsigned short altura;
    struct movimentos *controle; // elementos para controle do personagem 
};


#endif