#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

struct item_t{
  int valor ;                   // valor do item
  struct item_t *ant ;          // item anterior
  struct item_t *prox ; // próximo item
};

// estrutura de uma lista
struct lista_t{
  struct item_t *prim ; // primeiro item
  struct item_t *ult ;          // último item
  int tamanho ;         // número de itens da lista
};

struct lista_t *lista_cria(){
    struct lista_t *nova_lista;

    nova_lista = malloc (sizeof (struct lista_t));

    if (!nova_lista) /*testa para verificar se há espaço para alocação na memoria*/
        return NULL;

    nova_lista->prim = NULL;
    nova_lista->ult = NULL;

}

struct lista_t *lista_destroi(struct lista_t *lst){
  int aux_item, aux_pos;

    aux_pos = 0;
    while (lst->prim) /*verifica se há algum item na lista*/
        lista_retira (lst, &aux_item, aux_pos);

    free (lst);
    return NULL; 
}

int lista_insere(struct lista_t *lst, int item, int pos){
    struct item_t *novo_item, *aux; /*um aux para percorrer a lista*/
    int aux_pos;

    if (!lst)
        return -1;

    novo_item = malloc (sizeof (struct item_t));
    if (!novo_item)
        return -1;

    novo_item->valor = item;
    novo_item->ant = NULL;
    novo_item->prox = NULL;

    if (!lista_tamanho(lst)){ /*insere o item em uma lista vazia*/
        lst->prim = novo_item;
        lst->ult = novo_item;
    }

    else if (!pos){ /*já insere na primeira posição*/
        novo_item->prox = lst->prim;
        lst->prim->ant = novo_item;
        lst->prim = novo_item;
    }

    else if (pos == -1){ /*inserção no final, definida conforme .h*/
        novo_item->ant = lst->ult;
        lst->ult->prox = novo_item;
        lst->ult = novo_item;
    }

    else{ 
        aux = lst->prim;
        /*avança até a posição desejada*/
        for (aux_pos = 0; aux_pos < pos && aux->prox; aux_pos++) 
            aux = aux->prox;
             
        if (aux_pos < pos - 1){ /*insere no final e atualiza lst->ult*/
            aux->prox = novo_item;
            novo_item->ant = aux;
            lst->ult = novo_item;
        }
        
        else{ /*insere no meio*/
            novo_item->prox = aux;
            novo_item->ant = aux->ant;
            aux->ant->prox = novo_item;
            aux->ant = novo_item;
        }
        
    }

    lst->tamanho++;
    return lst->tamanho;
}

int lista_retira(struct lista_t *lst, int *item, int pos) {
    struct item_t *aux;
    int aux_pos;

    if (!lst || pos >= lst->tamanho || !item || lst->tamanho == 0)
        return -1;

    if (pos == -1 || pos == lst->tamanho - 1) {  /*retira do final*/
        aux = lst->ult;

        if (lst->ult->ant)  /*quando há mais de um item*/
            lst->ult = lst->ult->ant;
        else {  /* quando só há um item na lista*/
            lst->ult = NULL;
            lst->prim = NULL;
        }
        
        if (aux->ant)
            aux->ant->prox = NULL;
    } else {
        aux = lst->prim;
        
        /* avança até a posição desejada*/
        for (aux_pos = 0; aux_pos < pos && aux->prox; aux_pos++)
            aux = aux->prox;

        if (aux == lst->prim) {  /*retira do início*/
            lst->prim = aux->prox;
            if (aux->prox)
                aux->prox->ant = NULL;
        } else {  /*retira do meio*/
            if (aux->ant)
                aux->ant->prox = aux->prox;
            if (aux->prox)
                aux->prox->ant = aux->ant;
        }
    }

    *item = aux->valor;  /*retorna o valor do item retirado*/
    free(aux);
    lst->tamanho--;

    return lst->tamanho;
}

int lista_consulta(struct lista_t *lst, int *item, int pos){
    struct item_t *aux;

    if (!lst || pos > lst->tamanho - 1)
        return -1;
    
    if (pos == -1)
        *item = lst->ult->valor;

    else{ 
        aux = lst->prim;
        for(int i = 0; i < pos; i++)
          aux = aux->prox;
        *item = aux->valor;
    }

    return lst->tamanho;
}

int lista_procura(struct lista_t *lst, int valor){
    struct item_t *aux;
    int aux_pos;

    if (!lst)
        return -1;

    aux = lst->prim;
    for (aux_pos = 0; aux_pos < lst->tamanho - 1 && aux->valor != valor; aux_pos++) 
            aux = aux->prox;

    if (!aux->prox && aux->valor != valor)
        return -1;
    
    return aux_pos;
}

int lista_tamanho(struct lista_t *lst){
    
    if (!lst)
        return -1;
    return lst->tamanho;
}

void lista_imprime(struct lista_t *lst){
    struct item_t *aux;

    if (!lista_tamanho(lst))
        return;
    
    aux = lst->prim;
    printf("%d", aux->valor); /*impressão para não haver espaços em branco*/
    aux = aux->prox;
    for (int i = 1; i < lst->tamanho; i++){
        printf(" %d", aux->valor);
        aux = aux->prox;
    }
}