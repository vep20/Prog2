#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "membox.h"

int cria_caixa (const char *nome){
    FILE *aux_arq; // Ponteiro aux para manipulacao de arquivo
    long pos_dir;  // informacao de onde o diretorio com metadados inicia
    int qtd;

    // abre o arquivo (caixa) para escrita em binario
    aux_arq = fopen (nome, "wb");
    if (!aux_arq) // erro ao criar arquivo para escrita 
        return 1;
 
    qtd = 0;
    // posicao do diretorio, começa logo apos cabecalho, pois caixa vazia
    pos_dir = sizeof (int) + sizeof (long);

    // escreve o cabecalho no arquivo 
    fwrite (&qtd, sizeof (int), 1, aux_arq);
    fwrite (&pos_dir, sizeof (long), 1, aux_arq);
    
    fclose (aux_arq);
    return 0;
}

int abrir_caixa (const char *nome, Diretorio *diretorio){
    FILE *aux_arq;
    long pos_dir; // variavel auxiliar para ler posicao de diretorio
    int qtd;      // variavel para ler qtd de arquivos no cabecalho 

    if (!diretorio) // finaliza programa diretamente se nao for passado corretamente
        return 1;

    // abre o arquivo (caixa) para leitura em binario 
    aux_arq = fopen (nome,"rb");
    if (!aux_arq){ // se o arquivo nao existir ele tenta criar 
        printf ("Uma nova caixa precisara ser criada\n");

        if (cria_caixa (nome)){
            perror ("Erro ao criar a caixa");
            return 1;
        }

        // abre a caixa que acabou de ser criada (fechada na funcao cria)
        aux_arq = fopen (nome, "rb");
        if (!aux_arq){
            perror ("Erro ao abrir o arquivo");
            return 1;
        }
    }

    // le a quantidade de arquivos armazenada no cabecalho
    fread (&qtd, sizeof (int), 1, aux_arq); 
    diretorio->quantidade = qtd;
    
    // le a posicao onde o diretorio inicia
    fread (&pos_dir, sizeof (long), 1, aux_arq);

    // posiciona o ponteiro de leirua no inicio do diretorio
    fseek (aux_arq, pos_dir, SEEK_SET);

    if (qtd > 0){ // verifica se há arquivos no diretorio
        // abre espaco para entrada de arquivos no diretorio
        diretorio->arquivos = malloc (sizeof (*diretorio->arquivos) * qtd);
        if (!diretorio->arquivos){
            printf ("Erro ao alocar espaco para o diretorio\n");
            fclose (aux_arq);
            return 1;
        }

        // le as entradas do diretorio
        fread (diretorio->arquivos, sizeof (*diretorio->arquivos), 
               diretorio->quantidade, aux_arq);
    }

    else    
        diretorio->quantidade = NULL;
        
    fclose (aux_arq);
    return 0;
}

void fechar_caixa (Diretorio *diretorio){

    if (!diretorio)
        return;

    free (diretorio);
    diretorio->arquivos = NULL;
}

int adicionar_arquivo(const char *caixa, Diretorio *diretorio,
                      const char *arquivo){
    
    

}

// int remover_arquivo(const char *caixa, Diretorio *diretorio,
//                     const char *nome){

// }

// void listar_arquivos(const Diretorio *diretorio){

// }


// int visualizar_arquivo(const char *caixa, const Diretorio *diretorio,
//                        const char *nome){

// }
