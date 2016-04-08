#ifndef FILIAL_H
#define FILIAL_H
#include <stdlib.h>
#include <string.h>
#include "avl.h"


typedef struct filial *Filial;
typedef struct icliente *Icliente;
typedef struct iprodutos *Iprodutos;


Filial inicializa_filial();
void fil_regista_cliente(Filial fil, char *cliente);
void fil_insere_prod(Filial fil, char *cliente, char *produto,int q, int filial, int mes, float preco);


#endif
