#include <stdio.h>
#include <stdlib.h>
#include "grafico.h"
#include "obstaculo.h"


void atualiza_posicao (struct personagem *jogador, int largura_tela, int chao){
    float centro_chao;

    if (jogador->controle->esquerda){
        movimentos_personagem (jogador, 1, 0, largura_tela);
    }

    if (jogador->controle->direita){
        movimentos_personagem (jogador, 1, 1, largura_tela);
    }

    // centralizacao do personagem
    centro_chao = chao - jogador->tamanho / 2.0f;
    jogador->altura += jogador->veloc_y;
    jogador->veloc_y += 1.0f;

    // declinio do pulo
    if (jogador->altura >= centro_chao){
        jogador->altura = centro_chao;
        jogador->veloc_y = 0.0f;
    }
}

int main(void){
    ALLEGRO_EVENT evento;
    ALLEGRO_BITMAP *imagem_menu, *imagem_chao, *imagem_fundo;
    ALLEGRO_BITMAP *andando1, *andando2;
    ALLEGRO_BITMAP *salto, *agachado;
    ALLEGRO_BITMAP *pose;
    struct personagem *jogador_1;
    struct componentes_allegro al;
    struct obstaculo obstaculos[TOTAL_OBSTACULOS];
    float imagem_largura, imagem_altura, coord_pes;
    int largura_tela, altura_tela, coord_x, coord_y;
    int menu, fim_de_jogo, executando, pressionada, chao, andando, espaco; 
    int protecao, venceu;
    unsigned int quadro;

    if (!inicia_allegro(&al)){
        fprintf (stderr, "Erro ao iniciar allegro\n");
        return 1;
    }

    // att as dimensoes
    largura_tela = al_get_display_width(al.tela);   
    altura_tela = al_get_display_height(al.tela);
    chao = altura_tela - 160; // cria um chao 160 pixels acima da parte inferior

    // carrega imagens necessarias para o jogo
    imagem_menu = al_load_bitmap ("recursos/imagens/menu.png");
    imagem_chao = al_load_bitmap ("recursos/imagens/cenario/chao.png");
    imagem_fundo = al_load_bitmap ("recursos/imagens/cenario/fundo.png");
    andando1 = al_load_bitmap ("recursos/imagens/personagem/andando1.png");
    andando2 = al_load_bitmap ("recursos/imagens/personagem/andando2.png");
    agachado = al_load_bitmap ("recursos/imagens/personagem/abaixando.png");
    salto = al_load_bitmap ("recursos/imagens/personagem/pulando.png");
    jogador_1 = cria_personagem(20, 100, chao - 10, largura_tela, altura_tela);

    if (!imagem_menu || !imagem_chao || !imagem_fundo){
        fprintf (stderr, "Erro ao carregar menu, chao ou fundo\n");
        return 1;
    } 
    else if (!andando1 || !andando2 || !agachado || !salto){
        fprintf(stderr, "Erro ao carregar as poses do personagem\n");
        return 1;
    } 
    else if (!jogador_1){
        fprintf(stderr, "Erro ao criar o personagem principal\n");
        return 1;
    } 
    else if (!carrega_obstaculos (obstaculos)){
        return 1;
    }

    // valores variaveis iniciais
    executando = 1;
    menu = 1;
    fim_de_jogo = 0;
    andando = 0;
    protecao = 0;
    venceu = 0;
    quadro = 0;
    while (executando){
        al_wait_for_event (al.f_eventos, &evento);

        // att tela conforme quadros predefinidos ant (ou seja 30 fps)
        if (evento.type == ALLEGRO_EVENT_TIMER){
            
            // limpa a tela a cada quadro
            al_clear_to_color (al_map_rgb (0, 0, 0));

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
                            ALLEGRO_ALIGN_CENTRE, venceu ? "VOCE VENCEU!" : "FIM DE JOGO");

                al_draw_text(al.texto, al_map_rgb(60, 60, 60), largura_tela / 2,
                             altura_tela / 2 + 24, ALLEGRO_ALIGN_CENTRE, "[Esc] SAIR");
            }
            
            // carregamento normal dos elementos e imagens desenhadas
            else{
                atualiza_posicao (jogador_1, largura_tela, chao);
                atualiza_obstaculos (obstaculos, largura_tela, chao, quadro++);

                if (protecao > 0)
                    protecao--;
                if (protecao == 0 && tocou_obstaculo (jogador_1, obstaculos)){
                    jogador_1->vida--;
                    protecao = (int)FPS;
                }

                if (jogador_1->vida == 0)
                    fim_de_jogo = 1;
                else if (jogador_1->largura + jogador_1->tamanho / 2 >= largura_tela){
                    venceu = 1;
                    fim_de_jogo = 1;
                }

                // Apenas a paisagem desliza suavemente com o jogador.
                float deslocamento = 64.0f * jogador_1->largura / largura_tela;
                // carrega imagem de fundo 
                al_draw_scaled_bitmap (imagem_fundo, 0, 0,
                                        al_get_bitmap_width (imagem_fundo),
                                        al_get_bitmap_height (imagem_fundo), 
                                        -deslocamento, 0, largura_tela + 64, altura_tela, 0);

                // criando cenario e elementos da tela   
                // desenho do chao 
                al_draw_scaled_bitmap (imagem_chao, 0, 0, 
                                        al_get_bitmap_width (imagem_chao),
                                        al_get_bitmap_height (imagem_chao),
                                        0, chao, largura_tela, altura_tela - chao, 0);
                         

                // desenho do personagem principal 
                desenha_obstaculos (obstaculos);
                imagem_largura = 144.0f;
                imagem_altura = 135.0f;
                coord_pes = jogador_1->altura + jogador_1->tamanho / 2.0f;

                pose = jogador_1->imagem_atual;
                if (coord_pes < chao){
                    pose = salto;
                }
                else if (jogador_1->controle->abaixando){
                    pose = agachado;
                }
                else if (jogador_1->controle->esquerda != jogador_1->controle->direita){
                    pose = andando < 4 ? andando1 : andando2;
                    andando = (andando + 1) % 8;
                }

                if (protecao % 6 < 4){
                    al_draw_scaled_bitmap(pose, 0, 0, al_get_bitmap_width(pose),
                                          al_get_bitmap_height(pose),
                                          jogador_1->largura - imagem_largura / 2,
                                          coord_pes - imagem_altura, imagem_largura, imagem_altura, 0);
                }

                al_draw_filled_rectangle(8, 8, 110, 30, al_map_rgb(29, 32, 25));
                al_draw_textf (al.texto, al_map_rgb(255, 240, 182), 16, 15, 0,
                              "Vida: %u/3", (unsigned)jogador_1->vida);

            }

            al_flip_display ();
        }

        // redimenciona janela
        else if (evento.type == ALLEGRO_EVENT_DISPLAY_RESIZE){

            al_acknowledge_resize (al.tela);

            // att valores da tela
            largura_tela = al_get_display_width (al.tela);
            altura_tela = al_get_display_height (al.tela);

            jogador_1->altura += (altura_tela - 160) - chao;
            chao = altura_tela - 160;
            if (largura_tela > jogador_1->tamanho &&
                jogador_1->largura > largura_tela - jogador_1->tamanho / 2)
                jogador_1->largura = largura_tela - jogador_1->tamanho / 2;
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

            else if (fim_de_jogo){
                if (pressionada && evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                    executando = 0;
            }  

            else {
                switch (evento.keyboard.keycode){
                    case ALLEGRO_KEY_A:
                        esquerda(jogador_1->controle, pressionada);
                        break;
                    case ALLEGRO_KEY_D:
                        direita(jogador_1->controle, pressionada);
                        break;
                    case ALLEGRO_KEY_W:
                        pulando(jogador_1->controle, pressionada);
                        if (pressionada && jogador_1->altura + jogador_1->tamanho / 2.0f >= chao)
                            jogador_1->veloc_y = -14.0f;
                        break;
                    case ALLEGRO_KEY_S:
                        abaixando(jogador_1->controle, pressionada);
                        break;
                    // **** remover posteriormente 
                    case ALLEGRO_KEY_X:
                        if (pressionada){
                            fim_de_jogo = 1;
                        }                    
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

    // limpeza 
    destroi_obstaculos(obstaculos);
    if (andando1) al_destroy_bitmap(andando1);
    if (andando2) al_destroy_bitmap(andando2);
    if (salto) al_destroy_bitmap(salto);
    if (agachado) al_destroy_bitmap(agachado);
    if (imagem_fundo) al_destroy_bitmap(imagem_fundo);
    if (imagem_chao) al_destroy_bitmap(imagem_chao);
    if (imagem_menu) al_destroy_bitmap(imagem_menu);
    if (jogador_1) destroi_personagem(jogador_1);
    destroi_allegro(&al);

    return 0;
}
