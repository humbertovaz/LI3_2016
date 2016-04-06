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

#endif
