#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gbv.h"

int main(int argc, char *argv[]) {

    if (argc < 4) {
        printf("Uso: %s <chave> <opção> <biblioteca> [documentos...]\n", argv[0]);
        return 1;
    }

    const char *chave_digitada = argv[1];

    // Alteracao A2: verifica se a chave possui 4 bytes
    if (strlen (chave_digitada) != 4){
        printf ("Acesso Negado qtd\n");
        return 1;
    }

    const char *opcao = argv[2];
    const char *biblioteca = argv[3];

    Library lib;

    // ATT pos entrega
    lib.chave = NULL;// INICIA DE FORMA SEGURA ATT POS ENTREGA 
    lib.docs = NULL;

    // Alteracao: Criar a biblioteca se for inserção e ela não existir 
    // Removido pos entrega FILE *teste_existe;

    // DADOS QUE POSSUEM O A1
    // teste_existe = fopen(biblioteca, "rb");

    // if (!teste_existe && strcmp(opcao, "-a") == 0) 
    //     gbv_create(biblioteca);

    // else if (teste_existe)
    //     fclose(teste_existe);

    if (gbv_open(&lib, biblioteca) != 0) {
        printf("Erro ao abrir biblioteca %s\n", biblioteca);
        return 1;
    }

    // Alteracao A2, verifica se a chave digitada é a mesma que foi criada na
    // biblioteca;
    if (strcmp (chave_digitada, lib.chave) != 0){
        
        printf ("Acesso Negado\n");

    // ATT pos entrega
        if(lib.chave)
            free (lib.chave);

        if(lib.docs)
            free (lib.docs);

        return 1;
    }

    // Alteracao A2 : começo dos documentos é em 4
    if (strcmp(opcao, "-a") == 0) {
        for (int i = 4; i < argc; i++) {
            gbv_add(&lib, biblioteca, argv[i]);
        }
    } 
    
    // Alteracao A2 : começo dos documentos é em 4
    else if (strcmp(opcao, "-r") == 0) {
        for (int i = 4; i < argc; i++) {
            gbv_remove(&lib, biblioteca, argv[i]);
        }
    } 
    
    else if (strcmp(opcao, "-l") == 0) {
        gbv_list(&lib);
    } 
    
    // Alteracao A2 : começo dos documentos é em 4 e argc >=5
    else if (strcmp(opcao, "-v") == 0 && argc >= 5) {
        gbv_view(&lib, biblioteca, argv[4]);// alteração realizada para receber
                                            // paramentro 
    } 
    
    else if (strcmp(opcao, "-o") == 0 && argc >= 5) {
        gbv_order(&lib, biblioteca, argv[4]);
    } 
    
    else {
        printf("Opção inválida.\n");
    }

    // ATT pos entrega
    if (lib.chave != NULL) {
        free(lib.chave);
        lib.chave = NULL;
    }

    // alteracao: Liberar a memória do diretório antes de encerrar o programa
    if (lib.docs != NULL) {
        free(lib.docs);
        lib.docs = NULL;
    }

    return 0;
}