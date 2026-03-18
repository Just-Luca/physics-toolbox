/*
c++ -o FitMomenta FitMomenta.cpp `root-config --cflags --glibs`
*/

#include <iostream>
#include <fstream>

#include <TApplication.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>

using namespace std;

double distro1 (double* x, double* par)
{
  return par[0]*pow(x[0],2)*exp(-par[1]*x[0]);
}

double distro2 (double* x, double* par)
{
  return par[0]*x[0]*exp(-par[1]*x[0]);
}

double distro3(double *x,double *par){
  return par[0]*pow(x[0],2)*exp(-par[1]*pow(x[0],2));
}

int main (){

  TApplication *MyApp=new TApplication("MyApp", NULL, NULL);
  TCanvas* MyCanv = new TCanvas("MyCanv","MyCanv",0,0,700,500);
  TH1D *histo=new TH1D("histo","histo",200,0,4.5);

  TF1* MyFun1 = new TF1("MyFun1",distro1,0.,4.5,2);
  MyFun1->SetParameter(0,1.);
  MyFun1->SetParameter(1,1.);

  TF1* MyFun2 = new TF1("MyFun2",distro2,0.,4.5,2);
  MyFun2->SetParameter(0,1.);
  MyFun2->SetParameter(1,1.);

  TF1* MyFun3 = new TF1("MyFun3",distro3,0.,4.5,2);
  MyFun3->SetParameter(0,1.);
  MyFun3->SetParameter(1,1.);

  
  ifstream DataFile("momenta.txt");
  double var;
  while(true){
    DataFile>>var;
    if(DataFile.eof()==true)break;
    histo->Fill(var);
  }
  DataFile.close();

  histo->Draw();
  histo->Fit("MyFun1","+");
  MyFun2->SetLineColor(kGreen);
  histo->Fit("MyFun2","+");
  MyFun3->SetLineColor(kBlue);
  histo->Fit("MyFun3","+");

  MyCanv->Modified();
  MyCanv->Update();

  MyApp->Run();

  return 0;
}
