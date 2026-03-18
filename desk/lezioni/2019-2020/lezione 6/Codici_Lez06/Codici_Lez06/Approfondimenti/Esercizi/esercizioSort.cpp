/*
c++ -o esercizioSort esercizioSort.cpp
*/

#include <iostream>
#include <ctime>
#include <algorithm>
#include <vector>

#define DIM 10

void BubbleSort(double* myArray, int dim, int tmp = 0) // "tmp" was added for compatibility with calling sequence of QuickSort in order to test function pointers without template
{
  bool flag = true;

  for (int i = 1; (i < dim && flag == true); i++)
    {
      flag = false;

      for (int j = 0; j < (dim - i); j++)
        {
          if (myArray[j+1] < myArray[j])
            {
              double temp  = myArray[j];
              myArray[j]   = myArray[j+1];
              myArray[j+1] = temp;

              flag = true;
            }
        }
    }
}

void QuickSort(double* myArray, int lo, int hi)
{
  if (lo < hi)
    {
      double pivot = myArray[hi];
      int i = lo;
      for (int j = lo; j < hi; j++)
        {
          if (myArray[j] < pivot)
            {
              if (i != j)
                {
                  double temp = myArray[j];
                  myArray[j]  = myArray[i];
                  myArray[i]  = temp;
                }
              i++;
            }
        }
      double temp = myArray[i];
      myArray[i]  = myArray[hi];
      myArray[hi] = temp;

      QuickSort(myArray, lo, i - 1);
      QuickSort(myArray, i + 1, hi);
    }
}

// It's possible to implement the calling sequence with or without template
template <typename T>
void GeneralSort(T sortAlgo, double* myArray, int i1, int i2)
// void GeneralSort(void (*sortAlgo) (double*, int, int), double* myArray, int i1, int i2)
{
  sortAlgo(myArray,i1,i2);
}

int main (int argc, char** argv)
{
  double start, stop;
  double* data = new double[DIM];


  for (int i = 0; i < DIM; i++) data[i] = DIM-i;
  // #############################
  // # Benchmark for bubble sort #
  // #############################
  start = (double)clock()/CLOCKS_PER_SEC;
  BubbleSort(data, DIM);
  stop = (double)clock()/CLOCKS_PER_SEC;
  std::cout << "Time for bubble sort: " << stop - start << " seconds" << std::endl;


  for (int i = 0; i < DIM; i++) data[i] = DIM-i;
  // ############################
  // # Benchmark for quick sort #
  // ############################
  start = (double)clock()/CLOCKS_PER_SEC;
  QuickSort(data, 0, DIM-1);
  stop = (double)clock()/CLOCKS_PER_SEC;
  std::cout << "Time for quick sort: " << stop - start << " seconds" << std::endl;


  std::vector<int> vec;
  for (int i = 0; i < DIM; i++) vec.push_back(DIM-i);
  // #############################
  // # Benchmark for std::sort() #
  // #############################
  start = (double)clock()/CLOCKS_PER_SEC;
  std::sort(vec.begin(), vec.end());
  stop = (double)clock()/CLOCKS_PER_SEC;
  std::cout << "Time for STL std::sort(): " << stop - start << " seconds" << std::endl;


  // ##########################
  // # Test function pointers #
  // ##########################
  char choice;
  int i1, i2;

  while (true)
    {
      std::cout << "Choose which algorithm ('b' = bubble sort; 'q' = quick sort; else = exit): ";
      std::cin >> choice;

      if ((choice != 'b') && (choice != 'q')) break;

      std::cout << "Un-sorted values:" << std::endl;
      for (int i = 0; i < DIM; i++)
        {
          data[i] = DIM-i;
          std::cout << "Val " << i << " = " << data[i] << std::endl;
        }

      if (choice == 'b')
        {
          std::cout << "\n--> Using bubble sort <--\n" << std::endl;
          i1 = DIM;
          i2 = 0;
          GeneralSort(&BubbleSort,data,i1,i2);
        }
      else
        {
          std::cout << "\n--> Using quick sort <--\n" << std::endl;
          i1 = 0;
          i2 = DIM-1;
          GeneralSort(&QuickSort,data,i1,i2);
        }

      std::cout << "Sorted values:" << std::endl;
      for (int i = 0; i < DIM; i++)
        std::cout << "Val " << i << " = " << data[i] << std::endl;
    }


  delete[] data;
  return 0;
}
