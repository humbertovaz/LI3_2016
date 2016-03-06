#ifndef PRODUTOS_H
#define PRODUTOS_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define CD 8

typedef struct prod{
	char code[CD];
	int altura;
	struct prod *esq,*dir;
} *NodoP;

NodoP insertP(NodoP nodo, char * valor);
int maxP(int x,int y);
int alturaP(NodoP N);
NodoP novoNodoP(char * valor);
NodoP dirRotateP(NodoP y);
NodoP esqRotateP(NodoP x);
int getBalanceP(NodoP N);
NodoP insertP(NodoP nodo, char * valor);
int contaNodosP(NodoP avl);
int validaProdutos (char *produtos,NodoP produto);
NodoP removeP(NodoP p1, NodoP p2);
NodoP deleteNodoP(NodoP root, char code[]);
NodoP minValueNode(NodoP node);





#endif
