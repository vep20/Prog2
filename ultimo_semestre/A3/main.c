#include <stdio.h>
#include <stdlib.h>
#include "grafico.h"

void atualiza_posicao (struct personagem *jogador){

    if (jogador->controle->esquerda){
        movimentos_personagem (jogador, 1, 0, TELA_LARGURA, TELA_ALTURA);
    }

    if (jogador->controle->direita){
        movimentos_personagem (jogador, 1, 1, TELA_LARGURA, TELA_ALTURA);
    }

    if (jogador->controle->pulando){
        movimentos_personagem (jogador, 1, 2, TELA_LARGURA, TELA_ALTURA);
    }

    if (jogador->controle->abaixando){
        movimentos_personagem (jogador, 1, 3, TELA_LARGURA, TELA_ALTURA);
    }
}

int main(){
    struct personagem *jogador_1;

    al_init();

    al_init_primitives_addon ();
    al_install_keyboard ();
    
    // iniciar componentes 
    ALLEGRO_TIMER *tempo = al_create_timer (1.0/FPS); // criar tempo para o jogo
    ALLEGRO_EVENT_QUEUE *f_eventos = al_create_event_queue ();
    // ** ALLEGRO_FONT *texto = al_create_builtin_font ();
    ALLEGRO_DISPLAY *tela = al_create_display (TELA_ALTURA, TELA_LARGURA); 

    // acoes que a fila de f_eventos deve registrar
    al_register_event_source (f_eventos, al_get_keyboard_event_source());
    al_register_event_source (f_eventos, al_get_display_event_source(tela));
    al_register_event_source (f_eventos, al_get_timer_event_source(tempo));

    jogador_1 = cria_personagem (20, TELA_LARGURA/2, TELA_ALTURA/2, TELA_LARGURA, TELA_ALTURA);
    if (!jogador_1){
        return 1;
    }

    ALLEGRO_EVENT evento;
    al_start_timer (tempo);
    while (1){
        al_wait_for_event (f_eventos, &evento);

        if(evento.type == FPS){
            atualiza_posicao (jogador_1);
            al_clear_to_color (al_map_rgb (0, 0, 0));
            al_draw_filled_rectangle (
                jogador_1->largura - jogador_1->tamanho/2,
                jogador_1->altura - jogador_1->tamanho/2,
                jogador_1->largura + jogador_1->tamanho/2,
                jogador_1->altura + jogador_1->tamanho/2,
                al_map_rgb (255, 0, 0)
            );
            al_flip_display ();
        }
        
        else if ((evento.type == 10) || (evento.type == 12)){
            
            switch (evento.keyboard.keycode){
                case ALLEGRO_KEY_A:
                    esquerda (jogador_1->controle);
                    break;
                    
                case ALLEGRO_KEY_D:
                    direita (jogador_1->controle);
                    break;

                case ALLEGRO_KEY_W:
                    pulando (jogador_1->controle);
                    break;

                case ALLEGRO_KEY_S:
                    abaixando (jogador_1->controle);
                    break;
                    
                default:
                    break;
            }

        }

        else if (evento.type == 42){
            break;
        }
    }

    destroi_personagem (jogador_1);

    // liberar componetes allegro 
    al_destroy_timer (tempo);
    al_destroy_event_queue (f_eventos);
    // al_destroy_font (texto);
    al_destroy_display (tela);

    return 0;
}