#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

struct dados{
    char nome[100];
    char profissao [100];
    char estado_civil [100];
    char cor_favorita [100];    
};

// Preenche uma struct individual a partir de uma linha CSV
void preencher_struct (struct dados *d, char *linha){
    char *token;
    int coluna = 0;

    token = strtok (linha, ";");
    while (token) {

        switch (coluna){
            // insere a palavra no membro correspondente da struct
            case 0:
                strcpy (d->nome, token);
                break;
            
            case 1:
                strcpy (d->profissao, token);
                break;
            
            case 2:
                strcpy (d->estado_civil, token);
                break;

            case 3:
                strcpy (d->cor_favorita, token);
                break;

            default:
                break;
        }

        token = strtok (NULL, ";");
        coluna++;
    }
}

// Comparação para o qsort
int comparar_nome (const void *a, const void *b){
    struct dados *d1, *d2;

    d1 = (struct dados *) a;
    d2 = (struct dados *) b;
    return strcmp(d1->nome, d2->nome); // strcmp compara duas strings, caracter a caracte
}

// Função 3: Exibe o array de structs formatado
void exibir_tabela(struct dados lista[], int total){

    printf ("\nID | %-15s | %-15s | %-12s | %-10s\n", "NOME", "PROFISSAO", "ESTADO CIVIL", "COR");
    printf ("--------------------------------------------------------------------------\n");
    for (int i = 0; i < total; i++) {
        printf ("%02d | %-15s | %-15s | %-12s | %-10s\n", i + 1, lista[i].nome, lista[i].profissao, 
            lista[i].estado_civil, lista[i].cor_favorita);
    }
}

int main (){
    char csv[100];
    char *token;// ponteiro auxiliar para separar colunas
    int cont;
    struct dados lista_dados [50];

    cont = 0;
    // le uma string do "teclado" (stdin) do tamanho de uma linha armazenada em csv
    // adiciona um '/n' no final desta string 
    while (fgets (csv, sizeof (csv), stdin)){
        // troca o '\n' que o fgets deixa para um '\0'
        csv[strcspn  (csv, "\n")] = '\0';
       
        // pular linhas vazias
        if (strlen (csv) == 0) 
            continue;

        preencher_struct (&lista_dados[cont], csv);

        cont++;
    }

    // algoritmo de ordenacao, utilizado a que já existe na biblioteca
    qsort (lista_dados, cont, sizeof (struct dados), comparar_nome);

    // Impressão dos dados
    exibir_tabela (lista_dados, cont);
    
    printf ("\n");
    return 0;
}