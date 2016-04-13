#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers/clientes.h"
#include "headers/produtos.h"
#include "headers/faturacao.h"
#include "headers/filial.h"
#include "headers/array.h"
#include "headers/queries.h"






static CatClientes clientes;
static CatProdutos produtos;
static Faturacao faturacao;
static Filial fil;




/*
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
	int i = 0;
	int nr;
	int mes;
	double preco;
	char  *compra[7];
    char *cliente;
    char *produto;
    char * tmpString= (char *) malloc(100);
	ficheiro = fopen(nome_fich, "r");
	if (strcmp(nome_fich, "Clientes.txt") == 0){
		while ((string = fgets (str, 100, ficheiro)) != NULL) {
			linhas++;	
			token = strtok(string, limit);
			token[5] = '\0';
			insertC(clientes, token);
			fil_regista_cliente(fil,token);             
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
			cont_regista_produto(faturacao, token);

		}
		printf("Ficheiro lido: %s\nNúmero de linhas lidas: %d\n", nome_fich, linhas);	
 		fclose(ficheiro);
 		free(string);
 		free(str);
	}
   
  	else if (strcmp(nome_fich,"Vendas_1M.txt") == 0){
		while ((string = fgets (str, 100, ficheiro)) != NULL) {
			linhas++;
			strcpy(tmpString,string);
			token = strtok(string, limit);
			compra[0] = token;
			for(i=1; token != NULL && i < 7; i++) {
				token = strtok(NULL, " ");
				compra[i] = token;                
			}
			preco = strtod(compra[1], &compra[1]);
            nr = atoi(compra[2]);
			mes = atoi(compra[5]);
			modo = compra[3][0];
			filial=atoi(compra[6]);
            cliente=compra[4]; 
            produto=compra[0];
			if ((preco>=0.0 && preco <= 999.99) && (filial>=1 && filial <=3) && (modo=='P' || modo=='N') && mes >=1 && mes<=12 && nr>0 && existeCliente(cliente,clientes) && existeProduto(produto,produtos)) {
				cont_insere_venda(faturacao,produto,nr,preco,modo,mes,filial);
				fil_insere_prod(fil,cliente,produto,nr,filial,mes,preco,modo);
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

*/


void interface() {
    char r[50];
    int exitf=0;
    int estado=0;
    int mes,mes2;
    char letra,str[60];
    system("clear");
    while (!exitf) {
        
                puts("========================================================================================================================");
                puts("\t\tGereVendas >> MENU PRINCIPAL");
                puts("1  - Carregar dados para memória");
                puts("2  - Determinar a lista e o total de produtos cujo código se inicia por uma dada leitura"); 
                puts("3  - Numero total de vendas e o total facturado com esse produto num mês"); 
                puts("4  - Lista ordenada dos códigos dos produtos  que ninguém comprou");
                puts("5  - Tabela com o numero total de produtos comprados");
                puts("6  - Determinar o total de vendas registadas num intervalo de meses e o total facturado");
                puts("7  - lista ordenada de códigos de clientes que realizaram compras em todas as filiais");
                puts("8  - códigos (e número total) dos clientes que o compraram, distinguindo entre compra N e compra P;");
                puts("9  - lista de códigos de produtos que mais um dado cliente num determinado mês");
                puts("10 - Produtos mais vendidos em todo o ano, indicando o numero total de clientes e o numero de unidades vendidas");
                puts("11 - Códigos dos 3 produtos em que mais gastou dinheiro durante o ano dado um código de cliente");
                puts("12 - Determinar o numero de clientes registados que nao realizaram compras e produtos não comprados");
                puts("-----------------------------------------------------------------------------------------------------------------------");
                puts("BEM-VINDO                   0 - Sair");
                puts("=======================================================================================================================");                                           
                

        printf("Escolha uma opcao > ");

      
        scanf("%d",&estado);
        getchar();
        system("clear");
        switch (estado) {
            case 0:
                system("clear");
                printf("Saiu do programa! Obrigado pela visita\n");
                exitf=1;
                break;
            case 1:
			    if(clientes && produtos && faturacao && fil){
        			free_catalogo_Clientes(clientes);
        			free_catalogo_produtos(produtos);
        			free_faturacao(faturacao);
        			free_filial(fil);
    			}
    			clientes=inicializa_catalogo_clientes();
    			produtos=inicializa_catalogo_produtos();
    			faturacao=inicializa_faturacao();
    			fil=inicializa_filial();
    			querie1("Clientes.txt",clientes,produtos,faturacao,fil);
    			querie1("Produtos.txt",clientes,produtos,faturacao,fil);
    			querie1("Vendas_1M.txt",clientes,produtos,faturacao,fil);
    			printf("Prima enter para continuar.\n");
    			getchar();
    			system("clear");
    			break;
            case 2: 
            	if(produtos){
            		printf("Insira a letra\n");
            		letra=getchar();
            		getchar();
            		querie2(produtos,letra);
            	}
            	else printf("Produtos nao carregados.\n");
            	printf("Prima enter para continuar.\n");
            	getchar();
            	system("clear");
                break;
            case 3: 
            	if(faturacao){
            		printf("Insira o produto\n");
            		scanf("%s",str);
            		printf("Insira o mes\n");
            		scanf("%d",&mes);
            		getchar();
            		querie3(faturacao,str,mes);
            	}
            	else printf("Vendas nao carregados.\n");
            	printf("Prima enter para continuar.\n");
            	getchar();
            	system("clear");
                break;
            case 4: 
            	if(faturacao){
            		querie4(faturacao);
            	}
            	else printf("Vendas nao carregados.\n");
            	printf("Prima enter para continuar.\n");
            	getchar();
            	system("clear");
                break;   
            case 5: 
            	if(fil){
            		printf("Introduzir cliente\n");
            		scanf("%s",str);
            		getchar();
            		system("clear");
            		querie5(fil,str);
            		printf("Prima enter para continuar.\n");
            		getchar();
            	}
            	else {
            		printf("Vendas nao carregados.\n");
            		printf("Prima enter para continuar.\n");
            		getchar();
            	}
            	system("clear");
                break; 
            case 6: 
            	if(faturacao){
            		printf("Introduzir intervalo (ex. 2 7)\n");
            		scanf("%d %d",&mes, &mes2);
            		getchar();
            		system("clear");
            		querie6(faturacao,mes,mes2);
            		printf("Prima enter para continuar.\n");
            		getchar();
            	}
            	else {
            		printf("Vendas nao carregados.\n");
            		printf("Prima enter para continuar.\n");
            		getchar();
            	}
            	system("clear");
                break; 
            case 7: 
            	if(fil){
            		querie7(fil);
            		printf("Prima enter para continuar.\n");
            		getchar();
            	}
            	else {
            		printf("Vendas nao carregados.\n");
            		printf("Prima enter para continuar.\n");
            		getchar();
            	}
            	system("clear");
                break;
            case 8: 
            	if(fil){
            		printf("Insira o produto.\n");
            		scanf("%s",str);
            		printf("Insira a filial\n"); 
            		scanf("%d",&mes);
            		getchar();
            		querie8(fil,str,mes);
            		printf("Prima enter para continuar.\n");
            		getchar();
            	}
            	else {
            		printf("Vendas nao carregados.\n");
            		printf("Prima enter para continuar.\n");
            		getchar();
            	}
            	system("clear");
                break;
            case 9: 
            	if(fil){
            		printf("Insira cliente\n");
            		scanf("%s",str);
            		printf("Insira o mes\n");
            		scanf("%d",&mes);
            		getchar();
            		querie9(fil,str,mes);
            		printf("Prima enter para continuar.\n");
            		getchar();
            	}
            	else {
            		printf("Vendas nao carregados.\n");
            		printf("Prima enter para continuar.\n");
            		getchar();
            	}
            	system("clear");
                break;     
            case 10: 
            	if(fil && faturacao){
            		printf("Introduzir numero.\n");
            		scanf("%d",&mes);
            		getchar();
            		querie10(faturacao,fil,mes);
            		printf("Prima enter para continuar.\n");
            		getchar();
            	}
            	else {
            		printf("Vendas nao carregados.\n");
            		printf("Prima enter para continuar.\n");
            		getchar();
            	}
            	system("clear");
                break;
            case 11: 
            	if(fil){
            		printf("Insira cliente\n");
            		scanf("%s",str);
            		getchar();
            		querie11(fil,str);
            		printf("Prima enter para continuar.\n");
            		getchar();
            	}
            	else {
            		printf("Vendas nao carregados.\n");
            		printf("Prima enter para continuar.\n");
            		getchar();
            	}
            	system("clear");
                break;
            case 12: 
            	if(fil && faturacao){
            		querie12(fil,faturacao);
            		printf("Prima enter para continuar.\n");
            		getchar();
            	}
            	else {
            		printf("Vendas nao carregados.\n");
            		printf("Prima enter para continuar.\n");
            		getchar();
            	}
            	system("clear");
                break;                        
            default: 
                system("clear");
                printf("Tecla inválida\n");
                
                break;
        }
    }
}




int main () {
interface();
/*
CatClientes clientes=inicializa_catalogo_clientes();
CatProdutos produtos=inicializa_catalogo_produtos();
Faturacao faturacao=inicializa_faturacao();
Filial fil=inicializa_filial();*/
/*
leitura("Clientes.txt");
leitura("Produtos.txt");
leitura("Vendas_1M.txt");
*/
//querie2(produtos,'A');
//querie3(faturacao,"AF1184",6);
//querie4(faturacao);
//querie5(fil,"Z5000");
//querie6(faturacao,1,12);
//querie7(fil);
//querie8(fil,"AF1184",2);
//querie9(fil,"Z5000",4);
//querie10(faturacao,fil,5);
//querie11(fil,"Z5000");
//querie12(fil,faturacao);
free_faturacao(faturacao);
free_catalogo_produtos(produtos);
free_catalogo_Clientes(clientes);
free_filial(fil);
return 0;
}


