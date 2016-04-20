#ifndef FILIAL_H
#define FILIAL_H
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "array.h"


typedef struct filial *Filial;
typedef struct icliente *Icliente;
typedef struct iprodutos *Iprodutos;


Filial inicializa_filial();
void fil_regista_cliente(Filial fil, char *cliente);
void fil_insere_prod(Filial fil, char *cliente, char *produto,int q, int filial, int mes, float preco, char p);
int getQuantidadeMesCliente(Filial fil, char *cliente, int filial, int mes);
ARRAY comprouTodasFiliais(Filial fil);
void free_filial(Filial fil);
int naoComprou(Filial fil);
ARRAY maisCompradosCliente(Filial fil, char* cliente, int mes);
ARRAY topMaisGastou(Filial fil, char *cliente);
ARRAY clientesCompraramProduto(Filial fil, char* produto, int filial);
int comprouProdutoN(Filial fil, char* cliente, char* produto, int filial);
int comprouProdutoP(Filial fil, char* cliente, char* produto, int filial);
int getNumClientesFilial(Filial fil, char* produto, int filial);
#endif
