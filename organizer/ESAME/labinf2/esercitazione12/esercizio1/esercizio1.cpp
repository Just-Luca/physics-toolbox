#include "Analyzer.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char** argv)
{
	analyzer prova;
	std::ifstream data1(argv[1]); 
	prova.setData(data1, double);
	return 0;
}
