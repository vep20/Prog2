#include <stdio.h>
#include <math.h>

void imprimir_vetor (float *v){

    printf("{");
    for (int i; i < 5; i++){
        printf ("%.1f ", v[i]);
    }
    printf ("}\n");
}

void aplica_op (float *vetor, void (*op)){

    
}

int main (){
    float vetor[5] = {1.1, 2.3, 3.6, 4.8, 5.9};

    imprimir_vetor (vetor);

    return 0;
}