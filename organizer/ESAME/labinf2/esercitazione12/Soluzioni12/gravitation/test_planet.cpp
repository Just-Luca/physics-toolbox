/*
c++ -o test_planet test_planet.cpp vett2d.cc planet.cc `root-config --glibs --cflags`
*/

#include "planet.h"
#include "vett2d.h"

#include <iostream>
#include <cmath>
#include <string>

#include "TCanvas.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TFrame.h"
#include "TApplication.h"

using namespace std;

int main()
{
  TApplication *myApp = new TApplication("myApp", NULL, NULL);
	
  // Terra: r = 150e+9m v = 30e+3m/s m = 5.97e+24kg
  vett2d r_terra(150e+9,0);
  vett2d v_terra(0,30e+3);
  double mass_terra = 5.97e+24;
  planet* terra = new planet("Terra", mass_terra, r_terra, v_terra);
	
  // Marte: r = 228e+9m v = 24e+3m/s m = 6.42e+23kg
  vett2d r_marte(228e+9,0);
  vett2d v_marte(0,24e+3);
  double mass_marte = 6.42e+23;
  planet* marte = new planet("Marte", mass_marte, r_marte, v_marte);
	
  // Sole: r = 0 v = 0 m = 2e+30kg
  vett2d r_sole(0,0);
  vett2d v_sole(0,0);
  double mass_sole = 2e30;
  planet* sole = new planet("Sole", mass_sole, r_sole, v_sole);
	
  TCanvas* c1 = new TCanvas("c1","Gravitation",0, 0, 900, 900);
  c1->SetFrameFillColor(kBlue);
	
  TGraph* traiett_Terra = new TGraph();
  TGraph* traiett_Marte = new TGraph();
  TGraph* traiett_Sole  = new TGraph();
	
  traiett_Marte->SetMarkerStyle(7);
  traiett_Terra->SetMarkerStyle(7);
  traiett_Sole->SetMarkerStyle(30);
  traiett_Sole->SetMarkerSize(2);

  traiett_Marte->SetMarkerColor(kRed);
  traiett_Terra->SetMarkerColor(kGreen);
  traiett_Sole->SetMarkerColor(kYellow);
	
  double AxisRange = 5e11;
  double DeltaT    = 2*3600;

  int answer = 0;
  do {
    cout << "Imposta sistema di riferimento: "<< endl;
    cout << "\tSole -> 1" << endl;
    cout << "\tTerra -> 2" << endl;
    cout << "\tMarte -> 3" << endl;
    cin >> answer;
  } while (answer<1 || answer>3);
	
	
  for (int i = 0; i < 100000; i++)
    {
      terra->DoStep(sole, marte,DeltaT);
      marte->DoStep(sole, terra,DeltaT);
      sole->DoStep(marte, terra,DeltaT);
		
      if (answer == 1)
	{
	  traiett_Terra->SetPoint(i,terra->GetX()-sole->GetX(), terra->GetY()- sole->GetY());
	  traiett_Marte->SetPoint(i,marte->GetX()-sole->GetX(), marte->GetY()- sole->GetY() );
	  traiett_Sole->SetPoint(i,0., 0.);
	}
      else if (answer == 2)
	{
	  traiett_Terra->SetPoint(i,0., 0.);
	  traiett_Marte->SetPoint(i,marte->GetX()-terra->GetX(), marte->GetY()-terra->GetY());
	  traiett_Sole->SetPoint(i,sole->GetX()-terra->GetX(), sole->GetY()-terra->GetY());
	}
      
      else if (answer == 3)
	{
	  traiett_Terra->SetPoint(i,terra->GetX()-marte->GetX(), terra->GetY()- marte->GetY());
	  traiett_Marte->SetPoint(i,0., 0.);
	  traiett_Sole->SetPoint(i,sole->GetX()-marte->GetX(), sole->GetY()-marte->GetY());
	}
      
      if (i == 0)
	{
	  traiett_Marte->Draw("AP");
	  traiett_Terra->Draw("P same");
	  traiett_Sole->Draw("P same");
	}
      else if (i%30 == 0)
	{
	  traiett_Marte->GetXaxis()->SetRangeUser(-AxisRange, AxisRange);
	  traiett_Marte->GetYaxis()->SetRangeUser(-AxisRange, AxisRange);
	  c1->Modified();
	  traiett_Marte->GetXaxis()->SetLimits(-AxisRange, AxisRange);
	  traiett_Marte->GetYaxis()->SetLimits(-AxisRange, AxisRange);
	  c1->Modified();
	  c1->Update();
	}		
    }
  
  traiett_Marte->GetXaxis()->SetTitle("x (m)");
  traiett_Marte->GetYaxis()->SetTitle("y (m)");		
  c1->Modified();
  c1->Update();

  cout << "The end of the simulation " << endl;
  
  myApp->Run();
  return 0;
}
