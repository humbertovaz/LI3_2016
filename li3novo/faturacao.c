#include "headers/avl.h"
#include "headers/faturacao.h"
#include "headers/array.h"
#include <stdio.h>


struct faturacao{
	int totalvendas[12];
	float totalfaturado[12];
	ARVORE produtos;
};


struct info{
	char *code;
	int vendasP[12][3];
	int vendasN[12][3];
	float faturadoN[12][3];
	float faturadoP[12][3];
	int quantidadeP[12][3];
	int quantidadeN[12][3];
};



static Info fat_procura_info(Faturacao fat, char *prod);
static int fat_compara_info(const void *avl_a, const void *avl_b, void *avl_param);
static void free_info(Info prod);
static Info inicializa_info(char* prod);
static void freeinfo_avl(void *item, void *avl_param);
static Info codigo_to_info(char* prod);static Info *cat_produto_proximo(TRAVERSER t);

Faturacao inicializa_faturacao() {
    int i, j;
    Faturacao res = (Faturacao) malloc(sizeof (struct faturacao));
    
    res->produtos = avl_create(fat_compara_info, NULL, NULL);
    
    for (i = 0; i < 12; i++){
        res->totalvendas[i] = 0;
        res->totalfaturado[i] = 0;
    }
    
    return res;
}



void cont_regista_produto(Faturacao fat, char *prod){
    Info nodo = inicializa_info(prod);
    avl_insert(fat->produtos, nodo);
}

void cont_insere_venda(Faturacao fat, char *produto, int q, float preco, char M,int mes, int filial) {
    Info prod;
    prod=fat_procura_info(fat, produto);    
    if(M == 'N'){
    	prod->vendasN[mes-1][filial-1]++;
    	prod->quantidadeN[mes-1][filial-1]+=q;
    	prod->faturadoN[mes-1][filial-1]+=q*preco;
    }
    else {
    	prod->vendasP[mes-1][filial-1]++;
    	prod->quantidadeP[mes-1][filial-1]+=q;
    	prod->faturadoP[mes-1][filial-1]+=q*preco;
    }
}

void cont_remove_produto(Faturacao fat, char *produto){
    Info info = fat_procura_info(fat, produto);
    free_info((Info)avl_delete(fat->produtos, info));
}

void free_faturacao(Faturacao fat) {
    if(fat != NULL)
        avl_destroy(fat->produtos, freeinfo_avl);
    free(fat);
}


float getTotalFatNFilialX (char* prod,int mes,Faturacao fat, int filial){
    float total=0;
    Info nodo=NULL;
    Info nodo_aux=codigo_to_info(prod);
    nodo=(Info)avl_find(fat->produtos,nodo_aux);
    if (nodo==NULL) return -1; // se o produto nao existe
    total+=nodo->faturadoN[mes-1][filial-1];
    return total;
}

float getTotalFatPFilialX (char* prod,int mes,Faturacao fat, int filial){
    float total=0;
    Info nodo=NULL;
    Info nodo_aux=codigo_to_info(prod);
    nodo=(Info)avl_find(fat->produtos,nodo_aux);
    if (nodo==NULL) return -1; // se o produto nao existe
    total+=nodo->faturadoP[mes-1][filial-1];
    return total;
}

int getQuantidadeNFilialX (char* prod,int mes,Faturacao fat, int filial){
    int total=0;
    Info nodo=NULL;
    Info nodo_aux=codigo_to_info(prod);
    nodo=(Info)avl_find(fat->produtos,nodo_aux);
    if (nodo==NULL) return -1; // se o produto nao existe
    total=nodo->quantidadeN[mes-1][filial-1];
    return total;
}
int getQuantidadePFilialX (char* prod,int mes,Faturacao fat, int filial){
    int total=0;
    Info nodo=NULL;
    Info nodo_aux=codigo_to_info(prod);
    nodo=(Info)avl_find(fat->produtos,nodo_aux);
    if (nodo==NULL) return -1; // se o produto nao existe
    total=nodo->quantidadeP[mes-1][filial-1];
    return total;
}

int getVendasPFilialX (char* prod,int mes,Faturacao fat, int filial){
    int total=0;
    Info nodo=NULL;
    Info nodo_aux=codigo_to_info(prod);
    nodo=(Info)avl_find(fat->produtos,nodo_aux);
    if (nodo==NULL) return -1; // se o produto nao existe
    total=nodo->vendasP[mes-1][filial-1];
    return total;
}
int getVendasNFilialX (char* prod,int mes,Faturacao fat, int filial){
    int total=0;
    Info nodo=NULL;
    Info nodo_aux=codigo_to_info(prod);
    nodo=(Info)avl_find(fat->produtos,nodo_aux);
    if (nodo==NULL) return -1; // se o produto nao existe
    total=nodo->vendasN[mes-1][filial-1];
    return total;
}





static Info inicializa_info(char* prod) {
    int i, j;
    Info info = (Info) malloc(sizeof (struct info));
    char *copia = (char*) malloc(sizeof (char)*(strlen(prod) + 1));
    strcpy(copia, prod);
    info->code = copia;
    
    for (i = 0; i < 12; i++)
        for (j = 0; j < 3; j++) {
            info->vendasN[i][j] = 0;
            info->vendasP[i][j] = 0;
            info->quantidadeN[i][j]=0;
            info->quantidadeP[i][j]=0;
            info->faturadoN[i][j]=0;
            info->faturadoP[i][j]=0;
        }
    return info;
}


static Info cat_info_proximo(TRAVERSER t) {
    int i,j;
    Info info = NULL;
    Info res = avl_t_next(t);
    if (res != NULL) {
        info=inicializa_info(res->code);
        for(i=0;i<12;i++){
            for(j=0;j<3;j++){
                info->vendasN[i][j] = res->vendasN[i][j];
                info->vendasP[i][j] = res->vendasP[i][j];
                info->quantidadeN[i][j]=res->quantidadeN[i][j];
                info->quantidadeP[i][j]=res->quantidadeP[i][j];
                info->faturadoN[i][j]=res->faturadoN[i][j];
                info->faturadoP[i][j]=res->faturadoP[i][j]; 
            }
        }
    }
    return info;
}

ARRAY naoCompradosFilial(Faturacao fat, int filial){
    char *produto;
    int i,q=0;
    Info aux;
    ARRAY a= inicializa_array();
    TRAVERSER t = avl_t_alloc();
    avl_t_init(t,fat->produtos);
    while((aux=cat_info_proximo(t))!=NULL){
        for(i=0;i<12;i++) q+=aux->vendasP[i][filial-1]+aux->vendasN[i][filial-1];
        if(q==0){
            produto=(char*)malloc(sizeof(char)*strlen(aux->code));
            strcpy(produto,aux->code);
            insere_elemento(a,produto);
        }
        q=0;
    }
    avl_t_free(t);
    return a;
}

ARRAY naoComprados(Faturacao fat){
    char *produto;
    int i,j,q=0;
    Info aux;
    ARRAY a= inicializa_array();
    TRAVERSER t = avl_t_alloc();
    avl_t_init(t,fat->produtos);
    while((aux=cat_info_proximo(t))!=NULL){
        for(i=0;i<12;i++) 
            for(j=0;j<3;j++){
                q+=(aux->vendasP[i][j])+(aux->vendasN[i][j]);
            }
        if(q==0){
            produto=(char*)malloc(sizeof(char)*strlen(aux->code));
            strcpy(produto,aux->code);
            insere_elemento(a,produto);
        }
        q=0;
    }
    avl_t_free(t);
    return a;
}


static Info codigo_to_info(char* prod) {
    Info info = (Info) malloc(sizeof (struct info));
    char *copia = (char*) malloc(sizeof (char)*(strlen(prod) + 1));
    strcpy(copia, prod);
    info->code = copia;
    return info;
}

static Info fat_procura_info(Faturacao fat, char *prod){
    Info nodo_aux = codigo_to_info(prod);
    Info res = (Info) avl_find(fat->produtos, nodo_aux);
    free(nodo_aux->code);
    free(nodo_aux);
    return res;
}

static int fat_compara_info(const void *avl_a, const void *avl_b, void *avl_param){
    Info a = (Info) avl_a;
    Info b = (Info) avl_b;
    return strcmp(a->code, b->code);
}

static void free_info(Info prod) {
    if(prod != NULL)
        free(prod->code);
    
    free(prod);
}

static void freeinfo_avl(void *item, void *avl_param) {
    Info prod = (Info) item;
    free(prod->code);
    free(prod);
}



