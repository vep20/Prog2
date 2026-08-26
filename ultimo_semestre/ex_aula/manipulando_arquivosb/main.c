#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    float saldo;
    char nome[50];// considerar o /0
} Cliente;

// // cliente novos[]{
//     {maria, 42, 20};
//     (joao, 56, 09)/
// }


#define ARQUIVO "clientes.bin"

// int main (int argc, char *arcv()){
int main (void){
    FILE *arq;
    Cliente novo_cliente; 

    arq = fopen (ARQUIVO, "w+");
    if (!arq){
        perror ("Erro ao abrir arquivo");
        exit (1);
    }

    // copia um nome já definido para estrutura
    strcpy (novo_cliente.nome, "joao e maria");
    novo_cliente.id = 1;
    novo_cliente.saldo = 0;

    fwrite (&novo_cliente, sizeof (char), 50, arq);
    fwrite (&novo_cliente, sizeof (int), 1, arq);
    fwrite (&novo_cliente, sizeof (float), 1, arq);

    fclose (arq);
    printf ("Arquivo criado com sucesso\n");
    return 0;
}