#include <stdio.h>
#include <string.h>
#include <stdlib.h>




int main () {
	FILE * ficheiro;
	int i;
	char *string = (char *) malloc(100);
	char *str = (char *) malloc(100);
	char *token = NULL;
	char limit[2] = " ";
	char *compra[7];
	char cliente[8]="Z5000";
	int quantidadetotal=0;
	int quantidade;
	int compras=0;
	float gastou=0;
	float preco;
	ficheiro = fopen("VendasValidas.txt", "r");
	while ((string = fgets (str, 100, ficheiro)) != NULL) {
			token = strtok(string, limit);
			compra[0] = token;
			for(i=1; token != NULL && i < 7; i++) {
				token = strtok(NULL, " ");
				compra[i] = token;
			} 
			preco = atof(compra[1]);
			quantidade= atoi(compra[2]);
			if(strcmp(cliente,compra[4])==0) {
				compras++;
				quantidadetotal+=quantidade;
				gastou+=preco*quantidade;
				}

	}
	printf("gastou: %f euros\ncomprou: %d produtos\nfez %d compras\n",gastou,quantidadetotal,compras);
	free(string);
	free(str);
	return 0;
}
