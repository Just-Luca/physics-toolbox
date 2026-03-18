#include <stdio.h>
#include <stdlib.h>
#define key 6

int main () {

	int c;
	c = getchar();
	while (c != '*') {
		if (65<= c && c <= 90) {
			putchar(c+6);
			}
		else {if (97<= c && c <= 122) {
		putchar(c+6);
		}
		else if (c==32) {
		putchar(c);
		}
	}
	c=getchar();
	}
	exit(EXIT_SUCCESS);
	}		
