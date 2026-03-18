/*
c++ -o string string.cpp
*/

#include <iostream>
#include <string>

int main()
{
  std::string sentence;
  std::cout << "Insert a sentence: ";
  getline(std::cin,sentence);

  const char* sentenceC = sentence.c_str();
  std::cout << "Sentence: " << sentenceC << std::endl;

  int length = sentence.length();
  std::cout << "Length of the sentence: " << length << " characters" << std::endl;

  std::string word ("pizza");
  int position = sentence.find(word);
  std::cout << "The word " << word << " was found in position " << position << std::endl;

  std::string word2 ("pozza");
  int comparison = word2.compare(word);
  if (comparison == 0) std::cout << "The two words (pizza and pozza) are identical" << std::endl;
  else                 std::cout << "The two words (pizza and pozza) are different" << std::endl;

  for (int i = 0; i < word2.length(); i++)
    std::cout << "Character " << i << ": " << word2[i] << std::endl;

  return 0;
}
