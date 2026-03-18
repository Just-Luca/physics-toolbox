#include "Analyzer.h"

using namespace std;
 
analyzer::analyzer ()
{ 
  dataNumber_ = 0;
  minX_       = 0;
  maxX_       = 0;
    
  meanX_      = 0;
  stdDevX_    = 0;

  xMeas_.clear();
  yMeas_.clear();
  xErr_ .clear();
  yErr_ .clear();
    
  TH1D*         histo  = NULL;
  TGraphErrors* graph_ = NULL; 
}

analyzer::~analyzer ()
{
  if(histo_) delete histo_;
  if(graph_) delete graph_;
}    	
 
bool analyzer::setData (const string fileName, string type)
{
  ifstream inF(fileName.c_str());
  if (inF.good() == false)
    {
      cout << "[analyzer::setData]\tError opening the file: " << fileName.c_str() << endl;
      return false;
    }
  
  double x = 0, y = 0, xErr = 0, yErr = 0, weightX = 0, weightY = 0, varX = 0, varY = 0;
  int n = 0;

  while (true)
    {
      if      (type == "counts"  )     inF >> x;
      else if (type == "measurements") inF >> x >> y >> xErr >> yErr;
      else
	{
	  cout << "[analyzer::setData]\tError: wrong option " << type.c_str() << endl;
	  return false;
	}

      if (inF.eof() == true) break;      
      xMeas_.push_back(x);

      if (type == "measurements")
	{
	  yMeas_.push_back(y);
	  xErr_ .push_back(xErr);
	  yErr_ .push_back(yErr);
	}
	
      n++;
      if (x < minX_) minX_ = x;
      if (x > maxX_) maxX_ = x; 
    }  
  inF.close();
  
  dataNumber_ = n;
  
  int nBins = 100;
  if (type == "counts")
    {
      histo_ = new TH1D("Counts_Distribution","Counts distribution",nBins,minX_,maxX_);
      graph_ = NULL;

      for (int i = 0; i <= xMeas_.size()-1; i++)
	histo_->Fill(xMeas_.at(i));
      
      computeMoments(&xMeas_,&xErr_,meanX_,stdDevX_,meanError_);
    }
  else
    {
      graph_ = new TGraphErrors(fileName.c_str());
      histo_ = NULL;
      graph_->SetTitle("Measurements");
      graph_->GetXaxis()->SetTitle("x (units)"); 
      graph_->GetYaxis()->SetTitle("y (units)"); 
      graph_->SetMarkerStyle(20); 
      graph_->SetMarkerSize(0.5);
    }

  return true;
}

TH1D* analyzer::getHisto (void)
{
  if (histo_ != NULL) return histo_;
  else
    {
      cout << "[analyzer::getHisto]\tError: if data type was -measurements- use getGraph method to get a TGraphErrors" << endl;
      return 0;
    }
}

TGraphErrors* analyzer::getGraph (void)
{
  if (graph_ != NULL) return graph_;
  else
    {
      cout << "[analyzer::getGraph]\tError: if data type was -counts- use getHisto method to get a TH1D" << endl;
      return 0;
    }
}

void analyzer::computeMoments (vector<double>* values, vector<double>* errors, double& mean, double& stdDev, double& meanError)
{
  double var = 0, weight = 0, weightedMean = 0;
    
  mean = 0, stdDev = 0, meanError = 0;
    
  for (int i = 0; i <= values->size()-1; i++)
    {
      if (errors->empty() == false)
	{
	  weightedMean += values->at(i) / pow(errors->at(i),2);
	  weight       += 1.            / pow(errors->at(i),2);
	}

      mean =  mean + values->at(i);
      var  += pow(values->at(i),2);			
    }
  
  mean         =  mean / values->size();
  var          /= values->size();
  var          -= pow(mean,2);
  weightedMean /= weight;

  stdDev = sqrt(var);
    
  if (errors->empty() == true) meanError = stdDev / sqrt(dataNumber_);
  else
    {
      mean      = weightedMean;
      meanError = 1. / sqrt(weight);
    }
}

void analyzer::fitData (TF1* fitFunc, double xMin, double xMax)
{
  gStyle->SetOptFit(1112);
    	
  if      (histo_ != NULL) histo_->Fit(fitFunc,"","",xMin,xMax);
  else if (graph_ != NULL) graph_->Fit(fitFunc,"","",xMin,xMax);
  else
    {
      cout << "[analyzer::fitData]\tError: Histogram and Graph are both empty" << endl;
      exit(1);
    }
}

void analyzer::computeChi2 (TF1* fitFunc, double& chi2, int& NDF, double& pValue)
{
  chi2 = 0, NDF = 0, pValue = 0; 

  if (histo_ != NULL)
    {	    
      for (int i = 1; i <= histo_->GetNbinsX(); i++)
	chi2 = chi2 + pow((histo_->GetBinContent(i) - fitFunc ->Eval(histo_->GetBinCenter(i)))/(histo_->GetBinError(i)),2);
      
      NDF = histo_->GetNbinsX() - fitFunc -> GetNpar();
    }
  else if (graph_ != NULL)
    {
      for (int i = 0; i < graph_->GetN(); i++)
	chi2 = chi2 + pow((graph_->GetY()[i] - fitFunc ->Eval(graph_->GetX()[i])),2)/ ( pow(graph_->GetErrorY(i),2) + pow (fitFunc ->Derivative(graph_->GetX()[i]) * graph_->GetErrorX(i),2));

      NDF = graph_->GetN() - fitFunc -> GetNpar();
    }
  else
    {
      cout << "[analyzer::computeChi2]\tError: Histogram and Graph are both empty" << endl;
      exit(1);
    }
  
  pValue = fitFunc -> GetProb();
}

bool analyzer::testCompatibility (double& pvalue, double meas1, double err1, double meas2, double err2, double significance, string testType, double n1, double n2)
{
  double stat;

  if (testType == "Normal")
    {
      stat   = fabs((meas1 - meas2) / sqrt(err1*err1 + err2*err2));
      pvalue = TMath::Erfc(stat/sqrt(2.));
    }
  else if (testType == "tStudent")
    {
      if ((err1 != 0) && (err2 != 0))
	stat = fabs((meas1 - meas2) / sqrt(((n1-1.)*err1*err1 + (n2-1.)*err2*err2) / (n1+n2-2.) * (1./n1 + 1./n2)));
      else if ((err1 != 0) && (err2 == 0))
	{
	  stat = fabs((meas1 - meas2) / (err1/sqrt(n1)));
	  n2   = 1;
	}
      else if ((err1 == 0) && (err2 != 0))
	{
	  stat = fabs((meas1 - meas2) / (err2/sqrt(n2)));
	  n1   = 1;
	}
      pvalue = 2. * (1. - TMath::StudentI(stat,n1+n2-2.));
    }
  else
    {
      cout << "[analyzer::testCompatibility]\tError: unknown test type " << testType.c_str() << endl;
      return false;
    }
  
  if (pvalue < significance) return false;
  else                       return true;
}

TGraph* analyzer::computeContour (TF1* myFun, double delta, unsigned int parA, unsigned int parB)
{
  int    nPoints = 600;
  int    nSigma  = 2;
  double xMin    = myFun->GetParameter(parA) - nSigma * myFun->GetParError(parA);
  double yMin    = myFun->GetParameter(parB) - nSigma * myFun->GetParError(parB);
  double xStep   = 2.*nSigma*myFun->GetParError(parA) / nPoints;
  double yStep   = 2.*nSigma*myFun->GetParError(parB) / nPoints;
  double minChi2 = 0;
  double pValue  = 0;
  int    NDF     = 0;
    
  computeChi2(myFun,minChi2,NDF,pValue);
     
  double ContourLevel = minChi2 + delta;
  
  TGraph* least2Contour2D = new TGraph;
  least2Contour2D->GetXaxis()->SetTitle("Const");
  least2Contour2D->GetYaxis()->SetTitle("Scale (nm^2)");
  least2Contour2D->SetMarkerStyle(20);
  least2Contour2D->SetMarkerSize(0.3);
 
  double par0, par1;
  double newChi2  = 0;
  unsigned int it = 0;
    
  for (unsigned int i = 0; i < nPoints; i++)
    {
      bool belowLevel = false;
    	 
      myFun->SetParameter(parA,xMin + xStep*i);
      for (unsigned int j = 0; j < nPoints; j++)
    	{
    	  myFun->SetParameter(parB,yMin + yStep*j);
    	  computeChi2(myFun,newChi2,NDF,pValue);
    	  
    	  if (((newChi2 - ContourLevel) < 0) && (belowLevel == false))
	    {
	      belowLevel = true;
	      par0 = myFun->GetParameter(parA);
	      par1 = myFun->GetParameter(parB);
	      least2Contour2D->SetPoint(it,par0,par1);
	      it++;
	    }
    	  
    	  else if (((newChi2 - ContourLevel) > 0) && (belowLevel == true))
	    {
	      belowLevel = false;
	      par0 = myFun->GetParameter(parA);
	      par1 = myFun->GetParameter(parB);
	      least2Contour2D->SetPoint(it,par0,par1);
	      it++;
	    }
    	  
    	  else continue;
    	}
    }

  return least2Contour2D;
}
