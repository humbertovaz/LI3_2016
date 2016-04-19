#include "headers/avl.h"
#include "headers/filial.h"
#include <stdlib.h>
#include <string.h>
#include "headers/array.h"


struct filial{
	ARVORE infoCliente;
};


struct icliente{
	char *cliente;
	int quantidadeT[12];
	ARVORE infoprodutos[2];
};

struct iprodutos{
	char *prod;
	int quantidadeT;
	float gastouT;
	int quantidade[12];
	float gastou[12];
};

static Iprodutos inicializa_iprodutos(char *produto);
static Iprodutos prodToIprodutos(char *produto);
static Icliente clienteToIcliente(char *cliente);
static Icliente inicializa_icliente(char *cliente);
static int fil_compara_prod(const void* avl_a, const void* avl_b, void* avl_param);
static int fil_compara_cliente(const void* avl_a, const void* avl_b, void* avl_param);
static Icliente fil_procura_cliente(Filial fil, char *cliente);
static Iprodutos fil_procura_prod(Icliente cliente, char* prod, char p);
static Icliente cat_infocliente_proximo(TRAVERSER t);
static void free_InfoCliente(void *item, void *param);
static void free_infoProd(void *item, void *param);
static Iprodutos cat_infoproduto_proximo(TRAVERSER t);
static Iprodutos copiaIProdutos(Iprodutos iproduto);
static int comparaIprodutoQuantidade(void* a, void* b, void* param);
static void free_infoprod(void *item);
static ARVORE copiaAVLInfoProduto(ARVORE info);
static int comparaIprodutoGastou(void* a, void* b, void* param);
static int comparaString(void *a, void* b, void* param);
static char* my_strdup(const char *s);

char *my_strdup (const char *s) {
    char *d = malloc (strlen (s) + 1);   
    if (d == NULL) return NULL;          
    strcpy (d,s);                        
    return d;                            
}


Filial inicializa_filial() {
    Filial res = (Filial) malloc(sizeof (struct filial)); 
    res->infoCliente = avl_create(fil_compara_cliente, NULL, NULL);
    return res;
}


void fil_regista_cliente(Filial fil, char *cliente){
	Icliente icliente = inicializa_icliente(cliente);
	avl_insert(fil->infoCliente, icliente);
}

void fil_insere_prod(Filial fil, char *cliente, char *produto,int q, int mes, float preco, char p){
	Iprodutos prod;
        Icliente icliente=fil_procura_cliente(fil, cliente);
	icliente->quantidadeT[mes-1]+=q;
	 prod = fil_procura_prod(icliente,produto,p);
	if (prod){
		prod->quantidadeT+=q;
		prod->gastouT+=q*preco;
		prod->quantidade[mes-1]+=q;
		prod->gastou[mes-1]+=q*preco;
	}
	else{
		prod=inicializa_iprodutos(produto);
		prod->quantidadeT+=q;
		prod->gastouT+=q*preco;
		prod->quantidade[mes-1]+=q;
		prod->gastou[mes-1]+=q*preco;
		if (p=='P') avl_insert(icliente->infoprodutos[1],prod);
		else avl_insert(icliente->infoprodutos[0],prod);
	}
}

int getQuantidadeMesCliente(Filial fil, char *cliente, int mes){
	Icliente icliente=fil_procura_cliente(fil,cliente);
	return icliente->quantidadeT[mes-1];
}

static int fil_compara_cliente(const void* avl_a, const void* avl_b, void* avl_param){
	Icliente a = (Icliente) avl_a;
	Icliente b = (Icliente) avl_b;
	return strcmp(a->cliente,b->cliente);
}

static int fil_compara_prod(const void* avl_a, const void* avl_b, void* avl_param){
	Iprodutos a = (Iprodutos) avl_a;
	Iprodutos b = (Iprodutos) avl_b;
	return (strcmp(a->prod,b->prod)); 
}


static Icliente inicializa_icliente(char *cliente){
	int i,j;
	Icliente icliente = (Icliente) malloc(sizeof(struct icliente));
	char *copia = (char*) malloc(sizeof (char)*(strlen(cliente) + 1));
    strcpy(copia, cliente);
    icliente->cliente = copia;
    icliente->infoprodutos[0]=avl_create(fil_compara_prod,NULL,NULL);
    icliente->infoprodutos[1]=avl_create(fil_compara_prod,NULL,NULL);
	for(i=0;i<12;i++){
		icliente->quantidadeT[i]=0;
	}
	return icliente;
}


static Icliente clienteToIcliente(char *cliente){
	Icliente icliente = (Icliente) malloc(sizeof(struct icliente));
	char *copia = (char*) malloc(sizeof(char)*strlen(cliente)+1);
	strcpy(copia,cliente);
	icliente->cliente=copia;
	return icliente;
}



static Iprodutos prodToIprodutos(char *produto){
	Iprodutos iprodutos = (Iprodutos) malloc(sizeof(struct iprodutos));
	char *copia = (char*) malloc(sizeof(char)*strlen(produto)+1);
	strcpy(copia,produto);
	iprodutos->prod=copia;
	return iprodutos;
}

static Iprodutos inicializa_iprodutos(char *produto){
	int i,j;
	Iprodutos iprod = (Iprodutos) malloc(sizeof(struct iprodutos));
	char *copia=(char*)malloc(sizeof(char*)*strlen(produto)+1);
	strcpy(copia,produto);
	iprod->prod=copia;
	for(i=0;i<12;i++){
			iprod->quantidade[i]=0;
			iprod->gastou[i]=0;
	}
	iprod->quantidadeT=0;
	iprod->gastouT=0;
	return iprod;
}

static Icliente fil_procura_cliente(Filial fil, char *cliente){
	Icliente aux = clienteToIcliente(cliente);
	Icliente nodo = (Icliente)avl_find(fil->infoCliente,aux);
	free(aux->cliente);
	free(aux);
	return nodo;
}


static Icliente cat_infocliente_proximo(TRAVERSER t) {
    int i;
    Icliente cliente = NULL;
    Icliente res = avl_t_next(t);
    if (res != NULL) {
        cliente=inicializa_icliente(res->cliente);
    }
    return cliente;
}

static Iprodutos cat_infoproduto_proximo(TRAVERSER t){
	int i,j;
	Iprodutos produto=NULL;
	Iprodutos res=avl_t_next(t);
	if (res!=NULL){
		produto=inicializa_iprodutos(res->prod);
		for(i=0;i<12;i++){
			produto->quantidade[i]=res->quantidade[i];
			produto->gastou[i]=res->gastou[i];
		}
	}
	return produto;
}


ARRAY comprouTodasFiliais(Filial fil){
    char *cliente;
    Icliente aux;
    ARRAY a= inicializa_array();
    TRAVERSER t = avl_t_alloc();
    avl_t_init(t,fil->infoCliente);
    while((aux=cat_infocliente_proximo(t))!=NULL){
        if(aux->filial[0]+aux->filial[1]+aux->filial[2]==3){
            cliente=(char*)malloc(sizeof(char)*strlen(aux->cliente));
            strcpy(cliente,aux->cliente);
            insere_elemento(a,cliente);
        }
    }
    avl_t_free(t);
    return a;
}



ARRAY topMaisGastou(Filial fil, char *cliente){
	ARRAY a,b;
        TRAVERSER t;
        Iprodutos aux1,copia,aux2;
        ARVORE copiaAVL;
        Icliente nodo;
        Icliente aux;
	int i,j,g;
	char *prod;
	a=inicializa_array();
	b=inicializa_array();
        aux=inicializa_icliente(cliente);
	 nodo=avl_find(fil->infoCliente, aux);
	  copiaAVL=copiaAVLInfoProduto(nodo->infoprodutos[1]);
	 t= avl_t_alloc();
	avl_t_init(t,nodo->infoprodutos[0]);
	while((aux1=cat_infoproduto_proximo(t))!=NULL){
		g=0;
		aux2=avl_find(copiaAVL,aux1);
		for(i=0;i<12;i++){
			if(aux2!=NULL){
				g+=aux2->gastou[i][j]+aux1->gastou[i];
				avl_delete(copiaAVL,aux2);
			}
			else g+=aux1->gastou[i];
		}
		copia=copiaIProdutos(aux1);
		insere_elemento(a,copia);
	}
	avl_t_free(t);
	t=avl_t_alloc();
	avl_t_init(t,copiaAVL);
	while((aux1=cat_infoproduto_proximo(t))!=NULL){
		g=0;
		for(i=0;i<12;i++){
			g+=aux1->gastou[i];
		}
		copia=copiaIProdutos(aux1);
		insere_elemento(a,copia);
	}
	ordena(a,comparaIprodutoGastou,NULL);
	for(i=0;i<3;i++){
		aux1=get_elemento(a,i);
		prod=my_strdup(aux1->prod);
		insere_elemento(b,prod);
	}
	avl_t_free(t);
	deep_free(a,free_infoprod);
	return b;	
}

int comprouProdutoP(Filial fil, char* cliente, char* produto){
	int i,q=0;
        Icliente aux;
        Icliente nodo;
        Iprodutos auxp;
        Iprodutos nodop;
 
	 aux= inicializa_icliente(cliente);
	 nodo=avl_find(fil->infoCliente,aux);
	 auxp = inicializa_iprodutos(produto);
	nodop = avl_find(nodo->infoprodutos[1],auxp);
	if(nodop==NULL) return 0;
	else {
		for(i=0;i<12;i++) q+=nodop->quantidade[i];
		if(q>0) return 1;
	}
	return 0;
}


int comprouProdutoN(Filial fil, char* cliente, char* produto){
	int i,q=0;
	Icliente aux;
	Icliente nodo;
	Iprodutos auxp;
	Iprodutos nodop;

        aux= inicializa_icliente(cliente);
	nodo=avl_find(fil->infoCliente,aux);
	auxp = inicializa_iprodutos(produto);
	nodop = avl_find(nodo->infoprodutos[0],auxp);
	if(nodop==NULL) return 0;
	else {
		for(i=0;i<12;i++) q+=nodop->quantidade[i];
		if(q>0) return 1;
	}
	return 0;
	
}

int getNumClientesFilial(Filial fil, char* produto){
	int i,q,n=0;
       Iprodutos aux;
       Iprodutos nodop;
       Icliente nodo;
       TRAVERSER t;
	
	aux= inicializa_iprodutos(produto);
	t=avl_t_alloc();
	avl_t_init(t,fil->infoCliente);
	while((nodo=avl_t_next(t))!=NULL){
		q=0;
		nodop=avl_find(nodo->infoprodutos[0],aux);
		if(nodop!=NULL){
			for(i=0;i<12;i++)q+=nodop->quantidade[i];
			if(q>0){
				n++;
			}
		}
		else{
			nodop=avl_find(nodo->infoprodutos[1],aux);
			if(nodop!=NULL){
				for(i=0;i<12;i++)q+=nodop->quantidade[i];
				if(q>0){
					n++;
				}
			}
		}
	}
	avl_t_free(t);
	return n;	
}


ARRAY clientesCompraramProduto(Filial fil, char* produto){
	char *cliente;
	int i,q;
	Iprodutos aux;       
	Iprodutos nodop;
	Icliente nodo;
	TRAVERSER t;
	ARRAY a;
	
	aux= inicializa_iprodutos(produto);
	a=inicializa_array();
	t=avl_t_alloc();
	avl_t_init(t,fil->infoCliente);
	while((nodo=avl_t_next(t))!=NULL){
		q=0;
		nodop=avl_find(nodo->infoprodutos[0],aux);
		if(nodop!=NULL){
			for(i=0;i<12;i++)q+=nodop->quantidade[i];
			if(q>0){
				cliente=my_strdup(nodo->cliente);
				insere_elemento(a,cliente);
			}
		}
		else{
			nodop=avl_find(nodo->infoprodutos[1],aux);
			if(nodop!=NULL){
				for(i=0;i<12;i++)q+=nodop->quantidade[i];
				if(q>0){
					cliente=my_strdup(nodo->cliente);
					insere_elemento(a,cliente);
				}
			}
		}
	}
	avl_t_free(t);
	ordena(a,comparaString,NULL);
	return a;
}

ARRAY maisCompradosCliente(Filial fil, char* cliente, int mes){
	ARRAY a,b;
        Iprodutos aux1,copia,aux2;
        ARVORE copiaAVL;
        Icliente nodo;
        Icliente aux;
        TRAVERSER t;
	int i,q;
	char *prod;

	a=inicializa_array();
	b=inicializa_array();
        aux=inicializa_icliente(cliente);
        nodo=avl_find(fil->infoCliente, aux);
        copiaAVL=copiaAVLInfoProduto(nodo->infoprodutos[1]);
	 t= avl_t_alloc();
	avl_t_init(t,nodo->infoprodutos[0]);
	while((aux1=cat_infoproduto_proximo(t))!=NULL){
		q=0;
		aux2=avl_find(copiaAVL,aux1);
		if(aux2!=NULL){
			q+=aux2->quantidade[mes-1]+aux1->quantidade[mes-1];
			avl_delete(copiaAVL,aux2);
		}
		else q+=aux1->quantidade[mes-1];
		if(q>0){
			copia=copiaIProdutos(aux1);
			insere_elemento(a,copia);
		}
	}
	avl_t_free(t);
	t=avl_t_alloc();
	avl_t_init(t,copiaAVL);
	while((aux1=cat_infoproduto_proximo(t))!=NULL){
		q=0;
		q+=aux1->quantidade[mes-1];
		if(q>0){
			copia=copiaIProdutos(aux1);
			insere_elemento(a,copia);
		}
	}
	ordena(a,comparaIprodutoQuantidade,&mes);
	for(i=0;i<(get_tamanho(a));i++){
		aux1=get_elemento(a,i);
		prod=my_strdup(aux1->prod);
		insere_elemento(b,prod);
	}
	avl_t_free(t);
	deep_free(a,free_infoprod);
	return b;
}


static int comparaString(void *a, void* b, void* param){
	char *a1=(char*)a;
	char *b1=(char*)b;
	return strcmp(a1,b1);
}

static int comparaIprodutoQuantidade(void* a, void* b, void* param){
	Iprodutos a1= (Iprodutos) a;
	Iprodutos b1= (Iprodutos) b;
	int i,ta=0,tb=0,*m;
	m=(int*) (param);
	for(i=0;i<3;i++){
		ta+=a1->quantidade[(*m)-1][i];
		tb+=b1->quantidade[(*m)-1][i];
	}
	return ta>tb?-1:1;
}

static int comparaIprodutoGastou(void* a, void* b, void* param){
	Iprodutos a1= (Iprodutos) a;
	Iprodutos b1= (Iprodutos) b;
	int i,j,ga=0,gb=0;
	for(i=0;i<12;i++){
			ga+=a1->gastou[i];
			gb+=b1->gastou[i];
	}
	return ga>gb?-1:1;
}

static Iprodutos copiaIProdutos(Iprodutos iproduto){
	int i,j;
        Iprodutos novo;
	 novo = inicializa_iprodutos(iproduto->prod);
	for(i=0;i<12;i++){
		for(j=0;j<3;j++){
			novo->quantidade[i][j]=iproduto->quantidade[i][j];
			novo->gastou[i][j]=iproduto->gastou[i][j];
		}
		novo->quantidadeT=iproduto->quantidadeT;
		novo->gastouT=iproduto->gastouT;
	}
	return novo;
}

int naoComprou(Filial fil){
	int res=0;
         Icliente cliente;
	TRAVERSER t;
 
	 t = avl_t_alloc();
    avl_t_init(t,fil->infoCliente);
    while ((cliente=cat_infocliente_proximo(t))!=NULL){
    	if (cliente->filial[0]==0 && cliente->filial[1]==0 && cliente->filial[2]==0)
    		res++;
    }
	return res;
}




void free_filial(Filial fil){
	if(fil){
		avl_destroy(fil->infoCliente,free_InfoCliente);
		free(fil);
	}
}



static ARVORE copiaAVLInfoProduto( ARVORE info){
	Iprodutos aux, copia;
	TRAVERSER t;
	ARVORE novo;
 
	 novo=avl_create(fil_compara_prod,NULL,NULL);
	  t = avl_t_alloc();

	avl_t_init(t, info);
	while((aux=avl_t_next(t))!=NULL){
		copia=copiaIProdutos(aux);
		avl_insert(novo,copia);
	}
	avl_t_free(t);
	return novo;
}

static void free_InfoCliente(void *item, void *param){
	Icliente aux=(Icliente)item;
	free(aux->cliente);
	avl_destroy(aux->infoprodutos[0],free_infoProd);
	avl_destroy(aux->infoprodutos[1],free_infoProd);	
	free(aux);
}


static void free_infoprod(void *item){
	Iprodutos aux=(Iprodutos)item;
	free(aux->prod);
	free(aux);	
}

static void free_infoProd(void *item, void *param){
	Iprodutos aux=(Iprodutos)item;
	free(aux->prod);
	free(aux);
}


static Iprodutos fil_procura_prod(Icliente cliente, char* prod,char p){
    Iprodutos aux = prodToIprodutos(prod);
	Iprodutos nodo;
	if(p=='P') nodo = (Iprodutos)avl_find(cliente->infoprodutos[1],aux);
	else nodo = (Iprodutos)avl_find(cliente->infoprodutos[0],aux);
	free(aux->prod);
	free(aux);
	return nodo;
}






