#ifndef PRODUTOS_H
#define PRODUTOS_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "avl.h"


typedef struct catalogo_produtos *CatProdutos;


CatProdutos inicializa_catalogo_produtos();
void insertP(CatProdutos c, char * valor);
void cat_remove_produto(CatProdutos cat, char *str);
void free_catalogo_produtos(CatProdutos cat);
int existeProduto (char *produto,CatProdutos cat);
int numeroProdutos(CatProdutos cat);
int numeroProdutosLetra(CatProdutos cat, char letra);





#endif
