#include <stdio.h>
#include <stdlib.h>

int main (int argc, char * argv[]) {
	int c, a;
	c = getchar();
	a = 'A';
	int x;
	
	while (c != '0') {
	if (c == a) {
		x=1;
	} else { x=0;}
	printf("%d", x);
	c = getchar();
	
	}
	exit(EXIT_SUCCESS);
}	
