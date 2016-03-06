#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "produtos.h"

static NodoP produtos[26];
static NodoP produtosComprados[26];

int main () {
	FILE * ficheiro;
	int i;
	char *string = (char *) malloc(100);
	char *str = (char *) malloc(100);
	char *token = NULL;
	char limit[2] = " ";
	char *compra[7];
	int quantidade=0;
	ficheiro=fopen("Produtos.txt","r");
	while ((string = fgets (str, 100, ficheiro)) != NULL) {
		token = strtok(string, limit);
		token[6] = '\0';
		produtos[token[0]-'A'] = insertP(produtos[token[0]-'A'], token);
	}
	ficheiro = fopen("VendasValidas.txt", "r");
	while ((string = fgets (str, 100, ficheiro)) != NULL) {
			token = strtok(string, limit);
			compra[0] = token;
			for(i=1; token != NULL && i < 7; i++) {
				token = strtok(NULL, " ");
				compra[i] = token;
			} 
			token=compra[0];
			produtosComprados[token[0]-'A']=insertP(produtosComprados[token[0]-'A'],token);
	}
	for(i=0;i<26;i++){
		produtos[i]=removeP(produtos[i],produtosComprados[i]);
		quantidade+=contaNodosP(produtos[i]);
	}
	printf("nao foram comprados %d produtos\n",quantidade);
	free(string);
	free(str);
	return 0;
}