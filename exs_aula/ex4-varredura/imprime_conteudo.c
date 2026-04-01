// Programa que le um arquivo e imprime o que há neste arquivo na saida do terminal 

#include <stdio.h>

int main (){
    FILE *arquivo;
    char *guarda_char;

    arquivo = fopen ("ler_aquivo.c","r");

    while (feof(arquivo) == 0){
        guarda_char = fgetc (arquivo);
        printf ("%c", guarda_char);
    }

    fclose (arquivo);
    return 0;
}