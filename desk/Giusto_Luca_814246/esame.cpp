/*
c++ -o esame esame.cpp `root-config --cflags --glibs`
*/

#include <iostream>
#include <cmath>

#include <TApplication.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <TF1.h>
#include <TStyle.h>

#include <TMath.h>


/*---------------------- PARAMETRI HARD-CODED ------------------------------------------------------ */

#define DELTA 3			// risoluzione temporale del rivelatore
#define par0 4.76*pow(10,-7)	// primo parametro della distribuzione di energia	
#define par1 1000.		// secondo parametro della distribuzione di energia
#define par2 pow(10,-4)		// terzo parametro della distribuzione di energia
#define MU 10.			// parametro della distribuzione del tempo
#define N 10000			// numero di estrazioni
#define nBin sqrt(N)		// numero di bin di HTempi, HEne, HRiv e dell'asse X di HRec
#define significance 0.05	// significance del test di Student


using namespace std;


/*---------------------- DISTRIBUZIONI --------------------------------------------------------------*/

double dist_energia (double *E, double *p) {

	return p[0]*(p[1] - p[2]*(E[0]*E[0]));
}

double dist_tempo (double *t, double *p) {
	
	return (exp(-t[0]/p[0]) / p[0]);
}


/*---------------------- FUNZIONE DI FIT ------------------------------------------------------------*/

double myExp (double *x, double *p) {
	
	return p[0]*(exp(-x[0]/p[1]) / p[1]);
}

/*---------------------- FUNZIONE DEL TEST DI COMPATIBILITÀ -----------------------------------------*/

// questa funzione effettua il test di compatibilità di Student tra il valore misurato e il valore 
// vero, restituendo "true" se i due vlori sono compatibili e "false" altrimenti

bool testComp (double &pvalue, double mis, double mis_err, double true_val, double signif, int N_mis) {

	double t = fabs((true_val - mis) / mis_err);
	
	pvalue = 2.*(1. - TMath::StudentI(t, N_mis-1));
	
	if (pvalue < signif) return false;
  	else                 return true;
}
	 
	
/*---------------------- MAIN -----------------------------------------------------------------------*/

int main () {

	cout << "\n" << endl;
	
/*---------------------- DEFINIZIONE DI OGGETTI TF1 E TH1 ------------------------------------------ */
					
	// definizione della prima funzione TF1, rappresentante g(E), e dei suoi parametri
	
	TF1 *g = new TF1 ("Energia", dist_energia, 0, 2500, 3);
	
	g->SetParameter(0, par0);
	g->SetParameter(1, par1);
	g->SetParameter(2, par2);
	
	
	// definizione della seconda funzione TF1, rappresentante f(t), e del suo parametro
	
	TF1 *f = new TF1 ("Tempo", dist_tempo, 0, 30, 1);
	
	f->SetParameter(0, MU);
	
	
	// definizione della terza funzione TF1, rappresentante la funzione esponenziale 
	// di fit, e dei sui parametri
	
	TF1 *myFit = new TF1 ("myExp", myExp, 0, 30, 2);
	
	myFit->SetParameter(0, 3125.);
	myFit->SetParameter(1, MU);
	myFit->SetParName(1,"MU");
	
	
	// definizione dei cinque istogrammi
	
	TH1D *HTempi = new TH1D ("HTempi","distribuzione dei tempi", nBin, 0, 30);
	
	TH1D *HEne = new TH1D ("HEne","distribuzione delle energie", nBin, 0, 2500);
	
	TH1D *HRiv = new TH1D ("HRiv","distribuzione delle energie registrate", nBin, 0, 6000);
		// si è deciso di impostare il massimo a 6000 keV poiché oltre quel valore si hanno
		// bin quasi esclusivamente vuoti, indipendentemente dal numero di bin utilizzato
	
	TH1F *HPP = new TH1F ("HPP","distribuzione dei pile-up", 15, 0, 6);
	
	TH2D *HRec = new TH2D ("HRec","distribuzione 2D delle energie registrate", nBin, 0, 6000, 15, 0, 6);
	
	
/*---------------------- CORPO PRINCIPALE DEL PROGRAMMA ---------------------------------------------*/
	
	// inizializzazione delle variabili ausiliarie che verranno poi utilizzate, all'interno
	// del ciclo for, per riempire gli istogrammi HRiv, HPP e HRec 
	 
	double E_residua = 0.;
	int N_pileup = 0;
	
	for (unsigned int i = 0; i < N; i++) {
		
		double t_i = 0.;
		double E_i = 0.;
		
		// 1) estrazione dei numeri casuali
		t_i = f->GetRandom();
		E_i = g->GetRandom();
		
		// 2) si riempiono gli istogrammi HTempi e HEne
		HTempi->Fill(t_i);
		HEne->Fill(E_i);
		
		// 3) la variabile N_pileup viene incrementata prima dei controlli e, poi, viene azzerata 
		//    nel caso in cui la distanza temporale dall'evento i-esimo sia superiore alla
		//    risoluzione temporale del rivelatore "DELTA"
		N_pileup++;
		
		// 4) se l'evento i-esimo avviene a distanza inferiore alla risoluzione del rivelatore
		//    non viene registrato, ma la sua energia viene salvata in E_residua 
		if (t_i <= DELTA) E_residua += E_i;
		
		// 5) altrimenti, l'evento viene registrato, e la sua energia è pari alla somma della 
		//    energia i-esima "E_i" e di tutta l'energia residua "accumulata" fino a quel momento.
		//    Dopodiché si riempiono HRiv, HPP e HRec e si azzerano le variabili ausiliarie
		else if (t_i > DELTA) {
		
			HRiv->Fill(E_i + E_residua);
			HPP->Fill(N_pileup);
			
			HRec->Fill(E_i + E_residua, N_pileup);
			
			E_residua = 0.;
			N_pileup = 0;
		}
	}
	
	
/*---------------------- PLOT E FIT DEGLI ISTOGRAMMI ------------------------------------------------*/

	TApplication *myApp = new TApplication("app", 0, 0);
	
	gStyle -> SetOptFit(1112);
	
	
	TCanvas *c1 = new TCanvas ("c1", "DISTRIBUZIONI 1D & FIT");
	
	c1->Divide(2,2);	// si divide il primo Canvas in quattro settori
	
	
	// 1°) plot di HTempi
	
	c1->cd(1);	
	
	HTempi->Draw();
	HTempi->SetFillColor(kYellow);
	HTempi->GetXaxis() -> SetTitle("secondi");
	HTempi->GetYaxis() -> SetTitle("conteggi");
	
	HTempi->Fit("myExp");	// si fitta HTempi con la funzione myExp
	
	
	// 2°) plot di HEne
	
	c1->cd(2); 
	
	HEne->Draw();
	HEne->SetFillColor(kYellow);
	HEne->GetXaxis() -> SetTitle("keV");
	HEne->GetYaxis() -> SetTitle("conteggi");
	
	
	// 3°) plot di HRiv
	
	c1->cd(3);
	
	HRiv->Draw();
	HRiv->SetFillColor(kYellow);
	HRiv->GetXaxis() -> SetTitle("keV");
	HRiv->GetYaxis() -> SetTitle("conteggi");
	
	
	// 4°) plot di HPP
	
	c1->cd(4);
	
	HPP->Draw();
	HPP->SetFillColor(kYellow);
	HPP->GetXaxis() -> SetTitle("pile-up");
	HPP->GetYaxis() -> SetTitle("conteggi");
	
	
	c1->Modified();
	c1->Update();
	
	
	TCanvas *c2 = new TCanvas ("c2", "DISTRIBUZIONE 2D");
	
	// plot di HRec
	
	HRec->Draw("LEGO2");	// disegna un istogramma a colonne senza righe interne e in scala colori
	HRec->GetXaxis() -> SetTitle("keV");
	HRec->GetYaxis() -> SetTitle("pile-up");
	HRec->GetZaxis() -> SetTitle("conteggi");
	
	c2->Modified();
	c2->Update();
	
	
	// i risultati del fit di HTempi vengono stampati a terminale
	
	double MU_hat = myFit->GetParameter(1);
	double MU_hat_err = sqrt(myFit->GetParError(1));
	
	
	cout << "\n" << endl;
	cout << "\t###################################" << endl;
	cout << "\t#	 RISULTATI DEL FIT	  #" << endl;
	cout << "\t###################################" << endl;
	cout << "\t#                                 #" << endl;
	cout << "\t#  mu = " << MU << "                        #" << endl;
	cout << "\t#  mu_hat = " << MU_hat << " +/- " << MU_hat_err << "  #" << endl;
	cout << "\t#                                 #" << endl;
	cout << "\t###################################" << endl;
	cout << "\t#                                 #" << endl;
	

/*---------------------- TEST DI COMPATIBILITÀ ------------------------------------------------------*/
	
	// il risultato del test di compatibilità viene stampato a terminale
	
	double pvalue;
	
	if (testComp(pvalue, MU_hat, MU_hat_err, MU, significance, N) == true) {
	
		cout << "\t#  I due valori sono compatibili. #" << endl;
	}
	
	else  cout << "\t#  I valori non sono compatibili. #" << endl;
	
	cout << "\t#  p-value = " << pvalue << "             #" << endl;
	cout << "\t#                                 #" << endl;
	cout << "\t###################################" << endl;
	cout << "" << endl;

	
/*---------------------------------------------------------------------------------------------------*/

	// il programma termina quando si chiude uno dei due Canvas (ad esempio il secondo)
	
	c2 -> Connect("TCanvas", "Closed()", "TApplication", gApplication, "Terminate()");
	
	myApp -> Run();
	
	return 0;
}

