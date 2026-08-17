#ifndef LABROB
#define LABROB

struct robo {
    int id; // identificacao
    int qtd_sens; // quantidade de sensores
    int *conj_sens; // conjunto de sensores
    struct robo *prox;
};

struct lab {
    struct robo *robos;
};

struct lab *crialab ();

void cadastrar_robo (struct lab *dinf, int id, int qtd_sensores);

void analisa_robos (struct lab *dinf);

void att_robo (struct lab *dinf, int id);

// remove robo
// encerra programa
#endif