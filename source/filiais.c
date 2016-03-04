#include<stdio.h>
#include<stdlib.h>
#include<string.h>



int main () {
	FILE * ficheiro;
	int i;
	char *string = (char *) malloc(100);
	char *str = (char *) malloc(100);
	char *token = NULL;
	char limit[2] = " ";
        int filial;
	int filiais[3];
	char *compra[7];
	int total=0;
	filiais[0]=filiais[1]=filiais[2]=0;
	ficheiro = fopen("VendasValidas.txt", "r");
	while ((string = fgets (str, 100, ficheiro)) != NULL) {
			token = strtok(string, limit);
			compra[0] = token;
			for(i=1; token != NULL && i < 7; i++) {
				token = strtok(NULL, " ");
				compra[i] = token;
			} 
			filial=atoi(compra[6]);
			filiais[filial-1]++;
	}
	for(i=0;i<3;i++){
		printf("filial %d: %d vendas\n",i+1, filiais[i]);
		total+=filiais[i];
	}
	printf("vendas totais: %d\n",total);
	free(string);
	free(str);
	return 0;
}



