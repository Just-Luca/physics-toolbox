#include "Analyzer.h"
#include <iostream>
#include <TApplication.h>
#include <TCanvas.h>

//default constructor
analyzer::analyzer()
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

//destructor
analyzer::~analyzer()
{
	if(histo_) delete histo_;
	if(graph_) delete graph_;
}

/*****************************************************************************************************************************/

//metodo lettura dati, riempimento vector, istogramma o matrice di covarianza, calcolo del minimo e del massimo
bool analyzer::setData(const string fileName, string type)
{
	//lettura dati
	std::ifstream inF(fileName.c_str());
	if (inF.good() == false)
    {
    	std::cout << "[analyzer::setData] Error opening the file: " << fileName.c_str() << endl;
    	return false;
    }
    
	double x = 0, y = 0, xErr = 0, yErr = 0, weightX = 0, weightY = 0, varX = 0, varY = 0;
  	int n = 0;

	//riempimento vector
 	while (true)
    {
		if(type == "counts")
			inF >> x;
		else if (type == "measurements")
			inF >> x >> y >> xErr >> yErr;
		else
		{
	  		std::cout << "[analyzer::setData] Error: wrong option " << type.c_str() << std::endl;
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
      	//calcolo minimo e massimo
      	if (x < minX_)
      		minX_ = x;
      	if (x > maxX_)
      		maxX_ = x; 
    }  
 	inF.close();
 	
 	//riempimento istogramma e errori
 	dataNumber_ = n;
  
	int nBins = 100;
	if (type == "counts")
    {
	    histo_ = new TH1D("Counts_Distribution","Counts distribution", nBins, minX_, maxX_);
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

//metodo media, deviazione standard e errore sulla media
void analyzer::computeMoments(vector<double>* values, vector<double>*  errors, double& mean, double& stdDev, double& meanError)
{
	double var = 0, weight = 0, weightedMean = 0;
    
 	mean = 0, stdDev = 0, meanError = 0;
    
 	for (int i = 0; i <= values->size()-1; i++)
    {
    	if (errors->empty() == false)
		{
			weightedMean += values->at(i) / pow(errors->at(i),2);
			weight += 1/ pow(errors->at(i),2);
		}

     	mean =  mean + values->at(i);
      	var  += pow(values->at(i),2);			
    }
  
	mean =  mean / values->size();
	var /= values->size();
	var -= pow(mean,2);
	weightedMean /= weight;

  	stdDev = sqrt(var);
    
 	if (errors->empty() == true)
 	 	meanError = stdDev / sqrt(dataNumber_);
  	else
    {
     	mean = weightedMean;
      	meanError = 1 / sqrt(weight);
    }
}


