/*
c++ -std=c++11 -o esercizioAuto01 esercizioAuto01.cpp
-std=c++11 puo` essere utile in alcuni casi per forzare il compilatore ad usare C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

auto readData(std::string fileName, std::vector<double>& valVec) -> bool
{
  std::fstream myFile;

  myFile.open(fileName.c_str(),std::ios::in);
  if (myFile.good() == false)
    {
      return false;
    }

  double val;
  while (true)
    {
      myFile >> val;
      if (myFile.eof() == true) break;
      valVec.push_back(val);
    }
  myFile.close();

  return true;
}

int main (int argc, char** argv)
{
  // ##########################################################################
  // # Verify that at least three parameters are passed from the command line #
  // ##########################################################################
  if (argc < 3)
    {
      std::cout << "Insert from command line the two file names" << std::endl;
      std::cout << "\t./esercizioAuto01 data.txt results.txt" << std::endl;
      return 1;
    }


  std::string fileInput  = argv[1];
  std::string fileOutput = argv[2];


  // ############################
  // # Read data and processing #
  // ############################
  std::vector<double> vec;
  if (readData(fileInput, vec) == false)
    {
      std::cout << "Problem opening the file: " << fileInput.c_str() << std::endl;
      return 1;
    }

  auto Nrighe = vec.size();
  std::cout << "The std::vector vec contains " << Nrighe << " elements" << std::endl;

  auto sum = 0., sumSq = 0.;
  double mean, devst;

  for (int i = 0; i < Nrighe; i++)
    {
      sum   += vec[i];
      sumSq += vec[i]*vec[i];
    }
  mean  = sum/Nrighe;
  devst = sqrt(sumSq/Nrighe - mean*mean) * Nrighe/(Nrighe-1); // Unbiased standard deviation


  // #################################
  // # Write analysis on output file #
  // #################################
  std::ofstream OutFile (fileOutput.c_str());
  OutFile << "=== Results of the analysis ===" << std::endl;
  OutFile << "\tMean     = " << mean << std::endl;
  OutFile << "\tStd.Dev. = " << devst << std::endl;
  OutFile.close();


  return 0;
}
