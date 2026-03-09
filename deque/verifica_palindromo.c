#include "deque.h"
#include <string.h>

int main (){
    struct deque *novo;
    char test[100];

    novo = deque_cria ();
    

    novo = destroi_deque (novo);
    return 0;
}