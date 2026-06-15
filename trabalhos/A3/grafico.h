#ifndef GRAFICO_H
#define GRAFICO_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>      // Para imagens
#include <allegro5/allegro_primitives.h> // Para formas geométricas
#include <allegro5/allegro_font.h>       // Para textos
#include <stdbool.h>

// constantes do jogo 
#define TELA_LARGURA 800
#define TELA_ALTURA 60
#define FPS 60.0 

// lista de nomes representandos inteiros para as acoes do personagem
enum ACOES {
    EM_PE, 
    ANDANDO,
    PULANDO,
    ABAIXANDO, 
    INTERAGINDO
};

#endif