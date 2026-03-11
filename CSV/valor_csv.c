#include <stdio.h>
#include <string.h>
#include <strings.h>

int main (){
    char csv[101];
    char *token;// ponteiro auxiliar para separar colunas
    int cont;

    //scanf("%s", csv);

    // le uma string do "teclado" (stdin) do tamanho de uma linha armazenada em csv
    // adiciona um '/n' no final desta string 
    cont = 0; 
    while (fgets (csv, sizeof (csv), stdin)){
        cont++;
        //troca o \n que o fgets deix para um \0
        csv[strcspn  (csv, "\n")] = '\0';

        printf ("linha %d quantidade caracteres digitados: %ld\n",cont, strlen(csv));
        // Obs: função strlen retorna long int 
        token = strtok (csv, ";"); // separa a string em substrings com final NULL
        printf("Quantidade caracteres por colunas:");
        while (token){
            printf (" %ld", strlen(token));
            token = strtok(NULL, ";");// Modo de fazer continuar na mesma string passada anteriormente
        }
        printf ("\n\n");
    }
    return 0;
}