/*

Exercise: redo Exercise07 using a single function that calculates both the mean and variance (using pointers/references)

*/

#include <iostream>

#define DIM 10

void DataAnalysis(double* data, int dim, double& mean, double& var) {
  for (int i = 0; i < dim; i++) {
    mean += data[i];
    var  += data[i]*data[i];
  }

  mean = mean / dim;
  var = (var/dim - mean*mean) * dim / (dim-1);
  // Compute the "unbiased" estimator of the variance
}

int main (int argc, char** argv) {

  int dim = DIM;
  double* data = new double[dim];
  double mean;
  double var;

  for (int i = 0; i < dim; i++) {
    data[i] = i;
  }

  DataAnalysis(data, dim, mean, var);
  std::cout << std::endl;
  std::cout << "Sample mean: " << mean << "\nSample variance: " << var << std::endl;
  
  delete[] data;
  
  return 0;
}
