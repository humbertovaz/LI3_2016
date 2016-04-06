#ifndef PRODUTOS_H
#define PRODUTOS_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "avl.h"

#define CD 8

typedef struct catalogo_produtos *CatProdutos;
typedef struct iterador_cat_produtos *IT_CAT_PRODUTOS;
typedef struct cat_lista_produtos *CAT_LISTA_PRODUTOS;
typedef struct cat_paginador_lista_produtos *CAT_PAG_LISTA_PRODUTOS;

CatProdutos inicializa_catalogo_produtos();
void insertP(CatProdutos c, char * valor);
void cat_remove_produto(CatProdutos cat, char *str);
void free_catalogo_produtos(CatProdutos cat);
int existeProduto (char *produto,CatProdutos cat);
int numeroProdutos(CatProdutos cat);
int numeroProdutosLetra(CatProdutos cat, char letra);





#endif
