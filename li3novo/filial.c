#include "headers/avl.h"
#include "headers/filial.h"
#include <stdlib.h>
#include <string.h>


struct filial{
	ARVORE infoCliente;
};


struct icliente{
	char *cliente;
	int quantidadeT;
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
	int i;
	Icliente icliente = (Icliente) malloc(sizeof(struct icliente));
	char *copia = (char*) malloc(sizeof (char)*(strlen(cliente) + 1));
    strcpy(copia, cliente);
    icliente->cliente = copia;
    for(i=0;i<3;i++) icliente->filial[i]=0;
    icliente->infoprodutos=avl_create(fil_compara_prod,NULL,NULL);
	icliente->quantidadeT=0;
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

static Iprodutos fil_procura_prod(Icliente cliente, char* prod){
	Iprodutos aux = prodToIprodutos(prod);
	Iprodutos nodo = (Iprodutos)avl_find(cliente->infoprodutos,aux);
	free(aux->prod);
	free(aux);
	return nodo;
}






