#ifndef Clientes_H
#define Clientes_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "avl.h"


typedef struct catalogo_clientes *CatClientes;


CatClientes inicializa_catalogo_clientes();
void insertC(CatClientes c, char * valor);
void cat_remove_cliente(CatClientes cat, char *str);
void free_catalogo_Clientes(CatClientes cat);
int existeCliente (char *cliente,CatClientes cat);
int numeroClientes(CatClientes cat);
int numeroClientesLetra(CatClientes cat, char letra);





#endif
