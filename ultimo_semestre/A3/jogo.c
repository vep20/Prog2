#include <stdio.h>
#include <stdlib.h>
#include "grafico.h"


void atualiza_posicao (struct personagem *jogador, int largura_tela, int altura_tela){

    if (jogador->controle->esquerda){
        movimentos_personagem (jogador, 1, 0, largura_tela, altura_tela);
    }

    if (jogador->controle->direita){
        movimentos_personagem (jogador, 1, 1, largura_tela, altura_tela);
    }

    if (jogador->controle->pulando){
        movimentos_personagem (jogador, 1, 2, largura_tela, altura_tela);
    }

    if (jogador->controle->abaixando){
        movimentos_personagem (jogador, 1, 3, largura_tela, altura_tela);
    }
}

int main(){
    ALLEGRO_EVENT evento;
    ALLEGRO_BITMAP *imagem_menu, *imagem_chao, *imagem_fundo;
    struct personagem *jogador_1;
    struct componentes_allegro al;
    float imagem_largura, imagem_altura, coord_pes;
    int largura_tela, altura_tela, coord_x, coord_y, espaco;
    int menu, fim_de_jogo, executando, pressionada, chao; 

    if (!inicia_allegro(&al)){
        fprintf (stderr, "Erro ao iniciar allegro\n");
        return 1;
    }

    // att as dimensoes
    largura_tela = al_get_display_width(al.tela);   
    altura_tela = al_get_display_height(al.tela);

    // carrega imagem do menu
    imagem_menu = al_load_bitmap ("recursos/imagens/menu.png");
    if (!imagem_menu){
        fprintf (stderr, "Erro ao carregar imagem de fundo menu\n");
        destroi_allegro (&al);
        return 1;
    }

    imagem_chao = al_load_bitmap ("recursos/imagens/cenario/chao.png");
    if (!imagem_chao){
        fprintf (stderr, "Erro ao carregar imagem de chao\n");
        destroi_allegro (&al);
        return 1;        
    }

    imagem_fundo = al_load_bitmap ("recursos/imagens/cenario/fundo.png");
    if (!imagem_fundo){
        fprintf (stderr, "Erro ao carregar imagem de fundo do cenario\n");
        destroi_allegro (&al);
        return 1;
    }

    // cria valores de elementos para personagem principal
    jogador_1 = cria_personagem (20, largura_tela/2, altura_tela/2, largura_tela, altura_tela);
    if (!jogador_1){
        fprintf (stderr, "Erro ao criar o personagem principal\n");
        destroi_allegro (&al);
        return 1;
    }

    // valores variaveis iniciais
    executando = 1;
    menu = 1;
    fim_de_jogo = 0;
    while (executando){
        al_wait_for_event (al.f_eventos, &evento);

        // att tela conforme quadros predefinidos ant (ou seja 30 fps)
        if(evento.type == ALLEGRO_EVENT_TIMER){
            
            // limpa a tela a cada quadro
            al_clear_to_color (al_map_rgb (255, 255, 255));

            // verifica se esta na tela de menu 
            if (menu){
                al_draw_scaled_bitmap (imagem_menu, 0, 0,
                                        al_get_bitmap_width (imagem_menu),
                                        al_get_bitmap_height (imagem_menu), 
                                        0, 0, largura_tela, altura_tela, 0);
                
                // acha as coordenadas para incluir o texto de aviso de tecla
                coord_x = largura_tela / 2; 
                coord_y = altura_tela * 2 / 3; // ***coloca a opção Iniciar a dois terços da altura da janela, contando a partir do topo.
                espaco = 2 * al_get_font_line_height (al.texto); // altura da linha + 2 linhas em branco

                // avisos de teclas escrito como texto
                al_draw_text (al.texto, al_map_rgb (255, 215, 100), coord_x, coord_y, 
                                ALLEGRO_ALIGN_CENTER, "[Enter] INICIAR");

                al_draw_text (al.texto, al_map_rgb (255, 255, 255), coord_x, coord_y + espaco,
                                 ALLEGRO_ALIGN_CENTER, "[Esc] SAIR");
            }

            // indicacao de fim de jogo 
            else if (fim_de_jogo){
                al_draw_text (al.texto, al_map_rgb (255, 0, 0),
                            largura_tela / 2, altura_tela / 2,
                            ALLEGRO_ALIGN_CENTRE, "FIM DE JOGO");
            }
            
            // carregamento normal da fase att a cada fps
            else{
                atualiza_posicao (jogador_1, largura_tela, altura_tela);
                
                // carrega imagem de fundo 
                al_draw_scaled_bitmap (imagem_fundo, 0, 0,
                                        al_get_bitmap_width (imagem_fundo),
                                        al_get_bitmap_height (imagem_fundo), 
                                        0, 0, largura_tela, altura_tela, 0);

                // criando cenario e elementos da tela
                chao = altura_tela - 160; // cria um chao 160 pixels acima da parte inferior    
                // desenho do chao 
                al_draw_scaled_bitmap (imagem_chao, 0, 0, 
                                        al_get_bitmap_width (imagem_chao),
                                        al_get_bitmap_height (imagem_chao),
                                        0, chao, largura_tela, altura_tela - chao, 0);
                         

                // desenho do personagem principal 
                imagem_largura = 96.0f;
                imagem_altura = 90.0f;
                coord_pes = jogador_1->altura + jogador_1->tamanho / 2.0f;

                al_draw_scaled_bitmap (jogador_1->imagem_atual, 0, 0,
                                        al_get_bitmap_width (jogador_1->imagem_atual),
                                        al_get_bitmap_height (jogador_1->imagem_atual),
                                        jogador_1->largura - imagem_largura / 2.0f,
                                        coord_pes - imagem_altura, 
                                        imagem_largura, imagem_altura, 0);                                                                          
            }

            al_flip_display ();
        }

        // redimenciona janela
        else if (evento.type == ALLEGRO_EVENT_DISPLAY_RESIZE){

            al_acknowledge_resize (al.tela);

            // att valores da tela
            largura_tela = al_get_display_width (al.tela);
            altura_tela = al_get_display_height (al.tela);

            chao = altura_tela - 160;
        }
        
        // entradas teclado
        else if ((evento.type == ALLEGRO_EVENT_KEY_DOWN) 
                    || (evento.type == ALLEGRO_EVENT_KEY_UP)){ // 10 ou 12
            
            pressionada = (evento.type == ALLEGRO_EVENT_KEY_DOWN);
            
            // caso para eventos de menu
            if (menu){
                if (pressionada){
                    if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER){
                        menu = 0;
                    }
                    else if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                        executando = 0;
                    }
                }   
                continue; // ja vai para prox evento
            }

            else{
                // casos para eventos de movimentacao
                switch (evento.keyboard.keycode){
                    case ALLEGRO_KEY_A:
                        esquerda (jogador_1->controle, pressionada);
                        break;
                        
                    case ALLEGRO_KEY_D:
                        direita (jogador_1->controle, pressionada);
                        break;

                    case ALLEGRO_KEY_W:
                        pulando (jogador_1->controle, pressionada);
                        break;

                    case ALLEGRO_KEY_S:
                        abaixando (jogador_1->controle, pressionada);
                        break;
                        
                    // **** remover posteriormente 
                    case ALLEGRO_KEY_X:
                        if (pressionada)
                            fim_de_jogo = 1;                    
                        break;
                    
                    default:
                        break;
                }
            }
        }
        

        else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){ //42
            break;
        }
    }

    // ** verificar para talvez add em destroi allegro ou fazer funcao propria para destruir imagens
    al_destroy_bitmap (imagem_menu);
    al_destroy_bitmap (imagem_chao);
    // liberar estrutura peronagem
    destroi_personagem (jogador_1);
    // liberar componetes allegro 
    destroi_allegro (&al);

    return 0;
}