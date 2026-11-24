#include <stdio.h>
#include "grafico.h"

int inicia_allegro (struct componentes_allegro *al){
    ALLEGRO_MONITOR_INFO info;
    int largura, altura;

    // inicializa ponteiros para evitar acessos indevidos
    al->tela = NULL;
    al->tempo = NULL;
    al->f_eventos = NULL;
    al->texto = NULL;

    if (!al_init()){
        fprintf (stderr, "Erro ao iniciar o Allegro\n");
        return 0;
    }

    if (!al_install_keyboard()){
        fprintf (stderr, "Erro ao instalar o teclado\n");
        destroi_allegro (al);
        return 0;
    }

    // ** talvez sera removido
    if (!al_init_primitives_addon()){
        fprintf (stderr, "Erro ao iniciar o inclusor de primitivas\n");
        destroi_allegro (al);
        return 0;
    }

    if(!al_init_image_addon()){
        fprintf (stderr, "Erro ao iniciar inclusor de imagens\n");
        destroi_allegro (al);
        return 0;
    }

    al_init_font_addon();

    // obter resolucao max do monitor
    if (!al_get_monitor_info(0, &info)){
        fprintf (stderr, "Erro ao obter a resolucao do monitor\n");
        destroi_allegro (al); 
        return 0;
    }

    largura = info.x2 - info.x1;
    altura = info.y2 - info.y1;
    // permitir redimensionar tela
    al_set_new_display_flags (ALLEGRO_RESIZABLE | ALLEGRO_MAXIMIZED);

    al->tela = al_create_display(largura, altura);
    if (!al->tela){
        fprintf (stderr, "Erro ao criar a janela\n");
        destroi_allegro (al);
        return 0;
    }

    al->tempo = al_create_timer(1.0 / FPS);
    if (!al->tempo){
        fprintf (stderr, "Erro ao criar o timer\n");
        destroi_allegro (al);
        return 0;
    }

    al->f_eventos = al_create_event_queue();
    if (!al->f_eventos){
        fprintf (stderr, "Erro ao criar a fila de eventos\n");
        destroi_allegro (al);
        return 0;
    }

    al->texto = al_create_builtin_font();
    if (!al->texto){
        fprintf (stderr, "Erro ao criar a fonte\n");
        destroi_allegro (al);
        return 0;
    }

    // acoes que a fila de f_eventos deve registrar
    al_register_event_source(al->f_eventos, al_get_keyboard_event_source());
    al_register_event_source(al->f_eventos, al_get_display_event_source(al->tela));
    al_register_event_source(al->f_eventos, al_get_timer_event_source(al->tempo));
    al_start_timer(al->tempo);
    
    return 1;
}

void destroi_allegro(struct componentes_allegro *al){

    if (al->f_eventos)
        al_destroy_event_queue(al->f_eventos);

    if (al->tempo)
        al_destroy_timer(al->tempo);

    if (al->texto)
        al_destroy_font(al->texto);

    if (al->tela)
        al_destroy_display(al->tela);

    al->tela = NULL;
    al->tempo = NULL;
    al->f_eventos = NULL;
    al->texto = NULL;
}

struct personagem *cria_personagem (unsigned char tamanho, unsigned short largura, 
                                    unsigned short altura, unsigned short max_largura,
                                    unsigned short max_altura){
    struct personagem *novo_jogador;
    
    // verificacao de posicoes 
    if ((largura - tamanho/2 < 0) || (largura + tamanho/2 > max_largura)){
        return NULL;
    }
    if ((altura - tamanho/2 < 0) || (altura + tamanho /2 > max_altura)){
        return NULL;
    }

    // tenta crar novo personagem
    novo_jogador = (struct personagem *) malloc (sizeof (struct personagem));
    if (!novo_jogador){
        fprintf (stderr, "erro ao criar estrutura personagem\n");
        return NULL;
    }

    // preenche a estrutura 
    novo_jogador->tamanho = tamanho;
    novo_jogador->largura = largura;
    novo_jogador->altura = altura;
    novo_jogador->vida = 10;
    
    // tenta criar os movimentos para estrutura
    novo_jogador->controle = cria_movimentos ();
    if (!novo_jogador->controle){
        fprintf (stderr, "Erro ao criar movimentos para o personagem, estrutura sera limpa\n");
        destroi_personagem (novo_jogador);
        return NULL;
    }

    novo_jogador->imagem_atual = al_load_bitmap ("recursos/imagens/personagem/em_pe.png");
    if (!novo_jogador->imagem_atual){
        fprintf (stderr,"Erro ao carregar imagem inicial em pe do personagem\n");
        destroi_personagem (novo_jogador);
        return NULL;
    }

    return novo_jogador;
}


void movimentos_personagem (struct personagem *jogador, unsigned char movimentos, unsigned char trajetoria,
                            unsigned short max_largura, unsigned short max_altura){
                
    switch (trajetoria){

        // verifica se e possivel a movimentacao em largura para esquerda
        case 0:
            if ((jogador->largura - movimentos * TAM_MOVIMENTO) - jogador->tamanho/2 >= 0){
                jogador->largura -= movimentos * TAM_MOVIMENTO;
            }
            break;

        // verifica se e possivel a movimentacao em largura para direita
        case 1:
            if ((jogador->largura + movimentos * TAM_MOVIMENTO) + jogador->tamanho/2 <= max_largura){
                jogador->largura += movimentos * TAM_MOVIMENTO;
            }
            break;
        
        // verifica se e possivel a movimentacao em largura para cima        
        case 2:
            if ((jogador->altura - movimentos * TAM_MOVIMENTO) - jogador->tamanho/2 >= 0){
                jogador->altura -= movimentos * TAM_MOVIMENTO;
            }
            break;

        // verifica se e possivel a movimentacao em largura para baixo
        case 3:
            if ((jogador->altura + movimentos * TAM_MOVIMENTO) + jogador->tamanho/2 <= max_altura){
                jogador->altura += movimentos * TAM_MOVIMENTO;
            }
            break;

        default:
            break;
    }
}

void destroi_personagem (struct personagem *jogador){

    destroi_movimentos (jogador->controle);
    if (jogador->imagem_atual){
        al_destroy_bitmap (jogador->imagem_atual);
    }
    free (jogador);
}