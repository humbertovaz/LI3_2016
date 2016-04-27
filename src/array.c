
#include "headers/array.h"



struct array{
    void **elementos;
    int posicao;
    int capacidade;
};

static void quicksort(void **elems, compara_elems *f_comparacao, int n, void *param);
static void array_realloc(ARRAY a);
/*inits e frees*/

/* A funcão inicializa_array chama a funcão inicializa_array_cap com 20 slots   */
ARRAY inicializa_array(){
    return inicializa_array_cap(20);
}

/* A funcão inicializa_array_cap aloca um array com a capacidade passada por parâmetro, aloca espaco para os elementos, inicializa a posicão a zero e inicializa a capacidade passada por parametro */
ARRAY inicializa_array_cap(int capacidade){
    ARRAY array = (ARRAY) malloc(sizeof(struct array));
    
    array->elementos = (void **) malloc(sizeof(void *) * capacidade);
    
    if(array->elementos != NULL){
        array->posicao = 0;
        array->capacidade = capacidade;
    }
    
    return array;
}

/* A funcão deep_free percorre o array passado por parametro e para além de eliminar todos os elementos do array, faz free no final da estrutura elementos bem como free do array*/ 
void deep_free(ARRAY a, elimina_elems *f_eliminacao) {
    int i;
    if (a != NULL) {
        for (i = 0; i < a->posicao; i++) f_eliminacao(a->elementos[i]);
        free(a->elementos);
    }
    free(a);
}
/* A funcão array_free faz free da estrutura elementos bem como free do array*/
void array_free(ARRAY a) {
    if (a != NULL) {
        free(a->elementos);
    }
    free(a);
}


/*insercoes e remocoes*/
/* A funcão remove_posicao comeca a percorrer o array passado por parametro na posicão fornecida, coloca o apontador da posicão atual a apontar para o proximo elemento e assim sucessivamente até ao final do array. Desta maneira apenas elimina a posicão atual, ficando o array com -1 elemento do que o original */
void remove_posicao(ARRAY a, int pos){
    int i;    
    for(i=pos;i<a->posicao;i++){
        free(a->elementos[i]);
        a->elementos[i] = a->elementos[i + 1];
    }
    
    a->posicao--;
}

/* A funcão remove_elemento tenta eliminar um elemento existente no array passado por parametro, calculando o seu indice atraves da funcão get_posicao. Se existir chama a funcão remove_posicao, se não nada faz */
void remove_elemento(ARRAY a, void *elemento, compara_elems *f_compara, void *param){
    int posicao = get_posicao(a,elemento,f_compara, param);  
    if(posicao != -1)
        remove_posicao(a, posicao);
}


/* A funcão insere_elemento coloca um elemento de tipo indeterminado no array fornecido por parametro com o auxilio da funcão insere_elemento_pos na ultima posicão do array*/
void insere_elemento(ARRAY a, void *elemento){
    insere_elemento_pos(a, a->posicao, elemento);
}
/* A funcão insere_elemento_pos, inicialmente realoca o array com o dobro da capacidade usando a funcão array_realoc. Depois insere o elemento passado por parametro no array passado por parametro na posicão indicada*/
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
/* A funcão get_elemento vai buscar o elemento do array dada a posicão passada por parametro, se existir devolve o elemento se não devolve NULL*/
void *get_elemento(ARRAY a, int pos){
    return pos < a->posicao ? a->elementos[pos] : NULL;
}
/* A funcão binarysearch faz a pesquisa binária de um elemento */
int binarysearch(ARRAY a, void *elemento, compara_elems *f_compara,void *param){
    int m, fim,inicio;
    inicio =0;
    fim=get_tamanho(a)-1;
    while(inicio<=fim){
        m=(inicio+fim)/2;
        if(f_compara(elemento,a->elementos[m],param)==0){
            return m;
        }
        else if(f_compara(elemento,a->elementos[m],param)>0){
            inicio=m+1;
        }
        else{
            fim=m-1;
        }
    }
    return -1;
}
/* A funcão get_posicao*/
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
/* A funcão existe_elemento*/
int existe_elemento(ARRAY a, void *elemento, compara_elems *f_compara, void *param){
    return get_posicao(a, elemento,f_compara, param) == -1 ? 0 : 1; 
}


/* A funcão get_tamanho*/
int get_tamanho(ARRAY a){
    return a->posicao;
}
/* A funcão get_capacidade*/
int get_capacidade(ARRAY a){
    return a->capacidade;
}

/* A funcão ordena*/
void ordena(ARRAY a, compara_elems *f_comparacao, void *param) {
    quicksort(a->elementos, f_comparacao, a->posicao, param);
}

/* A funcão get_num_paginas_numero*/
int get_num_paginas_numero(ARRAY a,int x){
    int pags = get_tamanho(a)/x;
    if (get_tamanho(a)%x==0) return pags;
    else return (pags+1);
}
/* A funcão get_num_elems_pag_numero*/
int get_num_elems_pag_numero(ARRAY a, int pag, int x){
    if (pag==(get_tamanho(a)+1)) return get_tamanho(a)%x;
    else return 3;
}

/* A funcão get_num_paginas*/
int get_num_paginas(ARRAY a){
    int pags = get_tamanho(a)/10;
    if (get_tamanho(a)%10==0) return pags;
    else return (pags+1);
}
/* A funcão get_num_elems_pag*/
int get_num_elems_pag(ARRAY a, int pag){
    if (pag==(get_tamanho(a)+1)) return get_tamanho(a)%10;
    else return 10;
}
/* A funcão array_realloc*/
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

/* A funcão quicksort*/
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











