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
static Filial fil[3];



void interface() {
    int resultadoQ=1;
    int exitf=0;
    int estado=0;
    int mes,mes2;
    char letra,str[60];
   printf("%c[2J",27);
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
        if(resultadoQ){resultadoQ++;}
        resultadoQ=scanf("%d",&estado);
        getchar();
        printf("%c[2J",27);
        switch (estado) {
            case 0:
                printf("%c[2J",27);
                printf("Saiu do programa! Obrigado pela visita\n");
                exitf=1;
                break;
            case 1:
			    if(clientes && produtos && faturacao && fil[0] && fil[1] && fil[2]){
                    printf("entrou aqui\n");
        			free_catalogo_Clientes(clientes);
        			free_catalogo_produtos(produtos);
        			free_faturacao(faturacao);
        			free_filial(fil[0]);
                    free_filial(fil[1]);
                    free_filial(fil[2]);
    			}
    			clientes=inicializa_catalogo_clientes();
    			produtos=inicializa_catalogo_produtos();
    			faturacao=inicializa_faturacao();
    			fil[0]=inicializa_filial();
                fil[1]=inicializa_filial();
                fil[2]=inicializa_filial();
    			querie1("Clientes.txt",clientes,produtos,faturacao,fil);
    			querie1("Produtos.txt",clientes,produtos,faturacao,fil);
    			querie1("Vendas_1M.txt",clientes,produtos,faturacao,fil);
    			printf("Prima enter para continuar.\n");
    			getchar();
    			printf("%c[2J",27);
    			break;
            case 2: 
            	if(produtos){
            		printf("Insira a letra\n");
            		letra=getchar();
            		getchar();
                    if(letra<'A' || letra > 'Z') printf("Caracter invalido\n");
            		else querie2(produtos,letra);
            	}
            	else printf("Produtos nao carregados.\n");
            	printf("Prima enter para continuar.\n");
            	getchar();
            	printf("%c[2J",27);
                break;
            case 3: 
            	if(faturacao){
            		printf("Insira o produto\n");
            		resultadoQ=scanf("%s",str);
                    getchar();
                    if(existeProduto(str,produtos)){
            		  printf("Insira o mes\n");
            		  resultadoQ=scanf("%d",&mes);
            		  getchar();
                      if(mes<1 || mes>12) printf("Mes invalido\n");
            		  else querie3(faturacao,str,mes);
                    }
                    else printf("Produto invalido\n");
            	}
            	else printf("Vendas nao carregados.\n");
            	printf("Prima enter para continuar.\n");
            	getchar();
            	printf("%c[2J",27);
                break;
            case 4: 
            	if(faturacao){
            		querie4(faturacao);
            	}
            	else printf("Vendas nao carregados.\n");
            	printf("Prima enter para continuar.\n");
            	getchar();
            	printf("%c[2J",27);
                break;   
            case 5: 
            	if(fil[0] && fil[1] && fil[2]){
            		printf("Introduzir cliente\n");
            		resultadoQ=scanf("%s",str);
            		getchar();
            		printf("%c[2J",27);
                    if(existeCliente(str,clientes)){
            		  querie5(fil,str);
            		  printf("Prima enter para continuar.\n");
            		  getchar();
                    }
                    else printf("Cliente invalido\n");
            	}
            	else {
            		printf("Vendas nao carregados.\n");
            	}
                printf("Prima enter para continuar.\n");
                getchar();
            	printf("%c[2J",27);
                break; 
            case 6: 
            	if(faturacao){
            		printf("Introduzir intervalo (ex. 2 7)\n");
            		resultadoQ=scanf("%d %d",&mes, &mes2);
            		getchar();
            		printf("%c[2J",27);
                    if(mes>mes2 || mes<1 || mes2>12) printf("Intervalo invalido\n");
                    else{
            		  querie6(faturacao,mes,mes2);
                    }
            	}
            	else {
            		printf("Vendas nao carregados.\n");
            	}
                printf("Prima enter para continuar.\n");
                getchar();
            	printf("%c[2J",27);
                break; 
            case 7: 
            	if(fil[0] && fil[1] && fil[2]){
            		querie7(fil);
            		printf("Prima enter para continuar.\n");
            		getchar();
            	}
            	else {
            		printf("Vendas nao carregados.\n");
            		printf("Prima enter para continuar.\n");
            		getchar();
            	}
            	printf("%c[2J",27);
                break;
            case 8: 
            	if(fil[0] && fil[1] && fil[2]){
            		printf("Insira o produto.\n");
            		resultadoQ=scanf("%s",str);
                    getchar();
                    if(existeProduto(str,produtos)){
            		  printf("Insira a filial\n"); 
            		  resultadoQ=scanf("%d",&mes);
            		  getchar();
                      if(mes>3 || mes<1) printf("Filial invalida\n");
                      else{
            		      querie8(fil[mes-1],str);

                      }
                    }
                    else printf("Produto invalido\n");
            	}
            	else {
            		printf("Vendas nao carregados.\n");
            	}
                printf("Prima enter para continuar.\n");
                getchar();
            	printf("%c[2J",27);
                break;
            case 9: 
            	if(fil[0] && fil[1] && fil[2]){
            		printf("Insira cliente\n");
            		resultadoQ=scanf("%s",str);
                    getchar();
                    if(existeCliente(str,clientes)){
            		  printf("Insira o mes\n");
            		  resultadoQ=scanf("%d",&mes);
            		  getchar();
                      if(mes<1 || mes>12) printf("Mes invalido\n");
                      else{
            		      querie9(fil,str,mes);
                        }
                    }
                    else printf("Cliente invalido\n");
            	}
            	else {
            		printf("Vendas nao carregados.\n");
            	}
                printf("Prima enter para continuar.\n");
                getchar();
            	printf("%c[2J",27);
                break;     
            case 10: 
            	if(fil && faturacao){
            		printf("Introduzir numero.\n");
            		resultadoQ=scanf("%d",&mes);
            		getchar();
                    if(mes<0)printf("Numero invalido\n");
                    else{
            		  querie10(faturacao,fil,mes);
                    }
            	}
            	else {
            		printf("Vendas nao carregados.\n");
            	}
                printf("Prima enter para continuar.\n");
                getchar();
            	printf("%c[2J",27);
                break;
            case 11: 
            	if(fil[0] && fil[1] && fil[2]){
            		printf("Insira cliente\n");
            		resultadoQ=scanf("%s",str);
            		getchar();
                    if(existeCliente(str,clientes)){
            		  querie11(fil,str);
                    }
                    else printf("Cliente invalido\n");
            	}
            	else {
            		printf("Vendas nao carregados.\n");
            	}
                printf("Prima enter para continuar.\n");
                getchar();
            	printf("%c[2J",27);
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
            	printf("%c[2J",27);
                break;                        
            default: 
                printf("%c[2J",27);
                printf("Tecla inválida\n");
                
                break;
        }
    }
}




int main () {
interface();
free_faturacao(faturacao);
free_catalogo_produtos(produtos);
free_catalogo_Clientes(clientes);
free_filial(fil[0]);
free_filial(fil[1]);
free_filial(fil[2]);
return 0;
}


