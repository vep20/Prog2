GRR20203937 - Victor Eduardo de Paula

* Lista de arquivos: 
    - .c: gbv.c main.c util.c 
    - .h: gbv.h util.h
    - compillação: Makefile  
    - teste: grande.txt pequeno.txt minhabib.gbv 

* Dificuldades e bugs: 
    - Dificuldade na utilização de funções para acesso aos arquivos e binarios, principalmente qual variaveis utilizar em cada uma delas na função add e view
    - Dificuldade em saber quando se faz necessario criar funções auxiliares na gbv_order

* Alterações:
    - Alteração das funções view e remove , para o receber o paramentro const char *archive, no arquivo .h e na main.c;
    - Alteração na main para criar a estrutura  biblioteca, caso a mesma não exista e liberação da memoria do ponteiro lib.docs 
    - Criação das funções cmp_nome, cmp_data e cmp_tamanho para auxiliar a função gbv_order

* Comandos de teste final:
make clean
make

# Criação arquivo pequeno
echo "Este e um arquivo pequeno de teste." > pequeno.txt

# Criação Arquivo grande (cria um arquivo de texto com 1000 linhas)
for i in {1..1000}; do echo "Linha $i de texto para encher o arquivo" >> grande.txt; done

# Cria biblioteca e add os arquivos criados
./gbv -a minhabib.gbv pequeno.txt grande.txt

# Lista arquivos 
./gbv -l minhabib.gbv
    Quantidade de documentos na biblioteca 2
    Arquivo 0:
    Nome: pequeno.txt
    Tamanho: 36
    Data: 04/05/2026 16:54:02
    Offset: 12
    Arquivo 1:
    Nome: grande.txt
    Tamanho: 40893
    Data: 04/05/2026 16:54:02
    Offset: 48


# Vizualização das paginas
./gbv -v minhabib.gbv grande.txt
    --- Bloco: grande.txt [40893 bytes] ---
    Linha 1 de texto para encher o arquivo
    Linha 2 de texto para encher o arquivo
    Linha 3 de texto para encher o arquivo
    Linha 4 de texto para encher o arquivo
    Linha 5 de texto para encher o arquivo
    Linha 6 de texto para encher o arquivo
    Linha 7 de texto para encher o arquivo
    Linha 8 de texto para encher o arquivo
    Linha 9 de texto para encher o arquivo
    Linha 10 de texto para encher o arquivo
    Linha 11 de texto para encher o arquivo
    Linha 12 de texto para encher o arquivo
    Linha 13 de texto para encher o arquivo
    L Digite:
    [n] - Proximo bloco
    [p] - Bloco anterior
    [q] - Sair da navegação

    n

    --- Bloco: grande.txt [40893 bytes] ---
    inha 14 de texto para encher o arquivo
    Linha 15 de texto para encher o arquivo
    Linha 16 de texto para encher o arquivo
    Linha 17 de texto para encher o arquivo
    Linha 18 de texto para encher o arquivo
    Linha 19 de texto para encher o arquivo
    Linha 20 de texto para encher o arquivo
    Linha 21 de texto para encher o arquivo
    Linha 22 de texto para encher o arquivo
    Linha 23 de texto para encher o arquivo
    Linha 24 de texto para encher o arquivo
    Linha 25 de texto para encher o arquivo
    Linha 26 de texto para encher o a Digite:
    [n] - Proximo bloco
    [p] - Bloco anterior
    [q] - Sair da navegação
    p

    --- Bloco: grande.txt [40893 bytes] ---
    Linha 1 de texto para encher o arquivo
    Linha 2 de texto para encher o arquivo
    Linha 3 de texto para encher o arquivo
    Linha 4 de texto para encher o arquivo
    Linha 5 de texto para encher o arquivo
    Linha 6 de texto para encher o arquivo
    Linha 7 de texto para encher o arquivo
    Linha 8 de texto para encher o arquivo
    Linha 9 de texto para encher o arquivo
    Linha 10 de texto para encher o arquivo
    Linha 11 de texto para encher o arquivo
    Linha 12 de texto para encher o arquivo
    Linha 13 de texto para encher o arquivo
    L Digite:
    [n] - Proximo bloco
    [p] - Bloco anterior
    [q] - Sair da navegação
    n 
    .
    .
    .

    --- Bloco: grande.txt [40893 bytes] ---
    90 de texto para encher o arquivo
    Linha 991 de texto para encher o arquivo
    Linha 992 de texto para encher o arquivo
    Linha 993 de texto para encher o arquivo
    Linha 994 de texto para encher o arquivo
    Linha 995 de texto para encher o arquivo
    Linha 996 de texto para encher o arquivo
    Linha 997 de texto para encher o arquivo
    Linha 998 de texto para encher o arquivo
    Linha 999 de texto para encher o arquivo
    Linha 1000 de texto para encher o arquivo
    Digite:
    [n] - Proximo bloco
    [p] - Bloco anterior
    [q] - Sair da navegação
    n

    ---Fim do documento---

# Para ordenação
./gbv -a minhabib.gbv pequeno.txt        ok | 16:59:06 
./gbv -o minhabib.gbv tamanho
./gbv -l minhabib.gbv
Quantidade de documentos na biblioteca 2
Arquivo 0:
Nome: pequeno.txt
Tamanho: 36
Data: 04/05/2026 16:59:33
Offset: 40941
Arquivo 1:
Nome: grande.txt
Tamanho: 40893
Data: 04/05/2026 16:54:02
Offset: 48

# Remoção
./gbv -r minhabib.gbv pequeno.txt
./gbv -l minhabib.gbv
Quantidade de documentos na biblioteca 1
Arquivo 0:
Nome: grande.txt
Tamanho: 40893
Data: 04/05/2026 16:54:02
Offset: 48