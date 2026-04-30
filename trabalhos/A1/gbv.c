#include <stdio.h>
#include <stdlib.h>
#include "gbv.h"
#include "util.h"

// superbloco: guarda o numero de documentos e a posição do diretorio

// area de dados: onde os arquivos ficam armazenados em sequencia

// area de diretório: contem os metadados (nome, tamanho, data e offset)
//                    dos documentos

int gbv_create (const char *filename){
    FILE *aux_arq; // ponteiro para manipulação de arquivo
    int count;
    long dir_offset;

    count = 0;
    // inicio logo apos o superbloco 0-3 int e 4-11 long
    dir_offset = sizeof (int) + sizeof (long); 
    
    // abre o arquivo passado para escrita em binario
    aux_arq = fopen (filename, "wb");
    if (!aux_arq)    
        return 1; //retorna caso arquivo não seja criado ou resetado

    // grava o numero de documentos, no caso como esta vazio 0
    fwrite (&count, sizeof (int), 1, aux_arq);
    
    // grava onde o diretorio inicia
    fwrite (&dir_offset, sizeof (long), 1, aux_arq);

    fclose (aux_arq);
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

int gbv_list(const Library *lib){
    char aux_buffer[30];

    if (!lib)
        return 1;

    for(int i = 0; i < lib->count; i++){
        printf ("Nome: %s\n", lib->docs[i].name);
        printf ("Tamanho: %ld\n", lib->docs[i].size);

        // impressão da data no formato padrão exigido
        format_date (lib->docs[i].date, aux_buffer, 30);
        printf ("Data: %s\n", aux_buffer);

        printf ("Offset: %ld\n", lib->docs[i].offset);
    }

    return 0; 
}

int gbv_view(const Library *lib, const char *docname){
    FILE *aux_arq;
    long offset_inicial, tam_total, bytes;
    int indice;

    if (!lib || !docname)
        return 1;

    indice = -1;

    for (int i; i < lib->count; i++){
        // comparação caracter a caracter para verificar se
        // o documento esta na biblioteca
        if (strcmp(lib->docs[i].name, docname) == 0){
            indice = i;
            break;// documento encontrado
        }
    }

    if (indice == -1){
        printf ("Documento não esta na biblioteca\n");
        return 1; 
    }

    // nome generico da biblioteca que sera procurada pelo função
    // fopen, visto que o arquivo não pe passado como parametro
    // assim como nas funções add, remove e order
    aux_arq = fopen ("biblioteca.gbv", "rb");
    if (!aux_arq){
        printf ("Erro ao abrir arquivo da biblioteca\n");
        return 1;
    }

    offset_inicial = lib->docs[indice].offset;
    tam_total = lib->docs[indice].size;
    bytes = 0; // aux de deslcoamento da navegação 

    // loop para visualização por blocos 
    while (1){
        // mostra o bloco
        printf ("\n--- Bloco: %s [%ld bytes] ---\n", docname, tam_total);

        // posiciona o cursor do incicio do documento + o deslocamento da visu
        fseek (aux_arq, offset_inicial + bytes, SEEK_SET);
        
    }
    fclose(aux_arq);
    return 0;
}

// int gbv_add(Library *lib, const char *archive, const char *docname);
// int gbv_remove(Library *lib, const char *docname);
// int gbv_order(Library *lib, const char *archive, const char *criteria);
