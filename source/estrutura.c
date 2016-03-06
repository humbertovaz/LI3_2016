#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Nodo{
	char code[8];
	int altura;
	struct Nodo *l,*r;
} *AVL,nodo;


void deleteTree(AVL a){
	if (a!=NULL){
		deleteTree(a->l);
		deleteTree(a->r);
		free(a);
	}
}


int existe(AVL a, char s[]){
	if (a==NULL) return 0;
	if (strcmp(a->code,s)==0) return 1;
	if (strcmp(a->code,s)==-1) return existe(a->l,s);
	return existe(a->r,s);
}


int altura (AVL a){
	if (a==NULL) return -1;
	return a->altura;
}


int max( int l, int r){
    return l > r ? l: r;
}


AVL rotateLeft(AVL a){
	AVL aux = a->l;
	a->l=aux->r;
	aux->r=a;
	a->altura=max(altura(a->l),altura(a->r))+1;
	aux->altura=max(altura(aux->l),altura(aux->r))+1;
	return aux;
}


AVL rotateRight(AVL a){
	AVL aux = a->r;
	a->r=aux->l;
	aux->l=a;
	a->altura=max(altura(a->l),altura(a->r))+1;
	aux->altura=max(altura(aux->l),altura(aux->r))+1;
	return aux;
}

AVL doubleRotateLeft(AVL a){
	a->l=rotateRight(a->l);
	return rotateLeft(a);
}

AVL	doubleRotateRight(AVL a){
	a->r=rotateLeft(a->r);
	return rotateRight(a);
}

AVL inserir(char s[], AVL a){
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


void imprime(AVL a){
	if(a==NULL) return;
	printf("%s\n",a->code);
	imprime(a->l);
	imprime(a->r);
}



















