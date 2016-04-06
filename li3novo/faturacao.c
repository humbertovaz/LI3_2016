#include "headers/avl.h"
#include "headers/faturacao.h"


struct faturacao{
	int totalvendas[12];
	float totalfaturado[12];
	ARVORE produtos;
};


struct info{
	char *code;
	int vendasP[3][12];
	int vendasN[3][12];
	float faturadoN[3][12];
	float faturadoP[3][12];
	int quantidadeP[3][12];
	int quantidadeN[3][12];
};
static Info fat_procura_info(Faturacao fat, char *prod);
static int fat_compara_info(const void *avl_a, const void *avl_b, void *avl_param);
static void free_info(Info prod);
static Info inicializa_info(char* prod);
static void freeinfo_avl(void *item, void *avl_param);

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
    	prod->vendasN[filial-1][mes-1]++;
    	prod->quantidadeN[filial-1][mes-1]+=q;
    	prod->faturadoN[filial-1][mes-1]+=q*preco;
    }
    else {
    	prod->vendasP[filial-1][mes-1]++;
    	prod->quantidadeP[filial-1][mes-1]+=q;
    	prod->faturadoP[filial-1][mes-1]+=q*preco;
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
static Info inicializa_info(char* prod) {
    int i, j;
    Info info = (Info) malloc(sizeof (struct info));
    char *copia = (char*) malloc(sizeof (char)*(strlen(prod) + 1));
    strcpy(copia, prod);
    info->code = copia;
    
    for (i = 0; i < 3; i++)
        for (j = 0; j < 12; j++) {
            info->vendasN[i][j] = 0;
            info->vendasP[i][j] = 0;
            info->quantidadeN[i][j]=0;
            info->quantidadeP[i][j]=0;
            info->faturadoN[i][j]=0;
            info->faturadoP[i][j]=0;
        }
    return info;
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

