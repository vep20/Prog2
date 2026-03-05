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

// função que insere um item no inicio de um deque
void insere_inicio (struct deque *d, char c);

// função que insere um item no fim de um deque
void insere_fim (struct deque *d);

struct deque_nodo remove_ini ();

struct deque_nodo remove_fim ();

//função que retorna a quantidade de items que possui um deque
int tam (struct deque *d);