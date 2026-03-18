/*
c++ -o mandelbrot mandelbrot.cpp complesso.cc `root-config --glibs --cflags`
*/

#include "complesso.h"

#include <iostream>
#include <cmath>
#include <string>

#include "TCanvas.h"
#include "TH2F.h"
#include "TAxis.h"
#include "TStyle.h"
#include "TApplication.h"

using namespace std;

int main()
{
  TApplication* myApp = new TApplication("myApp", 0, 0);
	
  // Crea un istogramma in 2D inserendo i range e i bin sull'asse delle x e sull'asse delle y
  double xmin = -2., xmax = 1.;
  double ymin = -1., ymax = 1.;
  double pixelSize = 0.0005;
  int NbinX = (int)((xmax-xmin)/pixelSize); 
  int NbinY = (int)((ymax-ymin)/pixelSize); 
  int M = 100;

  TH2F* histo2d = new TH2F ("isto_name","histo_title", NbinX, xmin, xmax, NbinY, ymin, ymax);
	
  for (int i = 1; i <= NbinX; i++)
    {
      for (int j = 1; j <= NbinY; j++)
	{
	  complesso c(histo2d->GetXaxis()->GetBinCenter(i), histo2d->GetYaxis()->GetBinCenter(j));
	  complesso z1(0,0);
	  complesso z2;
	  int n;
	  for (n = 0; n < M; n++)
	    {
	      z2 = z1*z1 + c;
	      if(z2.Mod() > 2) break;
	      else z1 = z2;
	    }
	  histo2d->Fill(c.Re(),c.Im(),n);
	}
    }

  TCanvas* c2 = new TCanvas ("c1","Mandelbrot",0,0,900,600);
  c2->cd();
  gStyle->SetOptStat(0); // Non fa comparire il riquadro delle statistiche dell'istogramma
  histo2d->Draw("COLZ");
  c2->Modified();
  c2->Update():
    
  myApp->Run();
  return 0;
}
