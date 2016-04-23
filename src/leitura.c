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
        
                puts("================================================================================");
                puts("\t\tGereVendas >> MENU PRINCIPAL");
                puts("1  - Carregar ficheiros.");
                puts("2  - Produtos que iniciam por uma dada letra."); 
                puts("3  - Número total facturado de um dado produto num respectivo mês."); 
                puts("4  - Lista dos produtos  que ninguém comprou.");
                puts("5  - Total de produtos comprados de um dado cliente.");
                puts("6  - Número de vendas e o total faturado de um dado intervalo de meses.");
                puts("7  - Clientes que compraram em todas as filiais.");
                puts("8  - Clientes que compraram um determinado produto numa determinada filial.");
                puts("9  - Produtos comprados por um cliente num mês (ordenados por quantidade).");
                puts("10 - N produtos mais vendidos.");
                puts("11 - Os 3 produtos que um cliente mais dinheiro gastou.");
                puts("12 - Numero de clientes que nunca compraram e produtos nunca comprados.");
                puts("--------------------------------------------------------------------------------");
                puts("BEM-VINDO                   0 - Sair");
                puts("================================================================================");                                           
                

        printf("Escolha uma opcao > ");
        if(resultadoQ){resultadoQ++;}
        resultadoQ=scanf("%d",&estado);
        getchar();
        printf("%c[2J",27);
        switch (estado) {
            case 0:
                printf("%c[2J",27);
                printf("Saiu do programa!\n");
                exitf=1;
                break;
            case 1:
                printf("================================================================================\n");                                           
                printf("Ficheiros disponiveis:\n");
                printf("1 - Ficheiro de Vendas 1 milhao\n");
                printf("2 - Ficheiro de Vendas 3 milhoes\n");
                printf("3 - Ficheiro de Vendas 5 milhos\n");
                printf("================================================================================\n"); 
                printf("Escolha ficheiro\n");                                          
                resultadoQ=scanf("%d",&mes);
                getchar();
                printf("%c[2J",27);
			    if(clientes && produtos && faturacao && fil[0] && fil[1] && fil[2]){
                
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
                if(mes==1) querie1("Vendas_1M.txt",clientes,produtos,faturacao,fil);
                if(mes==2) querie1("Vendas_3M.txt",clientes,produtos,faturacao,fil);
                if(mes==3) querie1("Vendas_5M.txt",clientes,produtos,faturacao,fil);
                else if(mes>3) printf("Ficheiro invalido\n");
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
            		printf("Insira o produto que deseja ver\n");
            		resultadoQ=scanf("%s",str);
                    getchar(); 
                       
                    if(existeProduto(str,produtos)){
            		  printf("Insira o mes que deseja consultar \n");
            		  resultadoQ=scanf("%d",&mes);
            		  getchar();
                      if(mes<1 || mes>12) printf("Mes introduzido é invalido\n");
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
            		printf("Introduza um cliente\n");
            		resultadoQ=scanf("%s",str);
            		getchar();
            		printf("%c[2J",27);
                    if(existeCliente(str,clientes)){
            		  querie5(fil,str);
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
            		printf("Introduza um intervalo\n");
                    printf("Exemplo 2-3 \n");
            		resultadoQ=scanf("%d-%d",&mes, &mes2);
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
            		printf("Introduza um produto.\n");
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
            		printf("Introduza um cliente\n");
            		resultadoQ=scanf("%s",str);
                    getchar();
                    if(existeCliente(str,clientes)){
            		  printf("Introduza um mes\n");
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
            	if(fil[0] && fil[1] && fil[2] && faturacao){
            		printf("Introduza um numero.\n");
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
            		printf("Introduza um cliente\n");
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
            	if(fil[0] && fil[1] && fil[2] && faturacao){
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


