#include "headers/produtos.h"


struct catalogo_produtos{
    ARVORE indices[27];
};

static int cat_compara_produtos(const void *avl_a, const void *avl_b, void *avl_param);
static void cat_free_produto(void *item, void *param);

CatProdutos inicializa_catalogo_produtos(){
    int i = 0;
    CatProdutos res = (CatProdutos) malloc(sizeof (struct catalogo_produtos));

    for (i = 0; i <= 26; i++) {
        res->indices[i] = avl_create(cat_compara_produtos, NULL, NULL);
    }

    return res;
}



void insertP(CatProdutos cat,char *str){
    int tamanho = strlen(str);
    char *new = (char *) malloc(tamanho + 1);
    strncpy(new, str, tamanho + 1);
    avl_insert(cat->indices[new[0]-'A'], new);  
}


void cat_remove_produto(CatProdutos cat, char *str) {
    free(avl_delete(cat->indices[str[0]-'A'], str));
}

void free_catalogo_produtos(CatProdutos cat) {
    int i = 0;
    
    if(cat != NULL){
        for (i = 0; i <= 26; i++) {
            avl_destroy(cat->indices[i], cat_free_produto);
        }
        free(cat);
    }
}


char *cat_produto_proximo(TRAVERSER t) {
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

ARRAY listaProdutosLetra(CatProdutos cat, char l){
    char *produto;
    ARRAY a= inicializa_array();
    TRAVERSER t = avl_t_alloc();
    avl_t_init(t,cat->indices[l-'A']);
    while((produto=cat_produto_proximo(t))!=NULL){
        insere_elemento(a,produto);
    }
    avl_t_free(t);
    return a;
}





int existeProduto (char *produto,CatProdutos cat) {
    if (avl_find(cat->indices[produto[0]-'A'], produto) != NULL) return 1;
    else return 0;
}

int numeroProdutos(CatProdutos cat){
    int i,soma=0;
    for (i = 0; i <= 26; i++)
        soma += avl_count(cat->indices[i]);
    return soma;
}

int numeroProdutosLetra(CatProdutos cat, char letra) {
    return avl_count(cat->indices[letra-'A']);
}


static int cat_compara_produtos(const void *avl_a, const void *avl_b, void *avl_param) {
    return strcmp((char *) avl_a, (char *) avl_b);
}

static void cat_free_produto(void *item, void *param) {
    free(item);
}






