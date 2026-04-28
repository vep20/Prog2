#ifndef GBV_H
#define GBV_H

#include <time.h>

#define MAX_NAME 256
#define BUFFER_SIZE 512   // tamanho fixo do buffer em bytes

// Estrutura de metadados de cada documento
typedef struct {
    char name[MAX_NAME];   // nome do documento
    long size;             // tamanho em bytes
    time_t date;           // data de inserção
    long offset;           // posição no container
} Document;

// Estrutura que representa a biblioteca (diretório em memória)
typedef struct {
    Document *docs;        // vetor dinâmico de documentos
    int count;             // número de documentos
} Library;

// função que cria um arquivo binario novo e grava o superbloco
// recebe o nome do arquivo que será gravado
// retorna 1 em caso de falha e 0 em caso de sucesso
int gbv_create(const char *filename);

// função que preenche a bibllioteca
// retorna 1 em caso de falha e 0 em caso de sucesso
int gbv_open(Library *lib, const char *filename);

int gbv_add(Library *lib, const char *archive, const char *docname);
int gbv_remove(Library *lib, const char *docname);

// função que lista os metadados dos arquivos 
// recebe a biblioteca como parametro
// retorna em 1 em caso de falha e 0 em caso de sucesso
int gbv_list(const Library *lib);

int gbv_view(const Library *lib, const char *docname);
int gbv_order(Library *lib, const char *archive, const char *criteria);

#endif

