#ifndef Clientes_H
#define Clientes_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "avl.h"


typedef struct catalogo_clientes *CatClientes;
typedef struct iterador_cat_clientes *IT_CAT_CLIENTES;
typedef struct cat_lista_clientes *CAT_LISTA_CLIENTES;
typedef struct cat_paginador_lista_clientes *CAT_PAG_LISTA_CLIENTES;

CatClientes inicializa_catalogo_clientes();
void insertC(CatClientes c, char * valor);
void cat_remove_cliente(CatClientes cat, char *str);
void free_catalogo_Clientes(CatClientes cat);
int existeCliente (char *cliente,CatClientes cat);
int numeroClientes(CatClientes cat);
int numeroClientesLetra(CatClientes cat, char letra);





#endif
