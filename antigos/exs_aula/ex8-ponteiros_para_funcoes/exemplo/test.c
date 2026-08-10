#include <stdio.h>

void funcao1 (){

    printf ("hello word!\n");
}

float funcao2 (int x, float y){
    float aux;

    aux = x + y;
    return aux;
}

int main(){
    void (*ponteiro1) ();
    float (*ponteiro2) (int, float);


    ponteiro1 = funcao1;
    ponteiro1();

    ponteiro2 = funcao2;

    float soma = ponteiro2 (10, 5.5);
    printf ("%.2f\n", soma);

    return 0;
}