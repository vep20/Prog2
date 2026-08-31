#ifndef UTIL_H
#define UTIL_H

/*
 * Retorna o tamanho do arquivo em bytes.
 * Retorna -1 em caso de erro.
 */
long tamanho_arquivo(const char *nome);

/*
 * Exibe uma data no formato:
 * DD/MM/AAAA HH:MM:SS
 */
void exibir_data(long data);

#endif
