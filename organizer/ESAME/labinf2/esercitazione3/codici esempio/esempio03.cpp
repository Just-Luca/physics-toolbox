// c++ -o esempio03 esempio03.cpp `root-config --glibs --cflags`

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <TCanvas.h>
#include <TH1F.h>

using namespace std;

double rand_range (double a, double b)
{
return a+(b-a)*rand()/(1.*RAND_MAX);
}

int main()  {
  srand (time (NULL));
  double min=-1;
  double max=1;
  double mean;
  int nEstrazioni=10;
  int N=10000; 
  
  TH1F pdf ("name","title",100,min,max);
  
  for (int i=0; i<N; i++)  {
    mean=0.;
    for (int j=0; j<nEstrazioni; j++)
    {
      mean+=rand_range(min,max);
    }
    mean /= (double)nEstrazioni;
    pdf.Fill(mean);
  }

  TCanvas cnv;  
  pdf.Draw();  
  pdf.Fit("gaus");  
  cnv.Print("istogramma.png","png");
  
  return 0;
}
