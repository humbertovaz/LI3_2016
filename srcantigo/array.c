#include <stdlib.h>
#include "headers/array.h"



struct array{
    void **elementos;
    int posicao;
    int capacidade;
};

static void quicksort(void **elems, compara_elems *f_comparacao, int n, void *param);
static void array_realloc(ARRAY a);
/*inits e frees*/

ARRAY inicializa_array(){
    return inicializa_array_cap(20);
}


ARRAY inicializa_array_cap(int capacidade){
    ARRAY array = (ARRAY) malloc(sizeof(struct array));
    
    array->elementos = (void **) malloc(sizeof(void *) * capacidade);
    
    if(array->elementos != NULL){
        array->posicao = 0;
        array->capacidade = capacidade;
    }
    
    return array;
}


void deep_free(ARRAY a, elimina_elems *f_eliminacao) {
    int i;
    if (a != NULL) {
        for (i = 0; i < a->posicao; i++) f_eliminacao(a->elementos[i]);
        free(a->elementos);
    }
    free(a);
}

void array_free(ARRAY a) {
    if (a != NULL) {
        free(a->elementos);
    }
    free(a);
}


/*insercoes e remocoes*/

void remove_posicao(ARRAY a, int pos){
    int i;    
    for(i=pos;i<a->posicao;i++)
        a->elementos[i] = a->elementos[i + 1];
    
    a->posicao--;
}


void remove_elemento(ARRAY a, void *elemento, compara_elems *f_compara, void *param){
    int posicao = get_posicao(a,elemento,f_compara, param);  
    if(posicao != -1)
        remove_posicao(a, posicao);
}



void insere_elemento(ARRAY a, void *elemento){
    insere_elemento_pos(a, a->posicao, elemento);
}

void insere_elemento_pos(ARRAY a, int pos, void *elemento){
    int i;
    array_realloc(a);
    for(i=a->posicao;i>pos;i--){
        a->elementos[i] = a->elementos[i-1];
    }
    a->elementos[pos] = elemento;
    a->posicao++;
}



/* outras funcoes*/
void *get_elemento(ARRAY a, int pos){
    return pos < a->posicao ? a->elementos[pos] : NULL;
}



int get_posicao(ARRAY a, void *elemento,compara_elems *f_compara, void *param){
    int encontrado =0;
    int pos_encontrado=-1;
    int i=0;
    
    for(i=0;i<a->posicao && !encontrado;i++){
        if(f_compara(elemento, a->elementos[i], param)==0){
            encontrado = 1;
            pos_encontrado = i;
        }
    }
    
    return pos_encontrado;
    
}

int existe_elemento(ARRAY a, void *elemento, compara_elems *f_compara, void *param){
    return get_posicao(a, elemento,f_compara, param) == -1 ? 0 : 1; 
}



int get_tamanho(ARRAY a){
    return a->posicao;
}

int get_capacidade(ARRAY a){
    return a->capacidade;
}


void ordena(ARRAY a, compara_elems *f_comparacao, void *param) {
    quicksort(a->elementos, f_comparacao, a->posicao, param);
}





int get_num_paginas(ARRAY a){
    int pags = get_tamanho(a)/10;
    if (get_tamanho(a)%10==0) return pags;
    else return (pags+1);
}

int get_num_elems_pag(ARRAY a, int pag){
    if (pag==(get_tamanho(a)+1)) return get_tamanho(a)%10;
    else return 10;
}

static void array_realloc(ARRAY a){
    int nova_cap;
    void **novo;
    
    if(a->posicao == a->capacidade){
        nova_cap = a->capacidade*2;
        novo = (void **) realloc(a->elementos,sizeof(void *) * nova_cap);
        
        if (novo != NULL){
            a->elementos=novo;
            a->capacidade= nova_cap;
        }
    }
}


static void quicksort(void **elems, compara_elems *f_comparacao, int n, void *param){
    int i, j;
    void *p, *temp;
    
    if (n < 2) return;
    p = elems[n/2];
    
    for (i = 0, j = n - 1;; i++, j--) {
        
        while(f_comparacao(elems[i],p, param)<0) i++;
        while(f_comparacao(p,elems[j], param)<0)j--;
        if (i >= j) break;
        
        temp = elems[i];
        elems[i] = elems[j];
        elems[j] = temp;
    }
    quicksort(elems,f_comparacao, i, param);
    quicksort(elems+i,f_comparacao, n - i, param);
}











