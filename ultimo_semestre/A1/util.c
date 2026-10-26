#include "util.h"

#include <stdio.h>
#include <time.h>

long tamanho_arquivo(const char *nome)
{
    FILE *arquivo;
    long tamanho;

    arquivo = fopen(nome, "rb");

    if (arquivo == NULL)
        return -1;

    // posiciona o ponteiro para o fim do arquivo e verifica se é valido
    if (fseek(arquivo, 0, SEEK_END) != 0) {
        fclose(arquivo);
        return -1;
    }

    // retorna a posicao atual do ponteiro de leitura
    tamanho = ftell(arquivo);

    fclose(arquivo);

    return tamanho;
}

void exibir_data(long data)
{
    time_t tempo;
    struct tm *info;
    char texto[32];

    tempo = (time_t)data;
    info = localtime(&tempo);

    if (info == NULL) {
        printf("data invalida");
        return;
    }

    strftime(texto, sizeof(texto),
             "%d/%m/%Y %H:%M:%S", info);

    printf("%s", texto);
}
