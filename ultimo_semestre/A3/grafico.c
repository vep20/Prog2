#include <stdio.h>
#include "grafico.h"


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
    
    // tenta criar os movimentos para estrutura
    novo_jogador->controle = cria_movimentos ();
    if (!novo_jogador->controle){
        fprintf (stderr, "Erro ao criar movimentos para o personagem, estrutura sera limpa\n");
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
    free (jogador);
}