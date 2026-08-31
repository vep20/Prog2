#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    float saldo;
    char nome[50]; // considerar o /0
} Cliente;


#define ARQUIVO "clientes.bin"

int main (void){
    FILE *arq;
    Cliente novo_cliente;
    // forma alternativa de cadastro
    // = {
    //     .id = 001,
    //     .saldo = -1000,
    //     .nome = "Victor Eduardo de Paula"    
    // };
    int leitura;

    arq = fopen (ARQUIVO, "w+b");
    if (!arq){
        perror ("Erro ao abrir arquivo");
        exit (1);
    }

    // copia um nome já definido para estrutura
    strcpy (novo_cliente.nome, "joao e maria");
    novo_cliente.id = 1;
    novo_cliente.saldo = 0;

    fwrite (&novo_cliente.id, sizeof (novo_cliente.id), 1, arq);
    fwrite (&novo_cliente.saldo, sizeof (novo_cliente.saldo), 1, arq);
    fwrite (novo_cliente.nome, sizeof (novo_cliente.nome), 1, arq);

    printf ("Digite 1 caso queira realizar a leitura ou 0 para encerrar\n");
    scanf ("%d", &leitura);
    if (leitura == 1){
        
        // Retorna ao inicio do arquivo
        rewind(arq);

        fread (&novo_cliente.id, sizeof (novo_cliente.id), 1, arq);
        fread (&novo_cliente.saldo, sizeof (novo_cliente.saldo), 1, arq);
        fread (novo_cliente.nome, sizeof (novo_cliente.nome), 1, arq);
    
        printf ("ID: %d\n", novo_cliente.id);
        printf ("Saldo: %.2f\n", novo_cliente.saldo);
        printf ("Nome: %s\n", novo_cliente.nome);
    }

    fclose (arq);
    printf ("Arquivo criado com sucesso\n");
    return 0;
}