#include "headers/faturacao.h"


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


static char* my_strdup(const char *s);
static Info fat_procura_info(Faturacao fat, char *prod);
static int fat_compara_info(const void *avl_a, const void *avl_b, void *avl_param);
static void free_info(void* a);
static Info inicializa_info(char* prod);
static void freeinfo_avl(void *item, void *avl_param);
static Info codigo_to_info(char* prod);
static Info infoCopia(Info info);
static int comparaVendas(void *a, void *b, void *param);

/*A funcão my_strdup aloca uma string nova d com o comprimento + 1 da string passada por parametro s e copia-a para a string d*/
char *my_strdup (const char *s) {
    char *d = (char *)malloc (sizeof (char) *(strlen (s) + 1));   
    if (d == NULL) return NULL;          
    strcpy (d,s);                        
    return d;                            
}

/*A funcão inicializa_faturacao aloca uma estrutura Faturacao e cria uma avl para os produtos, bem como inicializa os 12 nodos totalvendas e totalfaurado a zero*/
Faturacao inicializa_faturacao() {
    int i;
    Faturacao res = (Faturacao) malloc(sizeof (struct faturacao));
    
    res->produtos = avl_create(fat_compara_info, NULL, NULL);
    
    for (i = 0; i < 12; i++){
        res->totalvendas[i] = 0;
        res->totalfaturado[i] = 0;
    }
    
    return res;
}


/*A funcão cont_regista_produto , dada a estrutura faturacão e um id de produto, insere-o através da funcão avl_insert*/
void cont_regista_produto(Faturacao fat, char *prod){
    Info nodo = inicializa_info(prod);
    avl_insert(fat->produtos, nodo);
}
/*A funcão cont_insere_venda, dada a estrutura faturacão, atualiza as vendas, quantidades e faturado conforme o produto em questão ser Promocão (P) ou Normal (N) */
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
    fat->totalvendas[mes-1]++;
    fat->totalfaturado[mes-1]+=q*preco;
}
/*A funcão cont_remove_produto remove um produto da Faturacao passados ambos por parametro. Inicialmente calcula o id do produto através da funcão fat_procura_info para depois eliminar o produto em questão através da funcão avl_delete e logo a seguir faz free ao nodo eliminado através da funcão free_info*/
void cont_remove_produto(Faturacao fat, char *produto){
    Info info = fat_procura_info(fat, produto);
    free_info((Info)avl_delete(fat->produtos, info)); //?
}
/*A funcão free_faturacao elimina todos os nodos da faturacao através da funcão avl_destroy e faz free à estrutura faturacao passada por parâmetro*/
void free_faturacao(Faturacao fat) {
    if(fat != NULL){
        avl_destroy(fat->produtos, freeinfo_avl);
        free(fat);
    }
}

/*A funcão getTotalFatNFilialX vai calcular o total faturado no modo Normal (N) de um dado produto, num determinado mes e em determinada filial */
float getTotalFatNFilialX (char* prod,int mes,Faturacao fat, int filial){
    float total=0;
    Info nodo=NULL;
    Info nodo_aux=codigo_to_info(prod);
    nodo=(Info)avl_find(fat->produtos,nodo_aux);
    if (nodo==NULL) return -1; 
    total+=nodo->faturadoN[mes-1][filial-1];
    return total;
}
/*A funcão getTotalFatPFilialX vai calcular o total faturado no modo Promocão (P) de um dado produto, num determinado mes e em determinada filial */
float getTotalFatPFilialX (char* prod,int mes,Faturacao fat, int filial){
    float total=0;
    Info nodo=NULL;
    Info nodo_aux=codigo_to_info(prod);
    nodo=(Info)avl_find(fat->produtos,nodo_aux);
    if (nodo==NULL) return -1; 
    total+=nodo->faturadoP[mes-1][filial-1];
    return total;
}
/*A funcão totalFatMeses calcula o total faturado num dado intervalo de meses*/
float totalFatMeses(Faturacao fat, int a, int b){
    int i;
    float f=0;
    if(fat!=NULL){
        for(i=a-1;i<b;i++){
            f+=fat->totalfaturado[i];
        }
    }
    return f;
}

/*A funcão totalVendasMeses calcula o total de vendas num determinado intervalo de meses*/
int totalVendasMeses(Faturacao fat, int a, int b){
    int i,v=0;
    if(fat!=NULL){
        for(i=a-1;i<b;i++){
            v+=fat->totalvendas[i];
        }
    }
    return v;
}
/*A funcão getQuantidadeFilial calcula a quantidade vendida de um determinado produto através do seu id de produto numa determinada filial em todos os meses */
int getQuantidadeFilial(Faturacao fat, char*prod, int filial){
    int total=0,i;
    Info nodo=NULL;
    Info nodo_aux=codigo_to_info(prod);
    nodo=(Info)avl_find(fat->produtos,nodo_aux);
    if (nodo==NULL) return -1; 
    for(i=0;i<12;i++) total+=nodo->quantidadeN[i][filial-1]+nodo->quantidadeP[i][filial-1];
    return total;
}
/*A funcão getQuantidadeNFilialX calcula a quantidade vendida em modo Normal (N) de um determinado produto num dado mês e filial*/
int getQuantidadeNFilialX (char* prod,int mes,Faturacao fat, int filial){
    int total=0;
    Info nodo=NULL;
    Info nodo_aux=codigo_to_info(prod);
    nodo=(Info)avl_find(fat->produtos,nodo_aux);
    if (nodo==NULL) return -1; 
    total=nodo->quantidadeN[mes-1][filial-1];
    return total;
}
/*A funcão getQuantidadePFilialX calcula a quantidade vendida em modo Promocão (P) de um determinado produto num dado mês e filial. Inicialmente vai buscar o nodo do produto atraves do id do produto e retorna finalmente a quantidade vendida*/
int getQuantidadePFilialX (char* prod,int mes,Faturacao fat, int filial){
    int total=0;
    Info nodo=NULL;
    Info nodo_aux=codigo_to_info(prod);
    nodo=(Info)avl_find(fat->produtos,nodo_aux);
    if (nodo==NULL) return -1; 
    total=nodo->quantidadeP[mes-1][filial-1];
    return total;
}
/*A funcão getVendasPFilialX calcula o nr de vendas em modo Promocao (P) de um produto num determinado mês e filial. Inicialmente vai buscar o produto através do seu id, se o encontrar devolve o nr de vendas nas condicões anteriores */
int getVendasPFilialX (char* prod,int mes,Faturacao fat, int filial){
    int total=0;
    Info nodo=NULL;
    Info nodo_aux=codigo_to_info(prod);
    nodo=(Info)avl_find(fat->produtos,nodo_aux);
    if (nodo==NULL) return -1; 
    total=nodo->vendasP[mes-1][filial-1];
    return total;
}
/*A funcão getVendasPFilialX calcula o nr de vendas em modo Normal (N) de um produto num determinado mês e filial. Inicialmente vai buscar o produto através do seu id, se o encontrar devolve o nr de vendas nas condicões anteriores */
int getVendasNFilialX (char* prod,int mes,Faturacao fat, int filial){
    int total=0;
    Info nodo=NULL;
    Info nodo_aux=codigo_to_info(prod);
    nodo=(Info)avl_find(fat->produtos,nodo_aux);
    if (nodo==NULL) return -1; 
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
        info=inicializa_info(res->code); /* copia o nodo da arvore*/
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
/*A funcão naoCompradosFilial percorre a estrutura da faturacao numa dada filial em todos os meses atraves do Traverser t, e verificia se este foi ou não comprado,se foi nada faz, se não insere-o num array a. No final faz free ao Traversser t e retorna o novo array*/
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
/*A funcão naoComprados percorre  percorre a estrutura da faturacao em todas as filiais e em todos os meses atraves do Traverser t, e verificia se este foi ou não comprado,se foi nada faz, se não insere-o num array a. No final faz free ao Traversser t e retorna o novo array*/
ARRAY naoCompradosFilial(Faturacao fat, int filial){
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


/*A funcão nMaisVendidos calcula os n produtos mais vendidos de todas as filiais através de um traversser t. Inicialza dois arrays a e b através da funcão inicializa_array . Copia os elementos do tipo Info para o array a, ordena-o através da funcão ordena e depois devolve o array b com os elementos ids dos produtos do array já ordenados */
ARRAY nMaisVendidos(Faturacao fat, int n){
    Info aux,copia;
    TRAVERSER t;
    char *produto;
    ARRAY a,b;
    int i;
    a=inicializa_array();
    b=inicializa_array();
    t=avl_t_alloc();
    avl_t_init(t,fat->produtos);
    while((aux=cat_info_proximo(t))!=NULL){
        copia= infoCopia(aux);
        insere_elemento(a,copia);
    }
    ordena(a,comparaVendas,NULL);
    for(i=0;i<n && i<get_tamanho(a);i++){
        aux=get_elemento(a,i);
        produto=my_strdup (aux->code);
        insere_elemento(b,produto);
    }
    deep_free(a,free_info);
    return b;
}


static int comparaVendas(void *a, void *b, void *param){
    Info a1=(Info)a;
    Info b1=(Info)b;
    int i,j,va=0,vb=0;
    for(i=0;i<12;i++){
        for(j=0;j<3;j++){
            va+=a1->quantidadeP[i][j]+a1->quantidadeN[i][j];
            vb+=b1->quantidadeP[i][j]+b1->quantidadeN[i][j];
        }
    }
    return va>vb?-1:1;
}

static Info codigo_to_info(char* prod) {
    Info info = (Info) malloc(sizeof (struct info));
    char *copia = (char*) malloc(sizeof (char)*(strlen(prod) + 1));
    strcpy(copia, prod);
    info->code = copia;
    return info;
}



static Info infoCopia(Info info){
    int i,j;
    Info novo=inicializa_info(info->code);
    for(i=0;i<12;i++){
        for(j=0;j<3;j++){
            novo->vendasP[i][j]=info->vendasP[i][j];
            novo->faturadoP[i][j]=info->faturadoP[i][j];
            novo->quantidadeP[i][j]=info->quantidadeP[i][j];
            novo->vendasN[i][j]=info->vendasN[i][j];
            novo->faturadoN[i][j]=info->faturadoN[i][j];
            novo->quantidadeN[i][j]=info->quantidadeN[i][j];
        }
    }
    return novo;
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

static void free_info(void* a) {
    Info prod=(Info)a;
    if(prod != NULL)
        free(prod->code);
    
    free(prod);
}

static void freeinfo_avl(void *item, void *avl_param) {
    Info prod = (Info) item;
    free(prod->code);
    free(prod);
}



