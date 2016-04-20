#include "headers/filial.h"



struct filial{
	ARVORE infoCliente;
};


struct icliente{
	char *cliente;
	int quantidade[12];
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
static void free_InfoCliente(void *item, void *param);
static void free_infoProd(void *item, void *param);
static Iprodutos copiaIProdutos(Iprodutos iproduto);
static int comparaIprodutoQuantidade(void* a, void* b, void* param);
static void free_infoprod(void *item);
static int comparaIprodutoGastou(void* a, void* b, void* param);
static int comparaString(void *a, void* b, void* param);
static char* my_strdup(const char *s);
static int comparaIproduto(void *a, void* b, void *param);

char *my_strdup (const char *s) {
    char *d = (char *)malloc (sizeof (char) *(strlen (s) + 1));   
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
	icliente->quantidade[mes-1]+=q;
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
	return icliente->quantidade[mes-1];
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
    icliente->infoprodutos[0]=avl_create(fil_compara_prod,NULL,NULL);
    icliente->infoprodutos[1]=avl_create(fil_compara_prod,NULL,NULL);
	for(i=0;i<12;i++){
		icliente->quantidade[i]=0;
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
	int i;
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





void clientesCompraram(Filial fil,ARRAY a){
    int i,q,pos;
    Icliente aux;
    TRAVERSER t = avl_t_alloc();
    avl_t_init(t,fil->infoCliente);
    while((aux=avl_t_next(t))!=NULL){
    	q=0;
    	for(i=0;i<12;i++) q+=aux->quantidade[i];
        if(q==0){
        	pos=binarysearch(a,aux->cliente,comparaString,NULL);
        	remove_posicao(a,pos);
        }
    }
    avl_t_free(t);
}



ARRAY topMaisGastou(ARRAY a){
	int i;
	ARRAY b;
	Iprodutos aux;
	char *str;
	b=inicializa_array();
	ordena(a,comparaIprodutoGastou,NULL);
	for(i=0;i<3;i++){
		aux=get_elemento(a,i);
		str=my_strdup(aux->prod);
		insere_elemento(b,str);
	}
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

ARRAY extraiPorQuantidade(ARRAY a, int mes){
	ARRAY b;
	int i;
	Iprodutos aux;
	char *str;
	b=inicializa_array();
	ordena(a,comparaIprodutoQuantidade,&mes);
	for(i=0;i<get_tamanho(a);i++){
		aux=get_elemento(a,i);
		str=my_strdup(aux->prod);
		insere_elemento(b,str);
	}
	deep_free(a,free_infoprod);
	return b;
}

void getIProdMes(Filial fil, char* cliente, int mes, ARRAY a){
	Icliente nodo,aux;
	TRAVERSER t;
	int i;
	Iprodutos nodop,copia,elem;
	aux=inicializa_icliente(cliente);
	t=avl_t_alloc();
	nodo=(Icliente)avl_find(fil->infoCliente,aux);
	avl_t_init(t,nodo->infoprodutos[0]);
	while((nodop=avl_t_next(t))!=NULL){
		copia=copiaIProdutos(nodop);
		i=get_posicao(a,copia,comparaIproduto,NULL);
		if(i==-1){
			insere_elemento(a,copia);
		}
		else{
			elem=get_elemento(a,i);
			elem->quantidade[mes-1]+=copia->quantidade[mes-1];
			free_infoprod(copia);
		}
	}
	avl_t_free(t);
	t=avl_t_alloc();
	avl_t_init(t,nodo->infoprodutos[1]);
	while((nodop=avl_t_next(t))!=NULL){
		copia=copiaIProdutos(nodop);
		i=get_posicao(a,copia,comparaIproduto,NULL);
		if(i==-1){
			insere_elemento(a,copia);
		}
		else{
			elem=get_elemento(a,i);
			elem->quantidade[mes-1]+=copia->quantidade[mes-1];
			free_infoprod(copia);
		}
	}
}


static int comparaString(void *a, void* b, void* param){
	char *a1=(char*)a;
	char *b1=(char*)b;
	return strcmp(a1,b1);
}


static int comparaIproduto(void *a, void* b, void *param){
	Iprodutos a1,b1;
	a1=(Iprodutos)a;
	b1=(Iprodutos)b;
	return strcmp(a1->prod,b1->prod);
}

static int comparaIprodutoQuantidade(void* a, void* b, void* param){
	Iprodutos a1= (Iprodutos) a;
	Iprodutos b1= (Iprodutos) b;
	int ta=0,tb=0,*m;
	m=(int*) (param);
	ta+=a1->quantidade[(*m)-1];
	tb+=b1->quantidade[(*m)-1];
	return ta>tb?-1:1;
}

static int comparaIprodutoGastou(void* a, void* b, void* param){
	Iprodutos a1= (Iprodutos) a;
	Iprodutos b1= (Iprodutos) b;
	int i,ga=0,gb=0;
	for(i=0;i<12;i++){
		ga+=a1->gastou[i];
		gb+=b1->gastou[i];
	}
	return ga>gb?-1:1;
}

static Iprodutos copiaIProdutos(Iprodutos iproduto){
	int i;
    Iprodutos novo;
	novo = inicializa_iprodutos(iproduto->prod);
	for(i=0;i<12;i++){
		novo->quantidade[i]=iproduto->quantidade[i];
		novo->gastou[i]=iproduto->gastou[i];
	}
	novo->quantidadeT=iproduto->quantidadeT;
	novo->gastouT=iproduto->gastouT;
	return novo;
}


void removeCompraram(Filial fil, ARRAY a){
	int i,tamanho;
	Icliente cliente, nodo;
	tamanho=get_tamanho(a);
	for(i=0;i<tamanho;i++){
		cliente=inicializa_icliente(get_elemento(a,i));
		nodo=avl_find(fil->infoCliente,cliente);
		if(nodo->infoprodutos[0] || nodo->infoprodutos[1]){
			remove_posicao(a,i);
			tamanho--;
		}
	}
}


ARRAY naoCompraram(Filial fil){
	char *str;
	ARRAY a;
    Icliente cliente;
	TRAVERSER t;
	a=inicializa_array();
	t = avl_t_alloc();
    avl_t_init(t,fil->infoCliente);
    while ((cliente=avl_t_next(t))!=NULL){
    	if (cliente->infoprodutos[0]==NULL && cliente->infoprodutos[1]==NULL){
    		str=my_strdup(cliente->cliente);
    		insere_elemento(a,str);
    	}
    }
	return a;
}

ARRAY compraram(Filial fil){
	int i,q;
	ARRAY a;
	char *cliente;
	Icliente nodo;
	TRAVERSER t;
	t=avl_t_alloc();
	avl_t_init(t,fil->infoCliente);
	a=inicializa_array();
	while((nodo=avl_t_next(t))!=NULL){
		q=0;
		for(i=0;i<12;i++){
			q+=nodo->quantidade[i];
		}
		if(q>0){
			cliente=my_strdup(nodo->cliente);
			insere_elemento(a,cliente);
		}
	}
	return a;
}

void removeNaoCompraram(Filial fil, ARRAY a){
	int i,j,q,tamanho;
	Icliente cliente,nodo;
	tamanho=get_tamanho(a);
	for(i=0;i<tamanho;i++){
		cliente=inicializa_icliente(get_elemento(a,i));
		nodo=avl_find(fil->infoCliente,cliente);
		q=0;
		for(j=0;j<12;j++){
			q+=nodo->quantidade[j];
		}
		if(q==0){
			remove_posicao(a,i);
			tamanho--;
		}
	}
}


void free_filial(Filial fil){
	if(fil){
		avl_destroy(fil->infoCliente,free_InfoCliente);
		free(fil);
	}
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






