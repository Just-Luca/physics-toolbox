/*

Exercise: use new and delete to create and destroy a double variable and a doubles array

*/

#include <iostream>

int main() {

  double *value = new double(1.5);
  std::cout << "Value created with new: " << *value << std::endl;
  delete value;

  int dim = 5;
  double *array = new double[dim];
  
  for (int i = 0; i < dim; i++) {

    array[i] = 2.2 * i;
    std::cout << "Array's value [" << i << "] created with new: " << array[i] << std::endl;
  }
  delete [] array;

  return 0;
}
