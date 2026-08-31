#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char id[11]; // 10 caracteres + \0
    int hacking;
    int criminalidade;
} Cidadao;


#define ARQUIVO "cidadaos.bin"

int main (void){
    FILE *arq;
    Cidadao cidadaos[] = {
         {"Neo", 90, 4}, 
         {"Trinity", 85, 7}, 
         {"Morpheus", 70, 8} 
    };
    float soma_hacking, media_hacking;
    int quantidade, criminalidade_alta;
    
    arq = fopen (ARQUIVO, "w+b");
    if (!arq){
        perror ("Erro ao abrir arquivo");
        exit (1);
    }

    quantidade = 0;
    criminalidade_alta = 0;
    soma_hacking = 0;

    for (int i = 0; i < 3; i++){
        fwrite (cidadaos[i].id, sizeof (cidadaos[i].id), 1, arq);
        fwrite (&cidadaos[i].hacking, sizeof (cidadaos[i].hacking), 1, arq);
        fwrite (&cidadaos[i].criminalidade, sizeof (cidadaos[i].criminalidade), 1, arq);
    }

    // Retorna ao inicio do arquivo
    rewind (arq);

    for (int i = 0; i < 3; i++){
        fread (cidadaos[i].id, sizeof (cidadaos[i].id), 1, arq);
        fread (&cidadaos[i].hacking, sizeof (cidadaos[i].hacking), 1, arq);
        fread (&cidadaos[i].criminalidade, sizeof (cidadaos[i].criminalidade), 1, arq);
    
        quantidade++; 
        soma_hacking += cidadaos[i].hacking; 

        if (cidadaos[i].criminalidade > 5) 
            criminalidade_alta++;
             
        printf ("ID: %s\n", cidadaos[i].id); 
        printf ("Hacking: %d\n\n", cidadaos[i].hacking);
    }

    if (quantidade > 0)
        media_hacking = soma_hacking / quantidade;

    else 
        media_hacking = 0;

    printf ("Quantidade total de cidadaos: %d\n", quantidade);
    printf ("Media dos niveis de hacking: %.2f\n", media_hacking);
    printf ("Cidadaos com criminalidade acima de 5: %d\n", criminalidade_alta);

    fclose (arq);
    return 0;
}