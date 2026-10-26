#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "util.h"
#include "membox.h"

int cria_caixa (const char *nome){
    FILE *aux_caixa; // Ponteiro aux para manipulacao de arquivo
    long pos_dir;  // informacao de onde o diretorio com metadados inicia
    int qtd;

    // abre o arquivo (caixa) para escrita em binario
    aux_caixa = fopen (nome, "wb");
    if (!aux_caixa) // erro ao criar arquivo para escrita 
        return 1;
 
    qtd = 0;
    // posicao do diretorio, começa logo apos cabecalho, pois caixa vazia
    pos_dir = sizeof (int) + sizeof (long);

    // escreve o cabecalho no arquivo 
    fwrite (&qtd, sizeof (int), 1, aux_caixa);
    fwrite (&pos_dir, sizeof (long), 1, aux_caixa);
    
    fclose (aux_caixa);
    return 0;
}

int abrir_caixa (const char *nome, Diretorio *diretorio){
    FILE *aux_caixa;
    long pos_dir; // variavel auxiliar para ler posicao de diretorio
    int qtd;      // variavel para ler qtd de arquivos no cabecalho 

    if (!diretorio) // finaliza a funcao se parametro nao for passado corretamente
        return 1;

    // abre o arquivo (caixa) para leitura em binario 
    aux_caixa = fopen (nome,"rb");
    if (!aux_caixa){ // tenta criar nova caixa 
        printf ("Uma nova caixa precisara ser criada\n");

        if (cria_caixa (nome)){
            perror ("Erro ao criar a caixa");
            return 1;
        }

        // abre a caixa que acabou de ser criada (fechada na funcao cria)
        aux_caixa = fopen (nome, "rb");
        if (!aux_caixa){
            perror ("Erro ao abrir o arquivo funcao abrir_caixa");
            return 1;
        }
    }

    // le a quantidade de arquivos armazenada no cabecalho
    fread (&qtd, sizeof (int), 1, aux_caixa); 
    diretorio->quantidade = qtd;
    
    // le a posicao onde o diretorio inicia
    fread (&pos_dir, sizeof (long), 1, aux_caixa);

    // posiciona o ponteiro de leitura no inicio do diretorio
    fseek (aux_caixa, pos_dir, SEEK_SET);

    if (qtd > 0){ // verifica se há arquivos no diretorio
        // abre espaco para entrada de arquivos no diretorio
        diretorio->arquivos = malloc (sizeof (*diretorio->arquivos) * qtd);
        if (!diretorio->arquivos){
            printf ("Erro ao alocar espaco para o diretorio\n");
            fclose (aux_caixa);
            return 1;
        }

        // le as entradas do diretorio
        fread (diretorio->arquivos, sizeof (*diretorio->arquivos), 
               diretorio->quantidade, aux_caixa);
    }

    else    
        diretorio->arquivos = NULL;
        
    fclose (aux_caixa);
    return 0;
}

void fechar_caixa (Diretorio *diretorio){

    if (!diretorio)
        return;

    free (diretorio->arquivos);
    diretorio->arquivos = NULL;
    diretorio->quantidade = 0;
}

int procura_arquivo (Diretorio *diretorio, const char *arquivo){
    int aux; 

    aux = -1;
    for (int i = 0; i < diretorio->quantidade; i++){
        // compara o nome do arquivo com os nomes dos arquivos no diretorio 
        if (strcmp (diretorio->arquivos[i].nome, arquivo) == 0){
            aux = i;
            break; //  documento encontrado
        }
    }
    
    return aux;
}

int adicionar_arquivo(const char *caixa, Diretorio *diretorio, const char *arquivo){
    FILE *novo_arq, *aux_caixa;
    Arquivo *temp, aux_novo_arq; // um ponteiro para reallocar
                            // e um auxiliar para receber dados do novo arquivo
    size_t bytes_percorridos;
    long pos_dir, tam_arq, nova_pos_arq;
    int indice, qtd;
    char aux_buffer [BUFFER_SIZE];
     

    if (!caixa || !diretorio || !arquivo){
        printf ("Erro nos parametros na funcao adicionar\n");
        return 1;
    }

    novo_arq = fopen (arquivo, "rb");
    if (!novo_arq){
        perror ("Erro ao abrir novo arquivo na funcao adicionar");
        return 1;
    }

    // abre caixa em modo de leitura e escrita, ja que dados serao verificados e att
    aux_caixa = fopen (caixa, "r+b");
    if (!aux_caixa){
        perror ("Erro ao abrir caixa na funcao adicionar");
        fclose (novo_arq);
        return 1;
    }

    //----------------------CAIXA--------------------------------------------------
    // posiciona o ponteiro de leitura no comeco da caixa, necessario quando usa r+b
    fseek (aux_caixa, 0, SEEK_SET);

    // le o cabecalho, qtd arquivos e posicao do diretorio
    fread (&qtd, sizeof (int), 1, aux_caixa);
    fread (&pos_dir, sizeof (long), 1, aux_caixa);

    // informa posicao onde novo arquivo deve ficar
    nova_pos_arq = pos_dir;
    //------------------------------------------------------------------------------

    //----------------------NOVO_ARQUIVO--------------------------------------------
    // descobre tamanho do novo arquivo para add posteriormente nos metadados
    tam_arq = tamanho_arquivo(arquivo);

    // verifica se ja ha um arquivo com mesmo nome no diretorio
    indice = procura_arquivo (diretorio, arquivo);

    // posiciona ponteiro de leitura no inicio do diretorio
    fseek (aux_caixa, nova_pos_arq, SEEK_SET);

    // leitura maxima até encher o buffer  
    bytes_percorridos = fread (aux_buffer, 1, BUFFER_SIZE, novo_arq);
    while (bytes_percorridos > 0){ 
        // escreve o que esta no buffer na area de dados da caixa
        fwrite (aux_buffer, 1, bytes_percorridos, aux_caixa);
        bytes_percorridos = fread (aux_buffer, 1, BUFFER_SIZE, novo_arq);
    }

    // fecha arquivo bruto, pois nao sera mais necessario
    fclose (novo_arq);
    //------------------------------------------------------------------------------

    // preenchimento dos dados do arquivo novo
    strncpy (aux_novo_arq.nome, arquivo, MAX_NAME - 1);
    aux_novo_arq.nome[MAX_NAME - 1] = '\0';
    aux_novo_arq.tamanho = tam_arq;
    aux_novo_arq.data = time (NULL);
    aux_novo_arq.offset = nova_pos_arq;

    // adiciona novo arquivo, pois outro com mesmo nome nao existe
    if (indice == -1){
        temp = realloc (diretorio->arquivos, sizeof (Arquivo) * (diretorio->quantidade + 1));
        if (!temp){
            printf ("Erro ao realocar espaco para novo arquivo na caixa\n");
            fclose (aux_caixa);
            return 1;
        }
        // att diretorio
        diretorio->arquivos = temp;
        diretorio->arquivos[diretorio->quantidade] = aux_novo_arq;
        diretorio->quantidade++;
    }

    // substitui arquivo que ja existe com o mesmo nome
    else {
        diretorio->arquivos[indice] = aux_novo_arq;
    }

    // att onde nome diretorio comeca, logo apos dados que acaba de ser inserido
    pos_dir = ftell (aux_caixa);
    
    fwrite (diretorio->arquivos, sizeof (*diretorio->arquivos), diretorio->quantidade, aux_caixa);

    // att cabecalho
    fseek (aux_caixa, 0, SEEK_SET);
    fwrite (&diretorio->quantidade, sizeof (int), 1, aux_caixa);
    fwrite (&pos_dir, sizeof (long), 1, aux_caixa);

    fclose (aux_caixa);
    return 0;
}

int remover_arquivo(const char *caixa, Diretorio *diretorio, const char *nome){
    FILE *aux_caixa;
    Arquivo *temp;
    long pos_dir;
    int indice, qtd;
    
    if (!caixa || !diretorio || !nome){
        printf ("Erro nos parametros na funcao remover\n");
        return 1;
    }

    // verifica se arquivo esta no diretorio
    indice = procura_arquivo (diretorio, nome);
    if (indice == -1){
        printf ("Arquivo nao esta no diretorio para ser removido\n");
        return 1;
    }

    // reorganiza onde cada metadado do arquivo deve ficar apos remocao 
    for (int i = indice; i < diretorio->quantidade - 1; i++){
        diretorio->arquivos[i] = diretorio->arquivos[i + 1];
    }

    // reduz espaco ocupado pelo diretorio 
    diretorio->quantidade--;
    if (diretorio->quantidade > 0){
        temp = realloc (diretorio->arquivos, sizeof (Arquivo) * diretorio->quantidade);
        if (!temp){
            printf ("Erro ao realocar memoria para remocao\n");
            return 1;
        }
        diretorio->arquivos = temp;
    }

    else {
        // diretorio vazio
        free (diretorio->arquivos);
        diretorio->arquivos = NULL;
    }

    aux_caixa = fopen (caixa, "r+b");
    if (!aux_caixa){
        perror ("Erro ao abrir caixa na funcao remover");
        return 1;
    }

    // inicia a leitura da caixa
    fread (&qtd, sizeof (int), 1, aux_caixa);
    fread (&pos_dir, sizeof (long), 1, aux_caixa);

    // posiciona ponteiro de leitura onde o diretorio incia
    fseek (aux_caixa, pos_dir, SEEK_SET);

    // att os metadados do diretorio na caixa
    if (diretorio->quantidade > 0){
        fwrite (diretorio->arquivos, sizeof (Arquivo), diretorio->quantidade, aux_caixa);
    }

    // att o cabecalho (somente qtd, conforme enunciado)
    rewind (aux_caixa);
    fwrite (&diretorio->quantidade, sizeof (diretorio->quantidade), 1, aux_caixa);

    fclose (aux_caixa);
    return 0;
}

void listar_arquivos(const Diretorio *diretorio){
    
    if (!diretorio)
        return;

    if (diretorio->quantidade == 0){
        printf ("Nao ha arquivos no diretorio\n");
        return;
    }

    printf ("\nQuantidade de arquivos no diretorio: %d\n", diretorio->quantidade);
    for (int i = 0; i < diretorio->quantidade; i++){
        printf ("\nArquivo: %d\n", i);
        printf ("Nome: %s\n", diretorio->arquivos[i].nome);
        printf ("Tamanho: %ld\n", diretorio->arquivos[i].tamanho);
        
        printf ("Data: ");
        exibir_data (diretorio->arquivos[i].data);
        printf ("\n");

        printf ("Posicao: %ld\n", diretorio->arquivos[i].offset);
    }
}

int visualizar_arquivo(const char *caixa, const Diretorio *diretorio, const char *nome){
    FILE *aux_caixa;
    Diretorio *aux_diretorio;
    size_t lido; // varivel para leitura no arquivo
    long pos_inicial, tam_total, bytes_percorridos, resto_bloco, a_ler;
    int indice;
    char aux_buffer [BUFFER_SIZE], opcao;

    if (!caixa || !diretorio || !nome){
        printf ("Erro nos parametros na funcao visualizar\n");
        return 1;
    }   

    // para evitar warning por causa do const
    aux_diretorio = (Diretorio *) diretorio;
    // verifica se arquivo esta no diretorio
    indice = procura_arquivo (aux_diretorio, nome);
    if (indice == -1){
        printf ("Arquivo nao esta no diretorio para ser visualizado\n");
        return 1;
    }
    
    aux_caixa = fopen (caixa, "rb");
    if (!aux_caixa){
        perror ("Erro ao abrir caixa na funcao visualizar");
        return 1;
    }

    // obtem a posicao inicial e o tamanho do arquivo no diretorio
    pos_inicial = diretorio->arquivos[indice].offset;
    tam_total = diretorio->arquivos[indice].tamanho;
    bytes_percorridos = 0; // para auxiliar navegacao

    while (1){
        // mostra o bloco
        printf ("\nArquivo: %s [%ld bytes]\n", nome, tam_total);

        // posiciona o ponteiro no arquivo apos os bytes ja visualizados
        fseek (aux_caixa, pos_inicial + bytes_percorridos, SEEK_SET);

        // calcula quanto falta do arquivo a partir da posicao atual
        resto_bloco = tam_total - bytes_percorridos;
        if (resto_bloco > BUFFER_SIZE){
            a_ler = BUFFER_SIZE; // ainda ha parte do bloco para ler
        }
        else{
            a_ler = resto_bloco; // recebe apenas o que falta para acarbar o arq
        }

        lido = fread (aux_buffer, 1, a_ler, aux_caixa);
        // exibe conteudo do bloco, sem corromper terminal com lixo de memoria
        fwrite (aux_buffer, 1, lido, stdout);

        do{
            printf (" Digite:\n"); 
            printf ("[n] - Proximo bloco\n");
            printf ("[p] - Bloco anterior\n");
            printf ("[q] - Sair da navegação\n");
            
            if (scanf (" %c", &opcao) != 1){
                break; // teste para leitura falha 
            }

            if (opcao != 'n' && opcao != 'p' && opcao != 'q'){
                printf ("Por favor digite uma opção valida\n");
            }

        } while (opcao != 'n' && opcao != 'p' && opcao != 'q');

        if (opcao == 'q'){
            break;
        }

        else if (opcao == 'n'){

            // Verifica se existe um proximo bloco
            if (bytes_percorridos + BUFFER_SIZE < tam_total){
                bytes_percorridos = bytes_percorridos + BUFFER_SIZE;
            }
            else {
                printf ("\nFim do arquivo\n");
                break;
            }
        }

         else {// opcao == 'p'

            // Verifica se existe um bloco anterior
            if (bytes_percorridos > 0)
                bytes_percorridos = bytes_percorridos - BUFFER_SIZE;

            else 
                printf ("\n---Você esta no primeiro bloco\n");            
        }
    }
    
    fclose (aux_caixa);
    return 0;
}   