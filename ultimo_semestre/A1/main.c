#include <stdio.h>
#include <string.h>

#include "membox.h"

static void uso(const char *programa)
{
    printf("Uso:\n");
    printf("  %s -a <caixa> <arquivo1> [arquivo2 ...]\n", programa);
    printf("  %s -r <caixa> <arquivo1> [arquivo2 ...]\n", programa);
    printf("  %s -l <caixa>\n", programa);
    printf("  %s -v <caixa> <arquivo>\n", programa);
}

int main(int argc, char *argv[])
{
    Diretorio diretorio;

    diretorio.arquivos = NULL;
    diretorio.quantidade = 0;

    if (argc < 3) {
        uso(argv[0]);
        return 1;
    }

    if (abrir_caixa(argv[2], &diretorio) != 0) {
        printf("Erro ao abrir a caixa.\n");
        return 1;
    }

    if (strcmp(argv[1], "-a") == 0) {

        if (argc < 4) {
            uso(argv[0]);
            fechar_caixa(&diretorio);
            return 1;
        }

        for (int i = 3; i < argc; i++) {
            if (adicionar_arquivo(argv[2],
                                  &diretorio,
                                  argv[i]) != 0) {
                printf("Erro ao adicionar: %s\n", argv[i]);
            }
        }

    } else if (strcmp(argv[1], "-r") == 0) {

        if (argc < 4) {
            uso(argv[0]);
            fechar_caixa(&diretorio);
            return 1;
        }

        for (int i = 3; i < argc; i++) {
            if (remover_arquivo(argv[2],
                                &diretorio,
                                argv[i]) != 0) {
                printf("Erro ao remover: %s\n", argv[i]);
            }
        }

    } else if (strcmp(argv[1], "-l") == 0) {

        if (argc != 3) {
            uso(argv[0]);
            fechar_caixa(&diretorio);
            return 1;
        }

        listar_arquivos(&diretorio);

    } else if (strcmp(argv[1], "-v") == 0) {

        if (argc != 4) {
            uso(argv[0]);
            fechar_caixa(&diretorio);
            return 1;
        }

        if (visualizar_arquivo(argv[2],
                               &diretorio,
                               argv[3]) != 0) {
            printf("Erro ao visualizar: %s\n", argv[3]);
        }

    } else {
        uso(argv[0]);
        fechar_caixa(&diretorio);
        return 1;
    }

    fechar_caixa(&diretorio);

    return 0;
}
