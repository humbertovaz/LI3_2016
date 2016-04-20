#include "headers/queries.h"





void querie1(char *nome_fich, CatClientes clientes, CatProdutos produtos, Faturacao faturacao, Filial *fil){
	FILE * ficheiro;
	clock_t inicio,fim;
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
	inicio=clock();
	if (strcmp(nome_fich, "Clientes.txt") == 0){
		while ((string = fgets(str, 100, ficheiro)) != NULL) {
			linhas++;	
			token = strtok(string, limit);
			token[5] = '\0';
			insertC(clientes, token);
			for(i=0;i<3;i++)fil_regista_cliente(fil[i],token);             
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
				fil_insere_prod(fil[filial-1],cliente,produto,nr,mes,preco,modo);
                linhas_val ++;        
            }
		} 
 		printf("Ficheiro lido: %s\nNúmero de linhas lidas: %d\nNúmero de linhas válidas: %d\n", nome_fich, linhas, linhas_val);	
 		fclose(ficheiro);
 		free(string);
 		free(str);
 		free(tmpString);
	}
	fim=clock();
	printf("Ficheiro foi lido em %f\n",(double)(fim-inicio)/CLOCKS_PER_SEC );
}

void querie2(CatProdutos cat, char letra){
	ARRAY a;
	int i,j,pags,elems,exitf=0;
	clock_t inicio, fim;
	char c;
	inicio=clock();
	  a = listaProdutosLetra(cat,letra);
	fim=clock();
	pags=get_num_paginas(a);
	for(i=1;i<=pags && !exitf;){
		elems=(i-1)*10+get_num_elems_pag(a,i);
		
		printf("%c[2J",27);
                printf("A letra do produto foi : %c\n",letra);
                         printf("=======================================\n");

		for(j=elems-10;j<elems;j++){
			if (get_elemento(a,j)!=NULL)printf("Produto \t %s \n", (char *)get_elemento(a,j));
		}
                printf("=======================================\n");
		printf("\n");
		printf("Resultados produzidos em %f\n",(double)(fim-inicio)/CLOCKS_PER_SEC);
		printf("Proxima pagina: 1\tPagina anterior: 2\tSair: Q\n");
		c=getchar();
		getchar(); 
		switch(c){
			case '1': if (i<pags) i++; break;
			case '2': if(i>1) i--; break;
			case 'Q': exitf=1; break; 
		}
	}
	deep_free(a,free);
}

void querie3(Faturacao fat, char *produto, int mes){
	int i,vendasN=0,vendasP=0;
	float faturacaoN=0, faturacaoP=0;
	char c;
	clock_t inicio, fim;
	printf("Como deseja observar os valores?\n");
	printf("y -Total das filiais\n");
    printf("n -Total de cada filial\n ");
        
	c=getchar();
	getchar();
        printf("%c[2J",27);
	if(c=='y'){
                   printf("O produto introduzido foi : %s \t e o mes introduzido foi %d\n",produto, mes);
                 printf("=======================================\n");
		 
		inicio=clock();
		for(i=1;i<=3;i++){
			vendasN+=getQuantidadeNFilialX(produto,mes,fat,i);
			vendasP+=getQuantidadePFilialX(produto,mes,fat,i);
			faturacaoP+=getTotalFatPFilialX(produto,mes,fat,i);
			faturacaoN+=getTotalFatNFilialX(produto,mes,fat,i);

		}
		fim=clock();
		printf("Vendas:\n\t Normal: %d Promocao: %d\nFaturado:\n\t Normal:%f Promocao:%f\n",vendasN,vendasP,faturacaoN,faturacaoP );
                printf("=======================================\n");
		printf("Resultados produzidos em %f\n",((double)fim-(double)inicio) /CLOCKS_PER_SEC );
	}
	else{  
                printf("O produto introduzido foi : %s \t e o mes introduzido foi %d\n",produto, mes);
                printf("=================================================================================\n");
		inicio=clock();
		for(i=1;i<=3;i++){
			vendasN=getQuantidadeNFilialX(produto,mes,fat,i);
			vendasP=getQuantidadePFilialX(produto,mes,fat,i);
			faturacaoP=getTotalFatPFilialX(produto,mes,fat,i);
			faturacaoN=getTotalFatNFilialX(produto,mes,fat,i);
			printf("filial %d:\n\tvendas:\n\t\tNormal: %d Promocao: %d\n\tFaturado:\n\t\tNormal: %f Promocao: %f\n",i,vendasN,vendasP,faturacaoN,faturacaoP );
			 printf("=================================================================================\n");
		}
		fim=clock();
		
		printf("Resultados produzidos em %f\n",((double)fim-(double)inicio) /CLOCKS_PER_SEC );

	}
}

void querie4(Faturacao fat){
	int i,j,k,pags,elems,exitf=0;
       
        char c;
	clock_t  inicio,fim;
	ARRAY a;
	printf("Valores totais->y\n");
	printf("Valores por filiar->n\n");
	c=getchar();
	getchar();
       
	if(c=='y'){
		inicio=clock();
		a=naoComprados(fat);
		fim=clock();
		pags=get_num_paginas(a);
		for(i=1;i<=pags && !exitf;){
			elems=(i-1)*10+get_num_elems_pag(a,i);
			printf("%c[2J",27);
			printf("========================================\n");
			printf("\t %d resultados obtidos\n",get_tamanho(a));
			printf("========================================\n");
			for(j=elems-10;j<elems;j++){
				if(get_elemento(a,j)!=NULL) printf("Produto \t %s \n", (char *)get_elemento(a,j));
			}
			printf("========================================\n");
			printf("Resultados produzidos em %f\n",((double)fim-(double)inicio) /CLOCKS_PER_SEC);
			printf("Proxima pagina: 1\tPagina anterior: 2\tSair: Q\n");
			c=getchar();
			getchar(); 
			switch(c){
				case '1': if (i<pags) i++; break;
				case '2': if(i>1) i--; break;
				case 'Q': exitf=1; break; 
			}
		}
	}
	else{
		for(i=1;i<=3;i++){
			a=naoCompradosFilial(fat,i);
			pags=get_num_paginas(a);
			exitf=0;
			for(j=1;j<=pags && !exitf;){
				elems=(j-1)*10+get_num_elems_pag(a,j);
				printf("%c[2J",27);
				printf("========================================\n");
				printf("\t %d resultados obtidos\n",get_tamanho(a) );
				printf("========================================\n");
				printf("Filial %d\n",i );
				printf("\n");
				for(k=elems-10;k<elems;k++){
					if (get_elemento(a,k)!=NULL)printf("Produto \t %s \n",(char *) get_elemento(a,k));
				}
				 printf("========================================\n");
				if(i<=2) printf("Proxima pagina: 1 Pagina anterior:2 Proxima Filial: Q\n");
				else printf("Proxima pagina: 1 Pagina anterior:2 Sair: Q\n");
				c=getchar();
				getchar();
				switch(c){
					case '1': if (j<pags) j++; break;
					case '2': if(j>1) j--; break;
					case 'Q': exitf=1; break; 
				}
			}
			deep_free(a,free);
		}
	}
}

void querie5(Filial *fil, char *cliente){
	int q[3],i,j;
	clock_t inicio, fim;
	printf("===================================================================\n");
	printf("Compras feitas pelo cliente: %s\n", cliente);
	printf("===================================================================\n");
	printf("\t\tFilial 1\tFilial 2\tFilial 3\n");
	inicio=clock();
	for(i=0;i<12;i++){
		for(j=0;j<3;j++){
			q[j]=getQuantidadeMesCliente(fil[j],cliente,i+1);
		}
		if (i<9) printf("mes 0%d: \t%d\t\t%d\t\t%d\n",i+1,q[0],q[1],q[2]);
		else printf("mes %d: \t%d\t\t%d\t\t%d\n",i+1,q[0],q[1],q[2]);

	}
	fim=clock();
	printf("===================================================================\n");
	printf("Resultados produzidos em %f\n",((double)fim-(double)inicio) /CLOCKS_PER_SEC);
}


void querie6(Faturacao fat, int a, int b){
	clock_t inicio,fim;
	inicio=clock();
	printf("===================================================================\n");
	printf("Total de vendas: %d\nTotal faturado: %f\n", totalVendasMeses(fat,a,b), totalFatMeses(fat,a,b));
	fim=clock();
	printf("===================================================================\n");
	printf("Resultados produzidos em %f\n",((double)fim-(double)inicio) /CLOCKS_PER_SEC);
}



void querie7(Filial *fil){
	int i,j,pags,elems,exitf=0;
    ARRAY a;
	char c;
	clock_t inicio, fim;
	
	inicio=clock();
	
	a = compraram(fil[0]);
	removeNaoCompraram(fil[1],a);
	removeNaoCompraram(fil[2],a);

	for(i=0;i<3;i++) clientesCompraram(fil[i],a);
	fim=clock();
	pags=get_num_paginas(a);
	for(i=1;i<=pags && !exitf;){
		elems=(i-1)*10+get_num_elems_pag(a,i);
		printf("%c[2J",27);
		printf("=======================================================\n");
		printf("\t %d resultados\n",get_tamanho(a) );
		printf("=======================================================\n");
		for(j=elems-10;j<elems;j++){
			if(get_elemento(a,j)!=NULL)printf("Cliente\t %s\n", (char *)get_elemento(a,j));
		}
		printf("=======================================================\n");
		printf("Resultados produzidos em %f\n", ((double)fim-(double)inicio) /CLOCKS_PER_SEC);
		printf("=======================================================\n");
		printf("Proxima pagina: 1\tPagina anterior: 2\tSair: Q\n");
		c=getchar();
		getchar(); 
		switch(c){
			case '1': if (i<pags) i++; break;
			case '2': if(i>1) i--; break;
			case 'Q': exitf=1; break; 
		}
	}
	deep_free(a,free);
}


void querie8(Filial fil, char* produto){
	int i,j,pags,elems,exitf=0;
    ARRAY a;
	char c;
	clock_t inicio, fim;
	inicio=clock();
	a = clientesCompraramProduto(fil,produto);
	fim=clock();
	pags=get_num_paginas(a);
	for(i=1;i<=pags && !exitf;){
		elems=(i-1)*10+get_num_elems_pag(a,i);
		printf("%c[2J",27);
		printf("======================================================\n");
		printf("%d resultados\n",get_tamanho(a) );
		printf("=============================================================\n");
		printf("Cliente\t |  Normal\t | Promocao\n");
		printf("=============================================================\n");
		for(j=elems-10;j<elems;j++){
			if(get_elemento(a,j)!=NULL){
				printf("%s\t", (char *)get_elemento(a,j));
				if(comprouProdutoN(fil,get_elemento(a,j),produto)) printf("\t    SIM\t");
				else printf("    NAO\t");
				if(comprouProdutoP(fil,get_elemento(a,j),produto)) printf("\t    SIM\n");
				else printf("    NAO\n");
			}
		}
		printf("=============================================================\n");
		printf("Resultados produzidos em %.3f\n",((double)fim-(double)inicio) /CLOCKS_PER_SEC);
		printf("=============================================================\n");
		printf("Proxima pagina: 1\tPagina anterior: 2\tSair: Q\n");
		c=getchar();
		getchar(); 
		switch(c){
			case '1': if (i<pags) i++; break;
			case '2': if(i>1) i--; break;
			case 'Q': exitf=1; break; 
		}
	}
	deep_free(a,free);
}

void querie9(Filial *fil, char* cliente, int mes){
	int i,j,pags,elems,exitf=0;
    ARRAY a;
	char c;
	clock_t inicio,fim;
	a=inicializa_array();
	inicio=clock();
	for(i=0;i<3;i++){
		getIProdMes(fil[i],cliente,mes,a);
	}
	a=extraiPorQuantidade(a,mes);
	fim=clock();
	pags=get_num_paginas(a);
	printf("O cliente escolhido foi %s e o mes escolhido foi %d",cliente,mes);
	printf("========================================\n");
	for(i=1;i<=pags && !exitf;){
		elems=(i-1)*10+get_num_elems_pag(a,i);
		printf("%c[2J",27);
		printf("========================================\n");
		printf("\t %d resultados obtidos\n",get_tamanho(a) );
		printf("========================================\n");
		for(j=elems-10;j<elems;j++){
			if(get_elemento(a,j)!=NULL)printf("Produto \t %s\n",(char*) get_elemento(a,j));
		}

		printf("========================================\n");
		printf("Resultados gerados em %f\n",((double)fim-(double)inicio) /CLOCKS_PER_SEC );
		printf("========================================\n");
		printf("Proxima pagina: 1\tPagina anterior: 2\tSair: Q\n");
		c=getchar();
		getchar(); 
		switch(c){
			case '1': if (i<pags) i++; break;
			case '2': if(i>1) i--; break;
			case 'Q': exitf=1; break; 
		}
	}
	deep_free(a,free);	
}

void querie10(Faturacao fat,Filial *fil, int n){
	int i,j,k,pags,elems,exitf=0;
	char c;
    ARRAY a;
	clock_t inicio1,inicio2,fim1,fim2;
	inicio1=clock();
	a = nMaisVendidos(fat,n);
	fim1=clock();
	pags=get_num_paginas_metade(a);
       inicio2=clock();
	for(i=1;i<=pags && !exitf;){
		elems=(i-1)*5+get_num_elems_pag_metade(a,i);
		printf("%c[2J",27);
		printf("===============================================================================\n");
		printf("\t %d resultados\n",get_tamanho(a) );
		for(j=elems-5;j<elems;j++){
			if(get_elemento(a,j)!=NULL){
				printf("===============================================================================\n");
				printf("\t Produto \t %s:\n",(char *) get_elemento(a,j));
				 printf("===============================================================================\n");
				for(k=1;k<=3;k++){
					printf("Filial %d: numero de clientes: %d quantidade vendida: %d\n",k,getNumClientesFilial(fil[k-1],get_elemento(a,j)),getQuantidadeFilial(fat,get_elemento(a,j),k));
				}
				
			}
		}
        fim2=clock();
        printf("===============================================================================\n");
        if (i==1)printf("Resultados produzidos em %f\n", (((double)fim1-(double)inicio1) /CLOCKS_PER_SEC)+(((double)fim2-(double)inicio2) /CLOCKS_PER_SEC) );
		else printf("Resultados produzidos em %f \n",((double)fim2-(double)inicio2) /CLOCKS_PER_SEC );
		printf("===============================================================================\n");
		printf("Proxima pagina: 1\tPagina anterior: 2\tSair: Q\n");
		
		c=getchar();
		getchar();
		switch(c){
			case '1': if (i<pags) i++; break;
			case '2': if(i>1) i--; break;
			case 'Q': exitf=1; break; 
		}
	}
	deep_free(a,free);
}

void querie11(Filial *fil, char* cliente){
	int i,j;
    ARRAY a;
	clock_t inicio,fim;
	a=inicializa_array();
	inicio=clock();
	for(i=0;i<3;i++){
		for(j=0;j<12;j++){
			getIProdMes(fil[i],cliente,j,a);
		}
	}
	a = topMaisGastou(a);
	fim=clock();
	printf("%c[2J",27);
	printf("=============================================\n");
	printf("O cliente introduzido foi %s\n",cliente);
	printf("=============================================\n");

	for(i=0;i<3;i++){
		if(get_elemento(a,i)!=NULL)printf("Protudo \t %s\n", (char*) get_elemento(a,i));
	}
	printf("=============================================\n");
	printf("Resultados produzidos em %f\n",((double)fim-(double)inicio)/CLOCKS_PER_SEC );
	printf("=============================================\n");
	printf("Prima qualquer tecla para sair\n");
	getchar(); 
	deep_free(a,free);
}



void querie12(Filial *fil, Faturacao fat){
    ARRAY a,b;
	clock_t inicio, fim;
	inicio=clock();
	b=naoCompraram(fil[0]);
	removeCompraram(fil[1],b);
	removeCompraram(fil[2],b);
	a = naoComprados(fat);
	fim=clock();
	printf("=============================================\n");
	printf("Clientes que nunca compraram:%d\n",get_tamanho(b));
	printf("=============================================\n");
	printf("Produtos nunca comprados:%d\n",get_tamanho(a));
	printf("=============================================\n");
	printf("Resultados produzidos em %.3f\n",((double)fim-(double)inicio) /CLOCKS_PER_SEC);
	printf("=============================================\n");
	deep_free(a,free);
	deep_free(b,free);
}





