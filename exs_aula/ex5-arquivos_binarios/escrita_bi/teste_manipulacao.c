// programa para escrita em um arquivo binario
#include <stdio.h>

int main (){
    int buffer [10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};//se for ler
    FILE *file;

    file = fopen ("output.txt", "wb");// rb para receber ao inves de wb
    fwrite (buffer, sizeof (int), 10, file);//fread caso queira ler
    fclose(file);

    return 0;
}