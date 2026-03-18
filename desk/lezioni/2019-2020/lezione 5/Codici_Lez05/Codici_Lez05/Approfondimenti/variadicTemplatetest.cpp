/*
c++ -o variadicTemplatetest -std=c++11 variadicTemplatetest.cpp
*/

#include <iostream>
#include <string>

template<typename T>
void unpacker(T arg)
{
  std::cout << arg << " ";
}

template<typename T, typename... Ts>
void unpacker(T arg, Ts... args)
{
  std::cout << arg << " ";
  unpacker(args...);
}

int main ()
{
  std::cout << "Unpacking: ";
  unpacker<int, std::string, double>(10,"Hello",3.14);
  std::cout << std::endl;

  std::cout << "\nUnpacking: ";
  unpacker<float, char, std::string, int>(2.12,'a',"Hey",3);
  std::cout << std::endl;
}
