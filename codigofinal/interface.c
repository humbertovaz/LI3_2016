#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "headers/interface.h"
#include "headers/queries.h"
#include "headers/clientes.h"
#include "headers/produtos.h"
#include "headers/faturacao.h"
#include "headers/filial.h"

extern CatClientes clientes;
extern CatProdutos produtos;
extern Faturacao faturacao;
extern Filial fil;

void carregarFicheiros(){
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
}


void interface() {
    char r[50];
    int exitf=0;
    int estado=0;
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
        switch (estado) {
            case 0:
                system("clear");
                printf("Saiu do programa! Obrigado pela visita\n");
                exitf=1;
                break;
            case 1:
                carregarFicheiros();
                break;
            case 2: 
                printf("Não Concluido\n"); //estado = query2();
                break;
            case 3: 
                printf("Não Concluido\n"); //estado = query3();
                break;
            case 4: 
                printf("Não Concluido\n"); //estado = query4();
                break;   
            case 5: 
                printf("Não Concluido\n"); //estado = query5();
                break;
            case 6: 
                printf("Não Concluido\n"); //estado = query6();
                break;
            case 7: 
                printf("Não Concluido\n"); //estado = query7();
                break;
            case 8: 
                printf("Não Concluido\n"); //estado = query8();
                break;
            case 9: 
                printf("Não Concluido\n"); //estado = query9();
                break;      
            case 10: 
                printf("Não Concluido\n"); //estado = query10();
                break;
            case 11: 
                printf("Não Concluido\n"); //estado = query11();
                break;
            case 12: 
                printf("Não Concluido\n"); //estado = query12();
                break;                        
            default: 
                system("clear");
                printf("Tecla inválida\n");
                
                break;
        }
    }
}



int main (){
interface();
return 0;
}
