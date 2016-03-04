typedef struct produtos{
	char code[8];
	int altura;
	struct Nodo *l,*r;
} *Produtos,produto;

void deleteP(AVL a);
int existeP(Produtos a, char s[]);
int alturaP (Produtos a);
int maxP( int l, int r);
Produtos rotateLeftP(Produtos a);
Produtos rotateRightP(Produtos a);
Produtos doubleRotateLeftP(Produtos a);
Produtos doubleRotateRightP(Produtos a);
Produtos inserirP(char s[], Produtos a);