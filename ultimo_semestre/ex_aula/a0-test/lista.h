#ifndef LISTA
#define LISTA

struct maquina{
    int id; // identificador da maquia
    long prob; // probabilidade da maquina
    struct maquina *ant; // nodo anterior
    struct maquina *prox; // proximo nodo    
};

struct lista{
    int qtd_maquina; // numero determinado de maquinas criada no dia
    struct maquina *senti; // nodo inicial sentinela
};

// funcao que retorna um numero aleatorio para probabilidade entre 0 e 100
long aleat (long min, long max);

struct lista *cria_dia ();

struct maquina *cria_maquina (struct lista *dia_atual, int id);

// void add_maquina (struct lista *dia_atual, int id);

// void remove_maquina (struct lista *dia_atual, int id);

// void encerra_dia ();

#endif