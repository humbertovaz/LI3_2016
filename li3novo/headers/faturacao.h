#ifndef FATURACAO_H
#define FATURACAO_H
#include <stdlib.h>
#include <string.h>
#include "avl.h"


typedef struct faturacao *Faturacao;
typedef struct info *Info;


Faturacao inicializa_faturacao();
void cont_regista_produto(Faturacao fat, char *prod);
void cont_insere_venda(Faturacao fat, char *produto, int q, float preco, char M,int mes, int filial);
void cont_remove_produto(Faturacao fat, char *produto);
void free_faturacao(Faturacao fat);
int getNumeroTotalVendasNTodasFiliais (char* prod,int mes,Faturacao fat);
int getNumeroTotalVendasNFilialX (char* prod,int mes,Faturacao fat, int filial);
int getNumeroTotalVendasPTodasFiliais (char* prod,int mes,Faturacao fat);
int getNumeroTotalVendasPFilialX (char* prod,int mes,Faturacao fat, int filial);
int getTotalFatVendasNTodasFiliais (char* prod,int mes,Faturacao fat);
int getTotalFatNFilialX (char* prod,int mes,Faturacao fat, int filial);
int getNumeroTotalFatPTodasFiliais (char* prod,int mes,Faturacao fat);
int getTotalFatPFilialX (char* prod,int mes,Faturacao fat, int filial);

#endif
