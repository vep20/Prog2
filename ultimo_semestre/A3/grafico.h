#ifndef GRAFICO_H
#define GRAFICO_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h> // para imagens
#include <allegro5/allegro_audio.h> // para audio
#include <allegro5/allegro_font.h> // para texto 
#include <allegro5/allegro_primitives.h> // para formas
#include <stdbool.h>

#define TELA_LARGURA 800
#define TELA_ALTURA 60
#define FPS 60.0

enum ACOES{
    EM_PE,
    ABAIXADO,
    PULANDO,
    ANDANDO,
    INTERACAO
};

#endif