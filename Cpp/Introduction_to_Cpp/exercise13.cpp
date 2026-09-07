/*

Exercise: rewrite the createArray function without using the return statement

*/

#include <iostream>

// ##########################
// # Solution with pointers #
// ##########################
void createArray (int dim, int** array) {
  *array = new int[dim];
}

// ############################
// # Solution with references #
// ############################
// void createArray (int dim, int*& array)
// {
//   array = new int[dim];
// }

int main() {
  int dim = 0;
  std::cout << "Insert the dimension of the array: ";
  std::cin >> dim;

  if (dim < 0) {
    std::cout << "Negative number" << std::endl;
    return -1;
  }

  // ###################################
  // # Dynamic allocation of the array #
  // ###################################
  int* vec;

  // ##########################
  // # Solution with pointers #
  // ##########################
  createArray(dim,&vec);

  // ############################
  // # Solution with references #
  // ############################
  // createArray(dim,vec);
  
  // Fill the array
  for (int i = 0; i < dim; ++i) {
    vec[i] = i+1;
  }

  // Print the elements of the array
  for (int i = 0; i < dim; ++i) {
    std::cout << "Content of the cell " << i << " : " << vec[i] << std::endl;
  }

  delete[] vec;

  return 0;
}
