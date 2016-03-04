#ifndef CLIENTES_H
#define CLIENTES_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define CD 8


typedef struct clt {
char codigo[CD];
struct clt *dir,*esq;
int altura;
}*NodoC;



NodoC insertC(NodoC nodo, char * valor);
int valida (char * cliente, NodoC clientes);
int contaNodosC(NodoC avl);
NodoC insertC(NodoC nodo, char * valor);
NodoC novoNodoC(char * valor);
int max(int x,int y);
int alturaC(NodoC N);




#endif
