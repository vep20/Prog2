#include <stdio.h>
#include <string.h>
#include <strings.h>

int main (){
    char csv[101];
    char *token;// ponteiro auxiliar para separar colunas

    scanf("%s", csv);
    printf ("Quantidade caracteres digitados: %ld\n", strlen(csv));
    // Obs: função strlen retorna long int 
    token = strtok (csv, ";"); // separa a string em substrings com final NULL
    while (token){
        printf (" %ld", strlen(token));
        token = strtok(NULL, ";");// Modo de fazer continuar na mesma string passada anteriormente
    }
    printf ("\n");
    return 0;
}

