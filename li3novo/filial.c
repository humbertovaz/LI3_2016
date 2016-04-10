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
	int quantidadeT[12][3];
	int filial[3];
	ARVORE infoprodutos;
};

struct iprodutos{
	char *prod;
	int quantidadeT;
	float gastouT;
	int quantidade[12][3];
	float gastou[12][3];
};

static Iprodutos inicializa_iprodutos(char *produto);
static Iprodutos prodToIprodutos(char *produto);
static Icliente clienteToIcliente(char *cliente);
static Icliente inicializa_icliente(char *cliente);
static int fil_compara_prod(const void* avl_a, const void* avl_b, void* avl_param);
static int fil_compara_cliente(const void* avl_a, const void* avl_b, void* avl_param);
static Icliente fil_procura_cliente(Filial fil, char *cliente);
static Iprodutos fil_procura_prod(Icliente cliente, char* prod);
static Icliente cat_infocliente_proximo(TRAVERSER t);
static void free_InfoCliente(void *item, void *param);
static void free_infoProd(void *item, void *param);
static Iprodutos fil_procura_prod(Icliente cliente, char* prod);


Filial inicializa_filial() {
    Filial res = (Filial) malloc(sizeof (struct filial)); 
    res->infoCliente = avl_create(fil_compara_cliente, NULL, NULL);
    return res;
}


void fil_regista_cliente(Filial fil, char *cliente){
	Icliente icliente = inicializa_icliente(cliente);
	avl_insert(fil->infoCliente, icliente);
}

void fil_insere_prod(Filial fil, char *cliente, char *produto,int q, int filial, int mes, float preco){
	Icliente icliente=fil_procura_cliente(fil, cliente);
	icliente->quantidadeT[mes-1][filial-1]+=q;
	icliente->filial[filial-1]=1;
	Iprodutos prod = fil_procura_prod(icliente,produto);
	if (prod){
		prod->quantidadeT+=q;
		prod->gastouT+=q*preco;
		prod->quantidade[mes-1][filial-1]+=q;
		prod->gastou[mes-1][filial-1]+=q*preco;
	}
	else{
		prod=inicializa_iprodutos(produto);
		prod->quantidadeT+=q;
		prod->gastouT+=q*preco;
		prod->quantidade[mes-1][filial-1]+=q;
		prod->gastou[mes-1][filial-1]+=q*preco;
		avl_insert(icliente->infoprodutos,prod);
	}
}

int getQuantidadeMesCliente(Filial fil, char *cliente, int filial, int mes){
	Icliente icliente=fil_procura_cliente(fil,cliente);
	return icliente->quantidadeT[mes-1][filial-1];
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
    for(i=0;i<3;i++) icliente->filial[i]=0;
    icliente->infoprodutos=avl_create(fil_compara_prod,NULL,NULL);
	for(i=0;i<12;i++){
		for(j=0;j<3;j++){
			icliente->quantidadeT[i][j]=0;
		}
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
		for(j=0;j<3;j++){
			iprod->quantidade[i][j]=0;
			iprod->gastou[i][j]=0;
		}
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
        for(i=0;i<3;i++){
        	cliente->filial[i]=res->filial[i];
        }
    }
    return cliente;
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


void free_filial(Filial fil){
	avl_destroy(fil->infoCliente,free_InfoCliente);
	free(fil);
}

static void free_InfoCliente(void *item, void *param){
	Icliente aux=(Icliente)item;
	free(aux->cliente);
	avl_destroy(aux->infoprodutos,free_infoProd);
	free(aux);
}


static void free_infoProd(void *item, void *param){
	Iprodutos aux=(Iprodutos)item;
	free(aux->prod);
	free(aux);
}


static Iprodutos fil_procura_prod(Icliente cliente, char* prod){
	Iprodutos aux = prodToIprodutos(prod);
	Iprodutos nodo = (Iprodutos)avl_find(cliente->infoprodutos,aux);
	free(aux->prod);
	free(aux);
	return nodo;
}






