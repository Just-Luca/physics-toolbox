#include <iostream>
#include <string>

int main()
{
	std::string parola;
	std::cout << "Inserisci una parola: ";
	std::cin >> parola;
	
	int N = 26; // Lettere della tastiera (no caratteri speciali)
	
	int array [N];
	for (int i = 0; i < N; i++)
	    array[i] = 0;
		
	char lettera = 'a';
	for (int i = 0; i < N; i++)
    {
    	for (int j = 0; j < parola.length(); j++)
		{
			if (lettera == parola[j])
				array[i]++;
		}
      
      	if (array[i] != 0)
			std::cout << "Lettera '" << lettera << "' : " << array[i] << std::endl;
    	lettera++;
    }

	return 0;
}

