#include <stdio.h>
#include <stdlib.h>
#include "gbv.h"
#include "util.h"

// superbloco: guarda o numero de documentos e a posição do diretorio

// area de dados: onde os arquivos ficam armazenados em sequencia

// area de diretório: contem os metadados (nome, tamanho, data e offset)
//                    dos documentos

int gbv_create (const char *filename){
    FILE *aux; // ponteiro para manipulação de arquivo
    int count;
    long dir_offset;

    count = 0;
    // inicio logo apos o superbloco 0-3 int e 4-11 long
    dir_offset = sizeof (int) + sizeof (long); 
    
    // abre o arquivo passado para escrita em binario
    aux = fopen (filename, "wb");
    if (!aux)    
        return 1; //retorna caso arquivo não seja criado ou resetado

    // grava o numero de documentos, no caso como esta vazio 0
    fwrite (&count, sizeof (int), 1, aux);
    // grava onde o diretorio inicia
    fwrite (&dir_offset, sizeof (long), 1, aux);

    fclose (aux);
    return 0;
}

int gbv_open (Library *lib, const char *filename){  
    FILE *aux_arq;
    long aux_offset;

    // abre o arquivo para leitura em binario 
    aux_arq = fopen (filename, "rb");

    // recupera o count no arquivo para gravar na biblioteca
    fread (&lib->count, sizeof (int), 1, aux_arq);
    // armazena onde o diretorio inicia no auxiliar
    fread (&aux_offset, sizeof (long), 1, aux_arq);
    
    lib->docs = malloc (sizeof (Document) * lib->count);
    if (!lib->docs)   
        return 1;

    // posiciona o ponteiro de arquivo no inicio da area de diretorio   
    fseek (aux_arq, aux_offset, SEEK_SET); // seek_set pe a partir do inicio do arq

    // realiza a leitura de todos os documentos e armazena na biblioteca
    fread (lib->docs, sizeof (Document), lib->count, aux_arq);    

    fclose (aux_arq);
    return 0;
}

// int gbv_add(Library *lib, const char *archive, const char *docname);
// int gbv_remove(Library *lib, const char *docname);
// int gbv_list(const Library *lib);
// int gbv_view(const Library *lib, const char *docname);
// int gbv_order(Library *lib, const char *archive, const char *criteria);
