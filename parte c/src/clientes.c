
#include "headers/clientes.h"




struct catalogo_clientes{
    ARVORE indices[27];
};

/*funcao privada ao modulo de comparacao entre dois apontadores*/
static int cat_compara_Clientes(const void *avl_a, const void *avl_b, void *avl_param);
/* funcao privada ao modulo de fazer free*/
static void cat_free_cliente(void *item, void *param);
/*funcao privada ao modulo que recorrendo a um traverser extrai o codigo cliente do nodo atual*/
static char *cliente_proximo(TRAVERSER t);


/*A funcao inicializa_catalogo_clientes inicializa o modulo (array de 27 posicoes de avls), pondo estes 27 indices a null*/
CatClientes inicializa_catalogo_clientes(){
    int i = 0;
    CatClientes res = (CatClientes) malloc(sizeof (struct catalogo_clientes));

    for (i = 0; i <= 26; i++) {
        res->indices[i] = avl_create(cat_compara_Clientes, NULL, NULL);
    }

    return res;
}

void listaClientesI(CatClientes cat, int indice, ARRAY a){
    char *cliente;
    TRAVERSER t = avl_t_alloc();
    avl_t_init(t,(cat->indices[indice]));
   while((cliente=cliente_proximo(t))!=NULL){
        insere_elemento(a,cliente);
    }
    avl_t_free(t);
}

ARRAY extraiClientes(CatClientes cat){
    int i;
    ARRAY a;
    a=inicializa_array();
    for(i=0;i<27;i++){
    listaClientesI(cat,i,a);
  
    }
    return a;
}


/*a funcao insertC insere um cliente na sua avl respectiva, isto é, a posicao do array a que corresponde a letra inicial*/

void insertC(CatClientes cat,char *str){
    int tamanho = strlen(str);
    char *new = (char *) malloc(tamanho + 1);
    strncpy(new, str, tamanho + 1);
    avl_insert(cat->indices[new[0]-'A'], new);  
}

/*a funcao cat_remove_cliente remove da respectiva avl o codigo de cliente passado por argumento, fazendo free ao nodo onde este situava.*/
void cat_remove_cliente(CatClientes cat, char *str) {
    free(avl_delete(cat->indices[str[0]-'A'], str));
}


/*a funcao free_catalo_Cliente apaga as 27 avls, fazendo o respectivo free.*/
void free_catalogo_Clientes(CatClientes cat) {
    int i = 0;
    
    if(cat != NULL){
        for (i = 0; i <= 26; i++) {
            avl_destroy(cat->indices[i], cat_free_cliente);
        }
        free(cat);
    }
}



/* A funcao existeCliente verifica se um codigo existe na respectiva avl*/
int existeCliente (char *cliente,CatClientes cat) {
    if (avl_find(cat->indices[cliente[0]-'A'], cliente) != NULL) return 1;
    else return 0;
}
/*a funcao numeroClientes conta quantos clientes existem nas avls, usando para isto a funcao generica do modulo avl, avl_count*/
int numeroClientes(CatClientes cat){
    int i,soma=0;
    for (i = 0; i <= 26; i++)
        soma += avl_count(cat->indices[i]);
    return soma;
}
/*a funcao numeroClientesLetra conta quantos clientes existem comecados por uma determinada letra, para isto so e contado os nodos da avl a que corresponde a posicao dessa letra*/
int numeroClientesLetra(CatClientes cat, char letra) {
    return avl_count(cat->indices[letra-'A']);
}

static char *cliente_proximo(TRAVERSER t) {
    int tamanho;
    char *ret = NULL;
    char *res = avl_t_next(t);
    if (res != NULL) {
        tamanho = strlen(res) + 1;
        ret = (char *) malloc(sizeof (char)*tamanho);
        strncpy(ret, res, tamanho);
    }
    return ret;
}

static int cat_compara_Clientes(const void *avl_a, const void *avl_b, void *avl_param) {
    return strcmp((char *) avl_a, (char *) avl_b);
}

static void cat_free_cliente(void *item, void *param) {
    free(item);
}





