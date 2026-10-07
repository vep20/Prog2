#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

    if (!diretorio) // finaliza a funcao se parametro nao for passado corretamente
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
            perror ("Erro ao abrir o arquivo funcao abrir_caixa");
            return 1;
        }
    }

    // le a quantidade de arquivos armazenada no cabecalho
    fread (&qtd, sizeof (int), 1, aux_arq); 
    diretorio->quantidade = qtd;
    
    // le a posicao onde o diretorio inicia
    fread (&pos_dir, sizeof (long), 1, aux_arq);

    // posiciona o ponteiro de leitura no inicio do diretorio
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
        diretorio->arquivos = NULL;
        
    fclose (aux_arq);
    return 0;
}

void fechar_caixa (Diretorio *diretorio){

    if (!diretorio)
        return

    free (diretorio);
    diretorio->arquivos = NULL;
}

int procura_arquivo (Diretorio *diretorio, const char *arquivo){
    int aux;

    aux = -1;
    for (int i = 0; i < diretorio->quantidade; i++){
        // compara o nome do arquivo com os nomes do arquivos no diretorio 
        if (strcmp (diretorio->arquivos[i].nome, arquivo) == 0){
            aux = i;
            break; //  documento encontrado
        }
    }
    
    return aux;
}

int adicionar_arquivo(const char *caixa, Diretorio *diretorio, const char *arquivo){
    FILE *novo_arq, *aux_caixa;
    Arquivo *temp, aux_novo_arq; // um ponteiro para substituir um arquivo já existente
                            // e um auxiliar para receber dados do novo arquivo
    size_t bytes_percorridos;
    long pos_dir, tam_arq, nova_pos_arq;
    int indice, qtd;
    char aux_buffer [BUFFER_SIZE];
     

    if (!caixa || !diretorio || !arquivo){
        printf ("Erro nos parametros na funcao adicionar\n");
        return 1;
    }

    novo_arq = fopen (arquivo, "rb");
    if (!novo_arq){
        perror ("Erro ao abrir novo arquivo na funcao adicionar");
        return 1;
    }

    // abre caixa em modo de leitura e escrita, ja que dados serao att
    aux_caixa = fopen (caixa, "r+b");
    if (!aux_caixa){
        fclose (novo_arq);
        return 1;
    }

    //----------------------CAIXA--------------------------------------------------
    // posiciona o ponteiro de leitura no comeco da caixa, necessario quando usa r+b
    fseek (aux_caixa, 0, SEEK_SET);

    // le o cabecalho, qtd arquivos e posicao do diretorio
    fread (&qtd, sizeof (int), 1, aux_caixa);
    fread (&pos_dir, sizeof (long), 1, aux_caixa);

    // descobre posicao onde novo arquivo deve ficar
    nova_pos_arq = pos_dir;
    //------------------------------------------------------------------------------

    //----------------------NOVO_ARQUIVO--------------------------------------------
    // posiciona o ponteiro de leitura no final do arquivo 
    // para descobrir tamanho do arquivo com ftell
    fseek (novo_arq, 0, SEEK_END);
    tam_arq = ftell (novo_arq);
    // retorna o ponteiro de leitura para inicio do arquivo
    rewind (novo_arq);

    // verifica se ja ha um documento com mesmo nome no diretorio
    indice = procura_arquivo (diretorio, arquivo);

    // posiciona ponteiro de leitura no inicio do diretorio
    fseek (aux_caixa, nova_pos_arq, SEEK_SET);

    // leitura maxima até encher o buffer  
    bytes_percorridos = fread (aux_buffer, 1, BUFFER_SIZE, novo_arq);
    while (bytes_percorridos > 0){ 
        // escreve o que esta no buffer nos arquivos
        fwrite (aux_buffer, 1, bytes_percorridos, aux_caixa);
        bytes_percorridos = fread (aux_buffer, 1, BUFFER_SIZE, novo_arq);
    }

    // fecha arquivo bruto, pois nao sera mais necessario
    fclose (novo_arq);
    //------------------------------------------------------------------------------

    // preenchimento dos dados do arquivo novo
    strncpy (aux_novo_arq.nome, arquivo, MAX_NAME - 1);
    aux_novo_arq.nome[MAX_NAME - 1] = '\0';
    aux_novo_arq.tamanho = tam_arq;
    aux_novo_arq.data = time (NULL);
    aux_novo_arq.offset = nova_pos_arq;

    // adicioan novo arquivo, pois outro com mesmo nome nao existe
    if (indice == -1){
        temp = realloc (diretorio->arquivos, sizeof (Arquivo) * (diretorio->quantidade + 1));
        if (!temp){
            printf ("Erro ao realocar espaco para novo arquivo na caixa\n");
            fclose (aux_caixa);
            return 1;
        }
        // att diretorio
        diretorio->arquivos = temp;
        diretorio->arquivos[diretorio->quantidade] = aux_novo_arq;
        diretorio->quantidade++;
    }

    // substitui arquivo que ja existe com o mesmo nome
    else {
        diretorio->arquivos[indice] = aux_novo_arq;
    }

    // att onde nome diretorio comeca, logo apos dados que acaba de ser inserido
    pos_dir = ftell (aux_caixa);
    
    fwrite (diretorio->arquivos, sizeof (*diretorio->arquivos), diretorio->quantidade, aux_caixa);

    // att cabecalho
    fseek (aux_caixa, 0, SEEK_SET);
    fwrite (&diretorio->quantidade, sizeof (int), 1, aux_caixa);
    fwrite (&pos_dir, sizeof (long), 1, aux_caixa);

    fclose (aux_caixa);
    return 0;
}

// int remover_arquivo(const char *caixa, Diretorio *diretorio,
//                     const char *nome){
    // FILE *aux_arq;
// if (!caixa || !diretorio || !arquivo){
    //     printf ("Erro nos parametros na funcao remover\n");
    //     return 1;
    // }
// }

void listar_arquivos(const Diretorio *diretorio){

    if (!diretorio)
        return;

    if (diretorio->quantidade == 0){
        printf ("Não há arquivos no diretorio\n");
        return;
    }

    printf ("\nQuantidade de arquivos no diretorio: %d\n", diretorio->quantidade);
    for (int i = 0; i < diretorio->quantidade; i++){
        printf ("\nArquivo: %d\n", i);
        printf ("Nome %s\n", diretorio->arquivos->nome);
        printf ("Tamanho %ld", diretorio->arquivos->tamanho);
        
        printf ("Data: ");
        exibir_data (diretorio->arquivos->data);
        printf ("\n");

        printf ("Posicao: %ld", diretorio->arquivos->offset);
    }
}


// int visualizar_arquivo(const char *caixa, const Diretorio *diretorio,
//                        const char *nome){
    // FILE *aux_arq;
    // if (!caixa || !diretorio || !arquivo){
    //     printf ("Erro nos parametros na funcao visualizar\n");
    //     return 1;
    // }
// }
