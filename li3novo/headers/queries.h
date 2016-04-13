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
void querie6(Faturacao fat, int a, int b);
void querie7(Filial fil);
void querie8(Filial fil, char* produto, int filial);
void querie9(Filial fil, char* cliente, int mes);
void querie10(Faturacao fat,Filial fil, int n);
void querie11(Filial fil, char* cliente);
void querie12(Filial fil, Faturacao fat);

#endif	

