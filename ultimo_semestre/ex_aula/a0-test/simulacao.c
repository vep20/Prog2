#include "lista.h"

int main (){
    struct lista *dia;

    dia = cria_dia ();
    if (!dia){
        fprintf("erro ao criar lista do dia\n");
        return 0;
    }

    for (int i = 1; i <= dia->qtd_maquina; i++){
        dia->senti->prox = cria_maquian (dia, i);
        
        if (!dia->senti->prox){
            fprintf("erro ao criar maquina");
            break;
        }
    }
}