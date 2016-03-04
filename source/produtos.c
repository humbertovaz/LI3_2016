
#include "produtos.h"

int maxP(int x,int y){
return x>y?x:y;
}

/* Função para calcular a altura da arvore */
int alturaP(NodoP N)
{
    if (N == NULL)
        return 0;
    return N->altura;
}
 
/* Função que aloca um novo NodoP com o valor recebido e inicializa a esq e dir a NULL. */
NodoP novoNodoP(char * valor)
{
    struct prod* nodo = (NodoP)malloc(sizeof(struct prod));
    strcpy(nodo->code, valor);
    nodo->esq   = NULL;
    nodo->dir   = NULL;
    nodo->altura = 1;  /* novo NodoP adicionado como folha */
    return(nodo);
}
 
/* Função que faz a rotação à direita */
NodoP dirRotateP(NodoP y)
{
    NodoP x = y->esq;
    NodoP T2 = x->dir;
 
    /* Rotação */
    x->dir = y;
    y->esq = T2;
 
    /* Update altura */
    y->altura = maxP(alturaP(y->esq), alturaP(y->dir))+1;
    x->altura = maxP(alturaP(x->esq), alturaP(x->dir))+1;
 
    /* Return novo root */
    return x;
}
 
/* Função que faz a rotação à esquerda */
NodoP esqRotateP(NodoP x)
{
    NodoP y = x->dir;
    NodoP T2 = y->esq;
 
    /* Rotação */
    y->esq = x;
    x->dir = T2;
 
    /*  Update altura */
    x->altura = maxP(alturaP(x->esq), alturaP(x->dir))+1;
    y->altura = maxP(alturaP(y->esq), alturaP(y->dir))+1;
 
    /* Return novo root */
    return y;
}
 
/* Retorna o balanceamento do nodo */
int getBalanceP(NodoP N)
{
    if (N == NULL)
        return 0;
    return alturaP(N->esq) - alturaP(N->dir);
}
 
NodoP insertP(NodoP nodo, char * valor)
{
    int balance;
    /* 1.  Rotação normal de uma arvore */
    if (nodo == NULL){
     

    return(novoNodoP(valor));
 }
    if (strcmp(valor, nodo->code) < 0)
        nodo->esq  = insertP(nodo->esq, valor);
    else if (strcmp(valor, nodo->code) > 0)
        nodo->dir = insertP(nodo->dir, valor);
 
    /* 2. Update altura do nodo anterior ao nodo */
    nodo->altura = maxP(alturaP(nodo->esq), alturaP(nodo->dir)) + 1;
 
    /* 3. Calculo do balaceamento do nodo para verificar se fico desbalanceado */
    balance = getBalanceP(nodo);
 
    /* Se ficou desbalanceado, temos 4 casos */
 
    /* esq esq Case */
    if (balance > 1 && (strcmp(valor, nodo->esq->code) < 0))
        return dirRotateP(nodo);
 
    /* dir dir Case */
    if (balance < -1 && (strcmp(valor, nodo->dir->code) > 0))
        return esqRotateP(nodo);
 
    /* esq dir Case */
    if (balance > 1 && (strcmp(valor, nodo->esq->code) > 0))
    {
        nodo->esq =  esqRotateP(nodo->esq);
        return dirRotateP(nodo);
    }
 
    /* dir esq Case */
    if (balance < -1 && (strcmp(valor, nodo->dir->code) < 0))
    {
        nodo->dir = dirRotateP(nodo->dir);
        return esqRotateP(nodo);
    }
 
    /* retorna o apontador de novo */
    return nodo;
}


int contaNodosP(NodoP avl)
{
	if(avl == NULL) return 0;
	return 1 + contaNodosP(avl->esq) + contaNodosP(avl->dir);
}


int validaProdutos (char *produtos,NodoP produto) {
   

  if(produto) {
   
     int rest= strcmp(produto->code,produtos);
    
     if(rest==0) {return 1;}
     else {
                   
            if (rest>0) {
                       return validaProdutos(produtos,produto->esq);
                        
            } 
         else {  return validaProdutos(produtos,produto->dir);
              } 
        
          }
}

 else return 0;

}
