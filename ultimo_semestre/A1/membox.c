#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "membox.h"

int abrir_caixa(const char *nome, Diretorio *diretorio){
    FILE *aux_arq; // Ponteiro aux para manipulacao de arquivo

    if (!diretorio) // finaliza programa diretamente se um diretorio nao existir
        return 1;

    // abre o arquivo (caixa) para leitura em binario 
    aux_arq = fopen (nome,"rb");
    if (!aux_arq){ // se o arquivo não existir ele tenta criar 
        printf ("Uma nova caixa precisara ser criada\n");

        if (!cria_caixa (nome)){
            printf ("Erro ao criar a caixa\n");
            return 1;
        }
    }

       
    
    return 0;
}

void fechar_caixa(Diretorio *diretorio){

    if (!diretorio)
        return 1;
    
    // VERIFICAR DEPOIS: fechar a caixa  
    
    free (diretorio);
}

// int adicionar_arquivo(const char *caixa, Diretorio *diretorio,
//                       const char *arquivo){

// }

// int remover_arquivo(const char *caixa, Diretorio *diretorio,
//                     const char *nome){

// }

// void listar_arquivos(const Diretorio *diretorio){

// }


// int visualizar_arquivo(const char *caixa, const Diretorio *diretorio,
//                        const char *nome){

// }
