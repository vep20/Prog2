#ifndef MEMBOX_H
#define MEMBOX_H

#define MAX_NAME 256
#define BUFFER_SIZE 512

typedef struct {
    char nome[MAX_NAME]; 
    long tamanho;    // tamanho em bytes
    long data;       // data da insercao no container
    long offset;     // posicao no container
} Arquivo;

typedef struct {
    Arquivo *arquivos;
    int quantidade;
} Diretorio;

/*
 * Cria uma caixa nova vazia 
 */
int cria_caixa(const char *nome);

/*
 * Abre uma caixa existente.
 * Se a caixa não existir, cria uma caixa vazia.    
 */
int abrir_caixa(const char *nome, Diretorio *diretorio);

/*
 * Fecha a caixa e libera a memória do diretório.
 */
void fechar_caixa(Diretorio *diretorio);

/*
 * Verifica se um arquivo com o mesmo nome já existe no diretorio
 * Devolve o indice onde o arquivo esta na lista e sera substituido
*/
int procura_arquivo (Diretorio *diretorio, const char *arquivo);

/*
 * Adiciona um ou mais arquivos à caixa.
 */
int adicionar_arquivo(const char *caixa, Diretorio *diretorio,
                      const char *arquivo);

/*
 * Remove logicamente um arquivo da caixa.
 */
int remover_arquivo(const char *caixa, Diretorio *diretorio,
                    const char *nome);

/*
 * Lista os arquivos presentes na caixa.
 */
void listar_arquivos(const Diretorio *diretorio);

/*
 * Visualiza um arquivo armazenado na caixa.
 */
int visualizar_arquivo(const char *caixa,
                       const Diretorio *diretorio,
                       const char *nome);

#endif
