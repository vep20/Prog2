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

// função para adicionar um arquivo na biblioteca
// recebe os metadados, a biblioteca e o novo arquivo
// retorna 1 em caso de falha e 0 caso o arquivo tenha sido inserido
// com sucesso na biblioteca
int gbv_add(Library *lib, const char *archive, const char *docname);

// função para remover o metadado do arquivo 
// retorna 1 em caso de falha e 0 caso sucesso
int gbv_remove(Library *lib, const char *archive, const char *docname);

// função que lista os metadados dos arquivos 
// recebe a biblioteca como parametro
// retorna em 1 em caso de falha e 0 em caso de sucesso
int gbv_list(const Library *lib);

// função auxiliar para buscar o nome de um documento na biblioteca
// retorna 1 caso o documento não esteja na bibliote ou o indice do vetor
// de documentos caso sim
int gbv_search (const Library *lib, const char *docname);

// função para navegar no conteudo de um documento 
int gbv_view(const Library *lib, const char *archive, const char *docname);
 

// funções de comparação para o qsort
int cmp_nome(const void *a, const void *b);
int cmp_data(const void *a, const void *b);
int cmp_tamanho(const void *a, const void *b);

// função para reordena os documento da biblioteca, att o diretorio e refletindo
// em nova ordem 
// retorna 1 em caso de falha e 0 em caso de sucesso
int gbv_order(Library *lib, const char *archive, const char *criteria);

#endif

