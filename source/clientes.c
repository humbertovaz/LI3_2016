#include "clientes.h"
#include <math.h>

int alturaC(NodoC N)
{
    if (N == NULL)
        return 0;
    return N->altura;
}

int max(int x,int y){
return x>y?x:y;
}


NodoC novoNodoC(char * valor)
{
    struct clt* nodo = (NodoC)malloc(sizeof(struct clt));
    strcpy(nodo->codigo, valor);
    nodo->esq   = NULL;
    nodo->dir   = NULL;
    nodo->altura = 1;  /* novo NodoC adicionado como folha*/
    return(nodo);
}

/* simples rotação á esquerda */
NodoC rotateLeft (NodoC x) {
	
       NodoC y = x->dir;
    NodoC T2 = y->esq;
 
    /* Rotação */
    y->esq = x;
    x->dir = T2;
 
    /*  Update altura */
    x->altura = max(alturaC(x->esq), alturaC(x->dir))+1;
    y->altura = max(alturaC(y->esq), alturaC(y->dir))+1;


	return y;
}

/* simples rotação á direita*/

NodoC rotateRight (NodoC y) {
    
  NodoC x = y->esq;
  
  NodoC T2 = x->dir;
 
    /* Rotação */
    x->dir = y;
    y->esq = T2;
 
    /* Update altura */
    y->altura = max(alturaC(y->esq), alturaC(y->dir))+1;
    x->altura = max(alturaC(x->esq), alturaC(x->dir))+1;

  return x;

}




 
/* Retorna o balanceamento do nodo */
int getBalanceC(NodoC n)
{   if(n==NULL) 
     return 0;
return alturaC(n->esq) - alturaC(n->dir);
    
 
    
    }





NodoC insertC(NodoC nodo, char * valor)
{
    int balance; 
    /* 1.  Rotação normal de uma arvore */
    if (nodo == NULL) {
     return (novoNodoC(valor)); 
  	}
    if (strcmp(valor, nodo->codigo) < 0)
        nodo->esq  = insertC(nodo->esq, valor);
    else if (strcmp(valor, nodo->codigo) > 0)
        nodo->dir = insertC(nodo->dir, valor);
 
    /* 2. Update altura do nodo anterior ao nodo */
    nodo->altura = max(alturaC(nodo->esq), alturaC(nodo->dir)) + 1;
 
    /* 3. Calculo do balaceamento do nodo para verificar se fico desbalanceado */  
    balance = getBalanceC(nodo);
    /* Se ficou desbalanceado, temos 4 casos */
 
    /* esq esq Case */
    if (balance > 1 && (strcmp(valor, nodo->esq->codigo) < 0))
        return rotateRight(nodo);
 
    /* dir dir Case */
    if (balance < -1 && (strcmp(valor, nodo->dir->codigo) > 0))
        return rotateLeft(nodo);
 
    /* esq dir Case */
    if (balance > 1 && (strcmp(valor, nodo->esq->codigo) > 0))
    {
        nodo->esq =  rotateLeft(nodo->esq);
        return rotateRight(nodo);
    }
 
    /* dir esq Case */
    if (balance < -1 && (strcmp(valor, nodo->dir->codigo) < 0))
    {
        nodo->dir = rotateRight(nodo->dir);
        return rotateLeft(nodo);
    }
   
    /* retorna o apontador de novo */
    return nodo;
}

int valida (char * cliente, NodoC clientes) {

  if(clientes) {
     int rest= strcmp(clientes->codigo,cliente);
    
     if(rest==0) {return 1;}
     else {

            if (rest>0) {
                      return  valida(cliente,clientes->esq);
    
            } 
         else {
                        return valida(cliente,clientes->dir);
              }
        
          }


}

  else return 0;

}


int contaNodosC(NodoC avl)
{
	if(avl == NULL) return 0;
	return 1 + contaNodosC(avl->esq) + contaNodosC(avl->dir);
}






