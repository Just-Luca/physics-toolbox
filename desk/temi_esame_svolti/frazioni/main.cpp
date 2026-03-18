#include <iostream>
#include "frazione.h"

using namespace std;

int main() {
	frazione f1(1, 4);
	frazione f2(1, 4);

	f1.somma(f2);
	f1.stampa();

	frazione f3(2, 3);
	frazione f4(2, 12);
	f2.moltiplica(f3);
	f2.stampa();
	int confronto = f2.compara(f4);
	cout << "Il confronto e': " << confronto << endl;

	return 0;
}
