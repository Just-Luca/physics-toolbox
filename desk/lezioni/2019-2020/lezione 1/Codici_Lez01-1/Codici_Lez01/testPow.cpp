/*
c++ -o testPow testPow.cpp
*/

#include <iostream>
#include <cmath>
#include <ctime>

#define N 1e9

int main ()
{
  double stop, start;

  
  double test = 0;
  // #####################
  // # Benckmark for pow #
  // #####################
  start = (double)clock()/CLOCKS_PER_SEC;
  for (double i = 0; i < N; i++)
    {
      test += pow(i,2);
    }
  stop = (double)clock()/CLOCKS_PER_SEC;

  std::cout << "Time for pow(i,2) " << N << "-times\t= " << stop - start << " seconds" << std::endl;

  
  test = 0;
  // ################################
  // # Benckmark for multiplication #
  // ################################
  start = (double)clock()/CLOCKS_PER_SEC;
  for (double i = 0; i < N; i++)
    {
      test += i*i;
    }
  stop = (double)clock()/CLOCKS_PER_SEC;
  
  std::cout << "Time for i*i " << N << "-times\t= " << stop - start << " seconds" << std::endl;
}
