#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gbv.h"
#include "util.h"

// superbloco: guarda o numero de documentos e a posição do diretorio

// area de dados: onde os arquivos ficam armazenados em sequencia

// area de diretório: contem os metadados (nome, tamanho, data e offset)
//                    dos documentos

int gbv_create (const char *filename){
    FILE *aux_arq; // ponteiro para manipulação de arquivo
    int count;
    long dir_offset;

    count = 0;
    // inicio logo apos o superbloco 0-3 int e 4-11 long
    dir_offset = sizeof (int) + sizeof (long); 
    
    // abre o arquivo passado para escrita em binario
    aux_arq = fopen (filename, "wb");
    if (!aux_arq)    
        return 1; //retorna caso arquivo não seja criado ou resetado

    // grava o numero de documentos, no caso como esta vazio 0
    fwrite (&count, sizeof (int), 1, aux_arq);
    
    // grava onde o diretorio inicia
    fwrite (&dir_offset, sizeof (long), 1, aux_arq);

    fclose (aux_arq);
    return 0;
}

int gbv_open (Library *lib, const char *filename){  
    FILE *aux_arq;
    long aux_offset;

    if (!lib || !filename)
        return 1;

    // abre o arquivo para leitura em binario 
    aux_arq = fopen (filename, "rb");
    if (!aux_arq){
        printf ("Erro ao abrir o arquivo\n");
        return 1;
    }

    // recupera o count no arquivo para gravar na biblioteca
    fread (&lib->count, sizeof (int), 1, aux_arq);

    // armazena onde o diretorio inicia no auxiliar
    fread (&aux_offset, sizeof (long), 1, aux_arq);
    
    if(lib->count > 0){ // verifica se há documentos
        lib->docs = malloc (sizeof (Document) * lib->count);
        if (!lib->docs)   
            return 1;

        // posiciona o ponteiro de arquivo no inicio da area de diretorio   
        fseek (aux_arq, aux_offset, SEEK_SET); // seek_set pe a partir do inicio do arq

        // realiza a leitura de todos os documentos e armazena na biblioteca
        fread (lib->docs, sizeof (Document), lib->count, aux_arq);    
    }

    else 
        lib->docs = NULL;
    
    fclose (aux_arq);
    return 0;
}

int gbv_list(const Library *lib){
    char aux_buffer[30];

    if (!lib)
        return 1;

    if (lib->count == 0)
        printf ("Não há documentos na biblioteca\n");

    else 
        printf ("Quantidade de documentos na biblioteca %d\n", lib->count);    

    for(int i = 0; i < lib->count; i++){
        printf ("Arquivo %d:\n", i);
        printf ("Nome: %s\n", lib->docs[i].name);
        printf ("Tamanho: %ld\n", lib->docs[i].size);

        // impressão da data no formato padrão exigido
        format_date (lib->docs[i].date, aux_buffer, 30);
        printf ("Data: %s\n", aux_buffer);

        printf ("Offset: %ld\n", lib->docs[i].offset);
    }

    return 0; 
}

int gbv_search (const Library *lib, const char *docname){
    int aux;

    aux = -1;

     for (int i = 0; i < lib->count; i++){
        // comparação caracter a caracter para verificar se
        // o documento esta na biblioteca
        if (strcmp(lib->docs[i].name, docname) == 0){
            aux = i;
            break;// documento encontrado
        }
    }

    return aux;
}

int gbv_view(const Library *lib, const char *archive, const char *docname){
    FILE *aux_arq;
    size_t lido;
    long offset_inicial, tam_total, bytes_percorridos, restante_bloco, a_ler;
    int indice;
    char aux_buffer[BUFFER_SIZE], opcao;

    if (!lib || !archive || !docname)
        return 1;

    indice = gbv_search (lib, docname);
   
    if (indice == -1){
        printf ("Documento não esta na biblioteca\n");
        return 1; 
    }

    aux_arq = fopen (archive, "rb");
    if (!aux_arq){
        printf ("Erro ao abrir arquivo da biblioteca\n");
        return 1;
    }

    // posicão inicia a partir do indice encontrado
    offset_inicial = lib->docs[indice].offset;
    tam_total = lib->docs[indice].size;
    bytes_percorridos = 0; // aux de deslocamento da navegação 

    // loop para visualização por blocos 
    while (1){
        // mostra o bloco
        printf ("\n--- Bloco: %s [%ld bytes] ---\n", docname, tam_total);

        // posiciona o cursor do inicio do documento + o deslocamento da visualização
        fseek (aux_arq, offset_inicial + bytes_percorridos, SEEK_SET);

        // calcula tamanho do bloco
        restante_bloco = tam_total - bytes_percorridos;

        if (restante_bloco > BUFFER_SIZE)
            a_ler = BUFFER_SIZE; // ainda ha blocos a serem lidos

        else 
            a_ler = restante_bloco; // le apenas o que falta para acabar o doc

        // realiza a leitura do bloco
        lido = fread (aux_buffer, 1, a_ler, aux_arq);
        
        // realiza a exibição do conteudo 
        fwrite (aux_buffer, 1, lido, stdout);

        do{
            printf (" Digite:\n"); 
            printf ("[n] - Proximo bloco\n");
            printf ("[p] - Bloco anterior\n");
            printf ("[q] - Sair da navegação\n");
            
            if (scanf (" %c", &opcao) != 1)
                break; // teste para leitura falha 

            if (opcao != 'n' && opcao != 'p' && opcao != 'q')
                printf ("Por favor digite uma opção valida\n");

        } while (opcao != 'n' && opcao != 'p' && opcao != 'q');

        if (opcao == 'q')
            break;

        else if (opcao == 'n'){

            // Verifica se existe um proximo bloco
            if (bytes_percorridos + BUFFER_SIZE < tam_total)
                bytes_percorridos = bytes_percorridos + BUFFER_SIZE;
            else {
                printf ("\n---Fim do documento---\n");
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

    fclose(aux_arq);
    return 0;
}

int gbv_add(Library *lib, const char *archive, const char *docname){
    FILE *novo_arq, *aux_arq;
    Document *temp, aux_doc;
    long tam_arq, novo_offset, dir_offset, novo_dir_offset;
    char aux_buffer[BUFFER_SIZE];
    size_t bytes_percorridos;
    int indice, count;

    if (!lib || !archive || !docname)
        return 1;

    indice = gbv_search (lib, docname);

    // abre o arquivo que sera adicionado para leitura em binario
    novo_arq = fopen (docname, "rb");
    if (!novo_arq){
        printf ("Erro ao abrir o arquivo que deveria ser add\n");
        return 1;
    }

    // Coloca o ponteiro do arquivo no final do documento
    fseek (novo_arq, 0, SEEK_END);

    // Utiliza a funcao ftell que informa qual byte estamos no arquivo
    // como estamos no final do arquivo, logo no tamanho final 
    tam_arq = ftell (novo_arq);

    // Volta para o inicio do arquivo
    rewind (novo_arq);

    aux_arq = fopen (archive, "r+b");
    if (!aux_arq){
        fclose (novo_arq);
        return 1;
    }

   // lê superbloco
    fseek(aux_arq, 0, SEEK_SET);
    fread(&count, sizeof(int), 1, aux_arq);
    fread(&dir_offset, sizeof(long), 1, aux_arq);

    // vai para início do diretório (fim da área de dados)
    fseek(aux_arq, dir_offset, SEEK_SET);
    novo_offset = ftell(aux_arq);

    // leitura maxima até encher o buffer  
    bytes_percorridos = fread (aux_buffer, 1, BUFFER_SIZE, novo_arq);
    while (bytes_percorridos > 0){ 
        // escreve o que esta no buffer nos documentos
        // conforme o maximo possivel segundo especificaçoes
        fwrite (aux_buffer, 1, bytes_percorridos, aux_arq);
        bytes_percorridos = fread (aux_buffer, 1, BUFFER_SIZE, novo_arq);
    }

    fclose (novo_arq);
    
    // preenche os dados e att a quantidade de docs na lib 
    strncpy(aux_doc.name, docname, MAX_NAME - 1);
    aux_doc.name[MAX_NAME - 1] = '\0';
    aux_doc.size = tam_arq;
    aux_doc.date = time(NULL);
    aux_doc.offset = novo_offset;
  
    // adiciona ou substitui
    if (indice == -1){ 
        temp = realloc(lib->docs, sizeof(Document) * (lib->count + 1));
        if (!temp){
            printf ("Erro ao realocar biblioteca\n");
            fclose(aux_arq);
            return 1;
        }
        lib->docs = temp;
        lib->docs[lib->count] = aux_doc;
        lib->count++;
    } 
    
    else 
        lib->docs[indice] = aux_doc;

    // novo diretório começa aqui
    novo_dir_offset = ftell(aux_arq);

    // escreve diretório atualizado
    fwrite(lib->docs, sizeof(Document), lib->count, aux_arq);

    // atualiza superbloco
    fseek(aux_arq, 0, SEEK_SET);
    fwrite(&lib->count, sizeof(int), 1, aux_arq);
    fwrite(&novo_dir_offset, sizeof(long), 1, aux_arq);

    fclose(aux_arq);

    return 0;
}

int gbv_remove(Library *lib, const char *archive, const char *docname){
    FILE *aux_arq;
    Document *temp;
    int indice;
    long dir_offset;

    if (!lib || !docname)
        return 1;

    indice = gbv_search (lib, docname);
    if (indice == -1){
        printf ("Documento não esta na biblioteca\n");
        return 1;     
    }

    // descola os elementos para remover o indice encontrado
    for (int i = indice; i < lib->count - 1; i++) 
        lib->docs[i] = lib->docs[i + 1];
    
    // atualiza a biblioteca
    lib->count--;
    if (lib->count > 0){
        temp = realloc (lib->docs, sizeof (Document) * lib->count);

        if (temp)
            lib->docs = temp;
        
        else
            printf ("Erro ao realocar memoria\n");
    
    }

    else {
        free(lib->docs);
        lib->docs = NULL;
    }


    aux_arq = fopen (archive, "r+b");
    if (!aux_arq){
        printf ("Erro ao abrir o arquivo");
        return 1;
    }

    // pula o count
    fseek (aux_arq, sizeof (int), SEEK_SET);
    fread (&dir_offset, sizeof(long), 1, aux_arq);

    fseek (aux_arq, dir_offset, SEEK_SET);

    // att o diretorio
    if (lib->count > 0)
        fwrite (lib->docs, sizeof (Document), lib->count, aux_arq);

    // att o Superbloco
    rewind (aux_arq);
    fwrite (&lib->count, sizeof (int), 1, aux_arq);

    fclose(aux_arq);
    return 0;
}

int cmp_nome(const void *a, const void *b){
    const Document *docA, *docB; 

    docA = (const Document *)a;
    docB = (const Document *)b;
    return strcmp(docA->name, docB->name);
}

int cmp_data(const void *a, const void *b){
    const Document *docA, *docB; 

    docA = (const Document *)a;
    docB = (const Document *)b;

    // Retorna negativo se docA for mais antigo, positivo se mais novo
    if (docA->date < docB->date) 
        return -1;

    if (docA->date > docB->date) 
        return 1;

    return 0;
}

int cmp_tamanho(const void *a, const void *b){
    const Document *docA, *docB; 

    docA = (const Document *)a;
    docB = (const Document *)b;

    // Retorna negativo se docA for menor, positivo se maior
    if (docA->size < docB->size) 
        return -1;

    if (docA->size > docB->size) 
        return 1;
    
    return 0;
}

int gbv_order(Library *lib, const char *archive, const char *criteria){
    FILE *aux_arq;
    int count_arq;
    long dir_offset;

    if (!lib || !archive || !criteria)
        return 1;

    if (lib->count <= 1)
        return 0; // Não há necessidade de ordenar 0 ou 1 elementos

    // Aplica a ordenação em memória de acordo com o critério escolhido
    if (strcmp(criteria, "nome") == 0)
        qsort(lib->docs, lib->count, sizeof(Document), cmp_nome);

    else if (strcmp(criteria, "data") == 0)
        qsort(lib->docs, lib->count, sizeof(Document), cmp_data);

    else if (strcmp(criteria, "tamanho") == 0)
        qsort(lib->docs, lib->count, sizeof(Document), cmp_tamanho);

    else {
        printf("Critério inválido. Utilize: nome, data ou tamanho.\n");
        return 1;
    }

    // Abre o arquivo contêiner para atualizar o diretório em disco
    aux_arq = fopen(archive, "r+b");
    if (!aux_arq) {
        printf("Erro ao abrir o arquivo para atualizar a ordenação.\n");
        return 1;
    }
    
    // le o superbloco para descobrir onde o diretório atual começa
    fread(&count_arq, sizeof(int), 1, aux_arq);
    fread(&dir_offset, sizeof(long), 1, aux_arq);

    // posiciona o ponteiro de gravação exatamente no início do diretório
    fseek(aux_arq, dir_offset, SEEK_SET);

    // sobrescreve o diretório refletindo a nova ordem
    fwrite(lib->docs, sizeof(Document), lib->count, aux_arq);

    fclose(aux_arq);
    return 0;
}