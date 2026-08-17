#include "labrob.h"
#include <stdio.h>
#include <stdlib.h>

int main(){ 
    struct lab *dinf;
    int opcao, aux_id, aux_sens;

    dinf = crialab();
    if (!dinf)
        printf ("impossivel criar lab de robos\n");

    printf ("\n--------------------------------\n");
    do{
        printf ("Informe o que gostaria de fazer\n");
        printf ("1 - cadastrar robo\n");
        printf ("2 - realizar analise de robos e seus sensores\n");
        printf ("3 - atualizar as leituras de um robo\n");
        // printf ("4 - remover um robo\n");
        printf ("5 - encerrar o programa\n");
        scanf ("%d", &opcao);

        switch (opcao){
        case 1:
            printf("informe id e quantos sensores quer que seu robo possua\n");
            scanf ("%d %d", &aux_id, &aux_sens);
            cadastrar_robo (dinf, aux_id, aux_sens);
            break;

        case 2:
            analisa_robos (dinf);
            break;

        case 3:
            printf ("Forneca o valor do id procurado\n");
            scanf ("%d", &aux_id);
            att_robo (dinf, aux_id);
            break;
            
        default:
            break;
        }
        printf("\n");
    } while (opcao != 5);

    return 0;
}