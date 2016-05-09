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
void fil_insere_prod(Filial fil, char *cliente, char *produto,int q, int mes, float preco, char p);
int getQuantidadeMesCliente(Filial fil, char *cliente, int mes);
ARRAY naoCompraram(Filial fil);
ARRAY compraram(Filial fil);
void clientesCompraram(Filial fil,ARRAY a);
void free_filial(Filial fil);
ARRAY topMaisGastou(ARRAY a);
ARRAY clientesCompraramProduto(Filial fil, char* produto);
int comprouProdutoN(Filial fil, char* cliente, char* produto);
int comprouProdutoP(Filial fil, char* cliente, char* produto);
int getNumClientesFilial(Filial fil, char* produto);
void getIProdMes(Filial fil, char* cliente, int mes, ARRAY a);
ARRAY extraiPorQuantidade(ARRAY a,int mes);
void removeNaoCompraram(Filial fil, ARRAY a);
void removeCompraram(Filial fil, ARRAY a);
#endif
