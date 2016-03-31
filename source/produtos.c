
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
<<<<<<< HEAD

}
=======
}

NodoP minValueNode(NodoP node)
{
    NodoP current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->esq != NULL)
        current = current->esq;
 
    return current;
}

NodoP deleteNodoP(NodoP root, char code[]){
    // STEP 1: PERFORM STANDARD BST DELETE
 
    if (root == NULL)
        return root;
 
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if ( strcmp(code,root->code)<0 )
        root->esq = deleteNodoP(root->esq, code);
 
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if( strcmp(code,root->code)>0 )
        root->dir = deleteNodoP(root->dir, code);
 
    // if key is same as root's key, then This is the node
    // to be deleted
    else
    {
        // node with only one child or no child
        if( (root->esq == NULL) || (root->dir == NULL) )
        {
            NodoP temp = root->esq ? root->esq : root->dir;
 
            // No child case
            if(temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
             *root = *temp; // Copy the contents of the non-empty child
 
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder successor (smallest
            // in the right subtree)
            NodoP temp = minValueNode(root->dir);
 
            // Copy the inorder successor's data to this node
            strcpy(root->code,temp->code);
 
            // Delete the inorder successor
            root->dir = deleteNodoP(root->dir, temp->code);
        }
    }
 
    // If the tree had only one node then return
    if (root == NULL)
      return root;
 
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->altura = maxP(alturaP(root->esq), alturaP(root->dir)) + 1;
 
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether
    //  this node became unbalanced)
    int balance = getBalanceP(root);
 
    // If this node becomes unbalanced, then there are 4 cases
 
    // Left Left Case
    if (balance > 1 && getBalanceP(root->esq) >= 0)
        return dirRotateP(root);
 
    // Left Right Case
    if (balance > 1 && getBalanceP(root->esq) < 0)
    {
        root->esq =  esqRotateP(root->esq);
        return dirRotateP(root);
    }
 
    // Right Right Case
    if (balance < -1 && getBalanceP(root->dir) <= 0)
        return esqRotateP(root);
 
    // Right Left Case
    if (balance < -1 && getBalanceP(root->dir) > 0)
    {
        root->dir = dirRotateP(root->dir);
        return esqRotateP(root);
    }
 
    return root;
}

NodoP removeP(NodoP p1, NodoP p2){
    if(p1!=NULL){
        if (p2!=NULL){
            p1=removeP(p1,p2->esq);
            p1=removeP(p1,p2->dir);
            p1=deleteNodoP(p1,p2->code);
        }
    }
    return p1;
}










>>>>>>> origin/master
