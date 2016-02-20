#include <stdlib.h>
#include <string.h>
#include "produtos.h"

void deleteP(AVL a){
	if (a!=NULL){
		deleteTree(a->l);
		deleteTree(a->r);
		free(a);
	}
}


int existeP(Produtos a, char s[]){
	if (a==NULL) return 0;
	if (strcmp(a->code,s)==0) return 1;
	if (strcmp(a->code,s)==-1) return existe(a->l,s);
	return existe(a->r,s);
}


int alturaP (Produtos a){
	if (a==NULL) return -1;
	return a->altura;
}


int maxP( int l, int r){
    return l > r ? l: r;
}


Produtos rotateLeftP(Produtos a){
	AVL aux = a->l;
	a->l=aux->r;
	aux->r=a;
	a->altura=max(altura(a->l),altura(a->r))+1;
	aux->altura=max(altura(aux->l),altura(aux->r))+1;
	return aux;
}


Produtos rotateRightP(Produtos a){
	AVL aux = a->r;
	a->r=aux->l;
	aux->l=a;
	a->altura=max(altura(a->l),altura(a->r))+1;
	aux->altura=max(altura(aux->l),altura(aux->r))+1;
	return aux;
}

Produtos doubleRotateLeftP(Produtos a){
	a->l=rotateRight(a->l);
	return rotateLeft(a);
}

Produtos doubleRotateRightP(Produtos a){
	a->r=rotateLeft(a->r);
	return rotateRight(a);
}

Produtos inserirP(char s[], Produtos a){
	if (a==NULL){
		a= (AVL) malloc(sizeof(nodo));
		if (a==NULL) exit(1);
		strcpy(a->code,s);
		a->altura=0;
		a->l=NULL;
		a->r=NULL;
	}
	else if(strcmp(a->code,s)>0){
		a->l=inserir(s,a->l);
		if(altura(a->l)-altura(a->r)==2){
			if (strcmp(s,a->l->code)<0) a=rotateLeft(a);
			else a=doubleRotateLeft(a);
		}
	}
	else if(strcmp(a->code,s)<0){
		a->r=inserir(s,a->r);
		if (altura(a->r)-altura(a->l)==2){
			if (strcmp(s,a->r->code)>0) a=rotateRight(a);
			else a= doubleRotateRight(a);
		}
	}
	a->altura=max(altura(a->l),altura(a->r))+1;
	return a;
}



















