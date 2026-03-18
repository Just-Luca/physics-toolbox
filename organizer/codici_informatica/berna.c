#include <stdio.h>
#include <stdlib.h>




typedef struct nodo Nodo;
struct nodo {
	int valore;
	Nodo * prox;
};

void stampa (Nodo * t) {
	while ( t != NULL ) {
		printf("%d", t->valore);
		t = t->prox;
	}
	printf("\n");
	return;
}

Nodo * nuovonodo (int n) {
	Nodo * np;
	np = (Nodo *) malloc (sizeof(Nodo));
	if (np == NULL) exit(EXIT_FAILURE);
	np->valore = n;
	np->prox = NULL;
	return np;
}

Nodo * inserisci(int n, Nodo * t) {
	Nodo * nuovo;
	nuovo = nuovonodo (n);
	nuovo->prox = t;
	return nuovo;
}

int verifica (char x) {
	
	
int main (int argc, char * argv[]) {
	
	char c = 0;
	int n;
	
	do {
		c = getchar();
	}
	while (c != FINE);

	/* Nodo * testa;  
	testa = NULL;
	scanf ("%d", &n);
	while (n != 0) {
		testa = inserisci(n, testa);
		stampa(testa);
		scanf("%d", &n);
	}*/
	
	exit(EXIT_SUCCESS);
}
