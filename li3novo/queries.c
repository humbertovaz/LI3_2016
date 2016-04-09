#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/clientes.h"
#include "headers/produtos.h"
#include "headers/faturacao.h"
#include "headers/filial.h"
#include "headers/array.h"


void querie2(CatProdutos cat, char letra){
	int i,j,pags,elems,exitf=0;
	char c;
	ARRAY a = listaProdutosLetra(cat,letra);
	pags=get_num_paginas(a);
	for(i=1;i<=pags && !exitf;){
		elems=(i-1)*10+get_num_elems_pag(a,i);
		system("clear");
		for(j=elems-10;j<elems;j++){
			printf("%s\n", get_elemento(a,j));
		}
		printf("Proxima pagina: 1\tPagina anterior: 2\tSair: Q\n");
		c=getchar();
		getchar(); //buffer para ler o \n do enter
		switch(c){
			case '1': if (i<pags) i++; break;
			case '2': if(i>1) i--; break;
			case 'Q': exitf=1; break; 
		}
	}
}

void querie3(Faturacao fat, char *produto, int mes){
	int i,vendasN=0,vendasP=0;
	float faturacaoN=0, faturacaoP=0;
	char c;
	printf("Valores totais? (y/n)\n");
	c=getchar();
	getchar();//buffer \n
	if(c=='y'){
		for(i=0;i<3;i++){
			vendasN+=getVendasNFilialX(produto,mes,fat,i);
			vendasP+=getVendasPFilialX(produto,mes,fat,i);
			faturacaoP+=getTotalFatPFilialX(produto,mes,fat,i);
			faturacaoN+=getTotalFatNFilialX(produto,mes,fat,i);
		}
		printf("vendas:\n\t Normal: %d Promocao: %d\nFaturado:\n\t Normal:%f Promocao:%f\n",vendasN,vendasP,faturacaoN,faturacaoP );
	}
	else{
		for(i=1;i<=3;i++){
			vendasN=getVendasNFilialX(produto,mes,fat,i);
			vendasP=getVendasPFilialX(produto,mes,fat,i);
			faturacaoP=getTotalFatPFilialX(produto,mes,fat,i);
			faturacaoN=getTotalFatNFilialX(produto,mes,fat,i);
			printf("filial %d:\n\tvendas:\n\t\tNormal: %d Promocao: %d\n\tFaturado:\n\t\tNormal: %f Promocao: %f\n",i,vendasN,vendasP,faturacaoN,faturacaoP );
		}
	}










}