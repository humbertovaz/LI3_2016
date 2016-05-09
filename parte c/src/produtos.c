#include "headers/produtos.h"


struct catalogo_produtos{
    ARVORE indices[27];
};

static int cat_compara_produtos(const void *avl_a, const void *avl_b, void *avl_param);
static void cat_free_produto(void *item, void *param);

/*A funcão inicializa_catalogo_produtos aloca memória para o respetivo catalogo de todos os produtos, 
e cria 27 AVLs para cada letra dos produtos através da funcão avl_create*/
CatProdutos inicializa_catalogo_produtos(){
    int i = 0;
    CatProdutos res = (CatProdutos) malloc(sizeof (struct catalogo_produtos));

    for (i = 0; i <= 26; i++) {
        res->indices[i] = avl_create(cat_compara_produtos, NULL, NULL);
    }

    return res;
}


/*A funcão insertP insere na estrutura catalogo de produtos o id do novo produto*/
void insertP(CatProdutos cat,char *str){
    int tamanho = strlen(str);
    char *new = (char *) malloc(tamanho + 1);
    strncpy(new, str, tamanho + 1);
    avl_insert(cat->indices[new[0]-'A'], new);  
}

/*A funcão cat_remove_produto elimina e faz free ao nodo do produto em questão (utilizando a funcao avl_delete) e de seguida faz o respetivo free */
void cat_remove_produto(CatProdutos cat, char *str) {
    free(avl_delete(cat->indices[str[0]-'A'], str));
}
/*A funcão free_catalogo_produtos destrói os dados do catalogo de produtos (cat) um a um (fazendo libavl_free) e no final liberta 
a memória do catálogo */
void free_catalogo_produtos(CatProdutos cat) {
    int i = 0;
    
    if(cat != NULL){
        for (i = 0; i <= 26; i++) {
            avl_destroy(cat->indices[i], cat_free_produto);
        }
        free(cat);
    }
}

/*A funcão cat_produto_proximo vai buscar o próximo nodo da estrutura associada ao traverser e se este existir, através da funcão avl_t_next vai buscar o id do proximo elemento e devolve uma cópia desse id */
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
/*A funcão listaProdutosLetra, dado uma letra e um catalogo em parâmetro, através de um traverser 
associada à estrutura avl dessa letra, vai inserindo num array a, todos os ids de produtos começados por essa letra. 
Fazendo o respetivo free do traverser*/
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




/*A funcão existeProduto verifica se existe um produto (através do seu id) num catálogo (ambos passados por parâmetro) se 
existe devolve 1 se não 0*/
int existeProduto (char *produto,CatProdutos cat) {
    if (avl_find(cat->indices[produto[0]-'A'], produto) != NULL) return 1;
    else return 0;
}
/*A funcão numeroProdutos faz a soma de todos os nodos de cada avl, uma a uma. Ou seja através de um ciclo for e
 da funcão avl_count iremos obter a soma total de produtos das 27 avl's */
int numeroProdutos(CatProdutos cat){
    int i,soma=0;
    for (i = 0; i <= 26; i++)
        soma += avl_count(cat->indices[i]);
    return soma;
}
/*A funcão numeroProdutosLetra com o auxilio da funcão avl_count, dado um catalogo e letra ambos passados por
 parâmetro, calcula o nr de nodos da avl associada a essa letra*/
int numeroProdutosLetra(CatProdutos cat, char letra) {
    return avl_count(cat->indices[letra-'A']);
}


static int cat_compara_produtos(const void *avl_a, const void *avl_b, void *avl_param) {
    return strcmp((char *) avl_a, (char *) avl_b);
}

static void cat_free_produto(void *item, void *param) {
    free(item);
}






