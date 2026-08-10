// AULA 18/05


#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>      // Para imagens
#include <allegro5/allegro_primitives.h> // Para formas geométricas
#include <allegro5/allegro_font.h>       // Para textos

// PROGRAMA PASSADO VIA SLIDE PARA ALLEGRO4
// #include <allegro.h>
// int main() {
// allegro_init();
// install_keyboard();
// set_color_depth(32);
// set_gfx_mode(GFX_AUTODETECT_WINDOWED,640,480,0,0);
// BITMAP *img = create_bitmap(640,480); /* Cria o BITMAP */
// while (!key[KEY_ESC]) {
// clear_bitmap(img);
// line(img, 10,10, 100,100, makecol(255,0,0 ) ); /* Define dimensão e cor da linha */
// };
// Return 0;
// }
// END_OF_MAIN()

int main (){

    al_init(); // função que inicia a biblioteca
    al_init();
    al_init_image_addon();
    al_init_primitives_addon();
    // al_init_font_addon(); - não necessario neste programa
    
    // mudança para não ser necessario definir profundidade de cores
    ALLEGRO_DISPLAY *display = al_create_display(640, 480);

    // criasse uma fila de eventos ao inves de um loop e 
    // registra o que vier do teclado e a janela nessa fila
    // O loop agora roda até um evento de fechar a janela ou apertar ESC ocorrer
    al_install_keyboard();
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));

    // O conceito de PALETTE não é mais necessário para imagens 
    // modernas. Usa-se ALLEGRO_BITMAP, al_load_bitmap(), 
    // al_draw_bitmap(), e para limpar a tela usa-se al_clear_to_color().
    ALLEGRO_BITMAP *img = al_load_bitmap("c:\\teste.bmp");

    // al_clear_to_color(al_map_rgb(0, 0, 0)); // Limpa a tela com a cor preta
    // al_draw_bitmap(img, 30, 80, 0); // Desenha a imagem na posição x=30, y=80

    // Loop Principal
    while (executando) {
        ALLEGRO_EVENT evento;
        // Espera até ter um evento, mas atualiza a tela enquanto isso
        while (al_get_next_event(queue, &evento)) {
            // Se o usuário clicar no 'X' da janela
            if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                executando = false;
            }
            // Se o usuário apertar uma tecla
            if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    executando = false;
                }
            }
        }

        // --- Área de Desenho ---
        
        // Limpa a tela (fundo preto)
        al_clear_to_color(al_map_rgb(0, 0, 0));

        // Desenha formas geométricas
        al_draw_line(10, 10, 100, 100, al_map_rgb(255, 0, 0), 2.0);
        al_draw_filled_rectangle(150, 150, 250, 250, al_map_rgb(0, 255, 0));
        al_draw_circle(400, 100, 50, al_map_rgb(0, 0, 255), 3.0);

        // Desenha o bitmap (se ele foi carregado com sucesso)
        if (img) {
            al_draw_bitmap(img, 30, 30, 0);
        }

        // Atualiza a tela ("flip")
        al_flip_display();
    }

    // 4. Limpeza de Memória (Destrutores em vez de END_OF_MAIN)
    if (img) al_destroy_bitmap(img);
    al_destroy_event_queue(queue);
    al_destroy_display(display);

    return 0;
}