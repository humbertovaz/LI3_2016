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
	double totalfaturado=0;
	int quantidade;
	int gratis=0;
	int vendidos=0;
	double preco;
	ficheiro = fopen("VendasValidas.txt", "r");
	while ((string = fgets (str, 100, ficheiro)) != NULL) {
			token = strtok(string, limit);
			compra[0] = token;
			for(i=1; token != NULL && i < 7; i++) {
				token = strtok(NULL, " ");
				compra[i] = token;
			} 
			preco = atoi(compra[1]);
			quantidade= atoi(compra[2]);
			if(preco==0) gratis+=quantidade;
			vendidos+=quantidade;
			totalfaturado+=preco*quantidade;
	}
	printf("gratis: %d unidades\ntotal faturado: %f\ntotal vendido:%d unidades\n",gratis,totalfaturado,vendidos);
	free(string);
	free(str);
	return 0;
}
