#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1000000
#define STACK_MAX 100



//o produto mais comprado, qual a quantidade que foi comprada desse mesmo produto?

//						   id produto Preço unids
// exemplo de linha de venda : KR1583 77.72 128 P L4891 2 1

int naoExiste (char *codigo, char *produtos [],int N){
int i;
for (i=0;i<N;i++)
	if (strcmp(codigo,produtos[i])==0)
		return 1;

return 0;
}



int main(){
FILE * ficheiro;
	int i,j=0,max=0;
	char *string = (char *) malloc(100);
	char *str = (char *) malloc(100);
	char *token = NULL;
	char limit[2] = " ";
	int *quantidadeProduto=(int *) malloc(sizeof(int)*MAX);
	char **codigoProduto=(char **) malloc (sizeof(char*)*MAX);
	char *compra[7];

	//colocar quantidades a zeros


	for (j=0;j<MAX;j++){
		quantidadeProduto[j]=0;
	}
	//ler do ficheiro vendas 
	j=0;
 	ficheiro = fopen("VendasValidas.txt", "r");
 	while ((string = fgets (str, 100, ficheiro)) != NULL) {
 			token = strtok(string, limit);
 			compra[0] = token;
 			printf("compra: %s\n",compra[0]);
 			//Adicionar IDs dos produtos ao array codigoProduto se este não existir

 				if (naoExiste (compra[0],codigoProduto,j)){
 					strcpy (codigoProduto[j],compra[0]);
 					j++;
 				}

	 			for(i=1; token != NULL && i < 7; i++) {
	 				token = strtok(NULL, " ");
	 				compra[i] = token;
	 			}
	 			
	 			// adicionar quandidade vendida
	 			for(j=0;j<MAX;j++){
	 				if (strcmp (codigoProduto[j],compra[0])==0)
	 					quantidadeProduto[j]++;
	 			}
	 			//determinar produto mais vendido
	 			for(i=0;i<j;i++)
	 				if (quantidadeProduto[i]>max){
	 					max=quantidadeProduto[i];
	 				}	
 	}
 	printf("Produto mais comprado:%s Quantidade comprada:%d\n",codigoProduto[max], max);
 	free(string);
 	free(str);
 	return 0;
 }