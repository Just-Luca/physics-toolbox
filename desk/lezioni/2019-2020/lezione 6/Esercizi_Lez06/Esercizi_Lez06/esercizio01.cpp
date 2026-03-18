/*
c++ -o esercizio01 esercizio01.cpp
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

bool readData(std::string fileName, std::vector<double>& valVec, std::vector<double>& valErr)
{
  std::fstream myFile;

  myFile.open(fileName.c_str(),std::ios::in);
  if (myFile.good() == false)
    {
      return false;
    }

  double val, err;
  while (true)
    {
      myFile >> val >> err;
      if (myFile.eof() == true) break;
      valVec.push_back(val);
      valErr.push_back(err);
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
      std::cout << "\t./esercizio01 data.txt results.txt" << std::endl;
      return 1;
    }

  std::string fileInput  = argv[1];
  std::string fileOutput = argv[2];


  // ############################
  // # Read data and processing #
  // ############################
  std::vector<double> vec;
  std::vector<double> err;
  if (readData(fileInput, vec, err) == false)
    {
      std::cout << "Problem opening the file: " << fileInput.c_str() << std::endl;
      return 1;
    }

  std::cout << "The std::vector vec contains " << vec.size() << " elements" << std::endl;
  std::cout << "The std::vector vec contains " << err.size() << " elements" << std::endl;

  double sum = 0., sumW2 = 0.;
  double mean, devst;

  for (int i = 0; i < vec.size(); i++)
    {
      sum   += vec[i] / (err[i]*err[i]);
      sumW2 += 1. / (err[i]*err[i]);
    }
  mean  = sum / sumW2;
  devst = sqrt(1. / sumW2);


  // #################################
  // # Write analysis on output file #
  // #################################
  std::ofstream OutFile (fileOutput.c_str());
  OutFile << "=== Results of the analysis ===" << std::endl;
  OutFile << "\tMean               = " << mean << std::endl;
  OutFile << "\tError on the mean. = " << devst << std::endl;
  OutFile.close();


  return 0;
}
