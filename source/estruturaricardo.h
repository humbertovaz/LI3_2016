#include <stdlib.h>

typedef struct catc{
	char cliente[8];
	struct catc *l,*r;
	int quantidadesP[3][12];
	double gastouP[3][12];
	int quantidadesN[3][12];
	double gastouN[3][12];
	int vendasP[3][12];
	int vendasN[3][12];
	int altura;
}*CatC;

typedef struct catproduto{
	char produto[8];
	int quantidadesP[3][12];
	double faturadoP[3][12];
	int quantidadesN[3][12];
	double faturadoN[3][12];
	int vendasP[3][12];
	int vendasN[3][12];
	CatC clientesN[3];
	CatC clientesP[3];
	struct catproduto *l,*r;
	int altura;
}*CatP;

int maxCat(int x,int y);
int alturaCatP(CatP p);
int alturaCatC(CatC p);
CatP novoNodoCatP(char *prod,char *cliente, int q, float p, int mes, int filial,char M);
CatC novoNodoCatC(char *cliente, int q, float p, int mes, int filial, char M);
CatP dirRotateCatP(CatP p);
CatP esqRotateCatP(CatP x);
CatC esqRotateCatC(CatC x);
CatC dirRotateCatC(CatC p);
int getBalanceCatP(CatP N);
int getBalanceCatC(CatC N);
CatP insertCatP(CatP nodo, char *prod, char* cliente, int q, float p, int mes, int filial,char M);
CatC insertCatC(CatC nodo, char *cliente, int q, float p, int mes, int filial, char M);
int quantos(CatP p, char *prod, int q[][12],int v[][12],double f[][12]);


