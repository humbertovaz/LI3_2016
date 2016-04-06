#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers/clientes.h"
#include "headers/produtos.h"






static CatClientes clientes;
static CatProdutos produtos;
  





int leitura (char * nome_fich) {
	FILE * ficheiro;
	
	char *string = (char *) malloc(100);
	char *str = (char *) malloc(100);
	char *token = NULL;
	char limit[2] = " ";
	char modo;

	int linhas = 0;
	int linhas_val = 0;
	
        int filial;

	ficheiro = fopen(nome_fich, "r");
	

	
	if (strcmp(nome_fich, "Clientes.txt") == 0){
		while ((string = fgets (str, 100, ficheiro)) != NULL) {
			linhas++;	
			token = strtok(string, limit);
			token[5] = '\0';
			insertC(clientes, token);
                        
		}
		printf("Ficheiro lido: %s\nNúmero de linhas lidas: %d\n", nome_fich, linhas);
         fclose(ficheiro);
         free(string);
         free(str);

}

          else if (strcmp(nome_fich, "Produtos.txt") == 0){
		while ((string = fgets (str, 100, ficheiro)) != NULL) {
			linhas++;
			token = strtok(string, limit);
			token[6] = '\0';
			insertP(produtos, token);
		        
		}
		printf("Ficheiro lido: %s\nNúmero de linhas lidas: %d\n", nome_fich, linhas);	
 fclose(ficheiro);
 free(string);
 free(str);


}
   
  else if (strcmp(nome_fich,"Vendas_1M.txt") == 0){
		int i = 0;
		int nr;
		int mes;
		double preco;
		char  *compra[7];
        char *cliente;
        char *produto;
        char * tmpString= (char *) malloc(100);
		while ((string = fgets (str, 100, ficheiro)) != NULL) {
			linhas++;
			strcpy(tmpString,string);
			token = strtok(string, limit);
			compra[0] = token;
			for(i=1; token != NULL && i < 7; i++) {
				token = strtok(NULL, " ");
				compra[i] = token;
                              
			}
			
			/* compra[4] -> cliente
			 * compra[0] -> produto
			 */
			preco = strtod(compra[1], &compra[1]);
                        nr = atoi(compra[2]);
			mes = atoi(compra[5]);
			modo = compra[3][0];  //por causa do /0;
			filial=atoi(compra[6]);
                         cliente=compra[4]; 
                         produto=compra[0];

			if ((preco>=0.0 && preco <= 999.99) && (filial>=1 && filial <=3) && (modo=='P' || modo=='N') && mes >=1 && mes<=12 && nr>0 &&
                           existeCliente(cliente,clientes) && existeProduto(produto,produtos)) {
//                              vendas=insertCatP(vendas,produto,cliente,nr,preco,mes,filial,modo);
                              linhas_val ++;
                           
                             }
			}
       
 printf("Ficheiro lido: %s\nNúmero de linhas lidas: %d\nNúmero de linhas válidas: %d\n", nome_fich, linhas, linhas_val);	
 fclose(ficheiro);
 free(string);
 free(str);
 free(tmpString);

} 
else return 0;
  
return 1;
	}







int main () {
clientes=NULL;
produtos=NULL;
leitura("Clientes.txt");
leitura("Produtos.txt");
leitura("Vendas_1M.txt");
return 0;
}


