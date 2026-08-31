#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "membox.h"

int abrir_caixa(const char *nome, Diretorio *diretorio){
    FILE *aux_arq;

    if (!nome || !diretorio)
        return 1;

    // abre o arquivo para leitura em binario 
    aux_arq = fopen (nome,"rb");
    if (!aux_arq)
        return 1;

    
    
    return 0;
}

// void fechar_caixa(Diretorio *diretorio){

// }

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
