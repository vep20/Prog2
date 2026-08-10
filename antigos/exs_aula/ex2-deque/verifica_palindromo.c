#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "deque.h"

int main (){
    struct deque *novo;
    char vetor_caracter[100], inicio, fim;
    short verifica;

    novo = cria();
    if (!novo){
        printf ("impossivel criar deque\n");
        return 1;
    }

    fgets ((char *)vetor_caracter, sizeof (vetor_caracter), stdin);
    vetor_caracter [strcspn((char *)vetor_caracter, "\n")] = '\0'; //substitui o ultimo caracter por \0


    for (int i = 0; vetor_caracter[i] != '\0'; i++)
        insere_fim (novo, vetor_caracter[i]);

    verifica = 1;
    while (novo->tam > 1){
        inicio = remove_ini(novo);
        fim = remove_fim (novo);

        if (inicio != fim)
            verifica = 0;        

    }

    if (verifica)
        printf ("é palindromo\n");
    
    else
        printf ("não é palindromo\n");
    novo = destroi_deque (novo);
    return 0;
}