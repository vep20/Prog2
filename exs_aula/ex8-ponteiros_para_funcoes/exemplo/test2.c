#include <stdio.h>
#include <string.h>

void funcao1(){
    printf("Hello World\n");
}
void funcao2(){
    printf("Olá Mundo!\n");
}
void falar(char *personagem, void (*mensagem)()){
    printf("%s: ", personagem);
    mensagem();
}

int main(void){
    char language[10] = "en";

    if (!strcmp("pt-br", language))
        falar("Robert", funcao2);
        
    else if (!strcmp("en", language))
        falar("Robert", funcao1);
    
    else
        printf("entendi a parada\n");
}