#ifndef ARRAY_H
#define	ARRAY_H


typedef struct array* ARRAY;
typedef int compara_elems(void *item_a, void *item_b, void *param);
typedef void elimina_elems(void *item_a);



ARRAY inicializa_array();
ARRAY inicializa_array_cap(int);
void deep_free(ARRAY, elimina_elems *);
void array_free(ARRAY);
int get_tamanho(ARRAY a);
int get_capacidade(ARRAY a);
void insere_elemento(ARRAY a, void *elemento);
void insere_elemento_pos(ARRAY a, int pos, void *elemento);
void *get_elemento(ARRAY a, int pos);
int get_posicao(ARRAY a, void *elemento,compara_elems *f_compara, void *param);
int existe_elemento(ARRAY a, void *elemento, compara_elems *f_compara, void *param);
void ordena(ARRAY a,compara_elems *f_compara, void *param);
int get_num_paginas(ARRAY a);
int get_num_elems_pag(ARRAY a,int pag);
void quicksort2(void **elems,void **elems2,compara_elems *f_comparacao, int n);



#endif

