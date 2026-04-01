// Programa para ler um arquivo (string) e grava no arquivo que deve ser aberto e escrito  

#include <stdio.h>


int main (){
    FILE *arquivo;

    arquivo = fopen ("teste.txt", "w");
    fputs ("testando essa porcaria 2", arquivo);
    fclose (arquivo);
    
    return 0; 
}