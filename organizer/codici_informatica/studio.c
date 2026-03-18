#include <stdio.h>
#include <stdlib.h>

int main () {
int x, i; /* La variabile i serve da contatore */
x = 1;
i = 1;
while ( i <= 10 ) {
x = 2*x;
i = i + 1;
}
printf("%d \n", x);
exit(EXIT_SUCCESS);
}
