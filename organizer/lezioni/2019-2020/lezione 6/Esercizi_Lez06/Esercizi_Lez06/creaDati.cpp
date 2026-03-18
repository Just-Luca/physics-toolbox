/*
c++ -o creaDati creaDati.cpp
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <random>

namespace CONST
{
  double mean  = 10;
  double sigma =  1;
  int N        = 40;
}

int main (int argc, char** argv)
{
  std::default_random_engine generator;
  std::normal_distribution<double> pdfGauss(CONST::mean,CONST::sigma);

  // ########################################################################
  // # Verify that at least two parameters are passed from the command line #
  // ########################################################################
  if (argc < 2)
    {
      std::cout << "Insert from command line the file name" << std::endl;
      std::cout << "\t./creaDati data.txt" << std::endl;
      return 1;
    }

  std::string NomeFile = argv[1];
  std::ofstream OutFile (NomeFile.c_str());

  for (int i = 0; i < CONST::N; i++)
    {
      double val = pdfGauss(generator);
      double err = fabs(pdfGauss(generator) - CONST::mean);
      OutFile << val << "\t" << err << std::endl;
    }
  OutFile.close();

  return 0;
}
