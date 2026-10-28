#include <stdio.h>
#include <stdlib.h>
#include "grafico.h"

int main(){

    al_init();
    al_install_keyboard ();
    
    // iniciar componentes 
    ALLEGRO_TIMER *tempo = al_create_timer (1.0/FPS); // criar tempo para o jogo
    ALLEGRO_EVENT_QUEUE *f_eventos = al_create_event_queue ();
    ALLEGRO_FONT *texto = al_create_builtin_font ();
    ALLEGRO_DISPLAY *tela = al_create_display (TELA_ALTURA, TELA_LARGURA); 

    // racoes que a fila de f_eventos deve registrar
    al_register_event_source (f_eventos, al_get_keyboard_event_source());
    al_register_event_source (f_eventos, al_get_display_event_source(tela));
    al_register_event_source (f_eventos, al_get_timer_event_source(tempo));

    ALLEGRO_EVENT evento;
    al_start_timer (tempo);
    while (1){
        
        al_wait_for_event (f_eventos, &evento);

        if(evento.type == FPS){
            al_clear_to_color (al_map_rgb (0, 0, 0));
            al_flip_display ();
        }   

        else if (evento.type == 42)
            break;
    }


    // liberar componetes allegro 
    al_destroy_timer (tempo);
    al_destroy_event_queue (f_eventos);
    al_destroy_font (texto);
    al_destroy_display (tela);
    return 0;
}