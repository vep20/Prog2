#ifndef ESTEIRA
#define ESTEIRA

struct porcao {
    int id;
    int uni;
    struct porcao *prox;
};

struct esteira {
    int tam;
    struct porcao *prim;
};

struct esteira *esteira_cria ();

struct esteira *esteira_destroi (struct esteira *e);

struct porcao *cria_porcao (int id, int uni);

void cadastra_porcao (struct esteira *e, int id, int uni);

void retira_porcao (struct esteira *e, int id);

void imprime_esteira (struct esteira *e);

int esteira_tamanho (struct esteira *e);

long aleat (long min, long max);

#endif 