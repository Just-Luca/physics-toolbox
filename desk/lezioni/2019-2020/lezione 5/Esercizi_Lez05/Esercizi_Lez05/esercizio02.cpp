/*
c++ -o esercizio02 esercizio02.cpp
*/

#include <iostream>
#include <string>

#define N 26 // Keyboard characters (no special ones)

int main()
{
  std::string word;
  std::cout << "Insert a word: ";
  std::cin >> word;

  int array [N];
  for (int i = 0; i < N; i++)
    array[i] = 0;

  char character = 'a';
  for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < word.length(); j++)
        {
          if (character == word[j]) array[i]++;
        }

      if (array[i] != 0)
        std::cout << "Character '" << character << "' : " << array[i] << std::endl;
      character++;
    }

  return 0;
}
