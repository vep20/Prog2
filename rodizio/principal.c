#include <stdio.h>
#include "esteira.h"

int main (){
    struct esteira *nova_esteira;
    int acao;

    nova_esteira = esteira_cria ();

    if (!nova_esteira){
        printf ("Impossivel criar uma nova esteira\n");
        return 1;
    }

    do {
        printf ("Digite o que gostaria de fazer\n");
        printf ("1 - caso queira cadastrar uma porcao\n");
        printf ("2 - caso queira que a nova_esteira de uma volta\n");
        printf ("3 - caso queira encerrar o programa\n");
        scanf ("%d", &acao);

        if (acao < 1 || acao > 3)
            printf("Por favor digite um numero de acao valido\n");

        else if (acao == 1){
            printf ("");
            // criar porcao e inserir na esteira
        }

        else 
            printf ("ok");
            // circula a fila, em cada nodo realiza uma parada e faz uma função de escolha aleatoria 
            // para verificar se o usuario tira algo da struct porcao
            // se ele retira e a struct fica com uni == 0, remove porção da esteira

    } while (acao != 3);
    

    nova_esteira = esteira_destroi (nova_esteira);
    return 0; 
}