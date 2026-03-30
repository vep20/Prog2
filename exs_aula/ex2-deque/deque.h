#include <stdio.h>
#include <stdlib.h>

struct deque_nodo{
    char item;
    struct deque_nodo *ant;
    struct deque_nodo *prox;
};

struct deque{
    int tam;
    struct deque_nodo *pri;
    struct deque_nodo *ult;
};

struct deque *cria();

// Apos verificaar destroi o deque;
// função que verifica se há elementos e um deque, se sim os retira.
struct deque *destroi_deque (struct deque *d);

// função que insere um item no inicio de um deque
void insere_inicio (struct deque *d, char c);

// função que insere um item no fim de um deque
void insere_fim (struct deque *d, char c);

// função que remove um item no comeco de um deque (propriedade fila)
void remove_ini (struct deque *d);

// função que remove um item no fim de um deque 
void remove_fim (struct deque *d);

//função que retorna a quantidade de items que possui um deque
int tam (struct deque *d);