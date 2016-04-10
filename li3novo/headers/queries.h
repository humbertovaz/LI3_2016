#ifndef QUERIES_H
#define	QUERIES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"
#include "produtos.h"
#include "faturacao.h"
#include "filial.h"
#include "array.h"

void querie2(CatProdutos cat, char letra);
void querie3(Faturacao fat, char *produto, int mes);
void querie4(Faturacao fat);
void querie5(Filial fil, char *cliente);
void querie7(Filial fil);

#endif	

