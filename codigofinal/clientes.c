#include "headers/avl.h"
#include "headers/clientes.h"
#include "headers/array.h"
#include <stdio.h>


struct catalogo_clientes{
    ARVORE indices[27];
};

static int cat_compara_Clientes(const void *avl_a, const void *avl_b, void *avl_param);
static void cat_free_cliente(void *item, void *param);
static char *cliente_proximo(TRAVERSER t);

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
    printf("fim alloc\n");
    avl_t_init(t,(cat->indices[indice]));
    printf("fim init\n");
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
        printf("cliclo %d\n",i );
        listaClientesI(cat,i,a);
        printf("fim\n");
    }
    return a;
}




void insertC(CatClientes cat,char *str){
    int tamanho = strlen(str);
    char *new = (char *) malloc(tamanho + 1);
    strncpy(new, str, tamanho + 1);
    avl_insert(cat->indices[new[0]-'A'], new);  
}


void cat_remove_cliente(CatClientes cat, char *str) {
    free(avl_delete(cat->indices[str[0]-'A'], str));
}

void free_catalogo_Clientes(CatClientes cat) {
    int i = 0;
    
    if(cat != NULL){
        for (i = 0; i <= 26; i++) {
            avl_destroy(cat->indices[i], cat_free_cliente);
        }
        free(cat);
    }
}




int existeCliente (char *cliente,CatClientes cat) {
    if (avl_find(cat->indices[cliente[0]-'A'], cliente) != NULL) return 1;
    else return 0;
}

int numeroClientes(CatClientes cat){
    int i,soma=0;
    for (i = 0; i <= 26; i++)
        soma += avl_count(cat->indices[i]);
    return soma;
}

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





