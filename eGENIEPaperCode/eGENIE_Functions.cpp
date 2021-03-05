#include "TMath.h"
#include <TProfile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TGaxis.h>

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <utility>

#include "eGENIE_Constants.h"

using namespace std;

// -------------------------------------------------------------------------------------------------------------------------------------

double XSecNorm(TString Nucleus, TString Energy, TString Model) {

	TString XSecNormLabel = Nucleus+"_"+Energy+"_"+Model;

	double Events = GENIEEvents[XSecNormLabel];
	if (Events == 0) { cout << " Craaaaaaaaaaaapppppppppppppp !!!! No events for " << XSecNormLabel << endl; }

	double XSec = GENIEXSec[XSecNormLabel];
	if (Nucleus == "CH2") { XSec = GENIEXSec["12C_"+Energy+"_"+Model] + 2*GENIEXSec["1H_"+Energy+"_"+Model]; }
	if (Nucleus == "CH") { XSec = GENIEXSec["12C_"+Energy+"_"+Model] + GENIEXSec["1H_"+Energy+"_"+Model]; }
	if (XSec == 0) { cout << " Craaaaaaaaaaaapppppppppppppp !!!! No xsec for " << XSecNormLabel << endl; }

	double weight = XSec / Events;

	return weight;

}

// -------------------------------------------------------------------------------------------------------------------------------------

void PrettyPlot(TH1D* h, int color) {

	h->GetXaxis()->CenterTitle();
	h->GetXaxis()->SetNdivisions(9);
	h->GetXaxis()->SetTitleFont(FontStyle);
	h->GetXaxis()->SetLabelFont(FontStyle);
//	h->GetXaxis()->SetLabelSize(TextSize);
//	h->GetXaxis()->SetTitleSize(TextSize);

	h->GetYaxis()->CenterTitle();
	h->GetYaxis()->SetNdivisions(9);
	h->GetYaxis()->SetTitleFont(FontStyle);
	h->GetYaxis()->SetLabelFont(FontStyle);
//	h->GetYaxis()->SetLabelSize(TextSize);
//	h->GetYaxis()->SetTitleSize(TextSize);
	h->GetYaxis()->SetTitle("Area Normalized");

	h->SetLineColor(color);
	h->SetLineWidth(3);
	h->Draw("c hist same");	

}

// -------------------------------------------------------------------------------------------------------------------------------------

TString ToStringInt(int num) {

	std::ostringstream start;
	start << num;
	string start1 = start.str();
	return start1;

}

// -------------------------------------------------------------------------------------------------------------------------------------

void Reweight(TH1D* h, double SF) {

	int NBins = h->GetXaxis()->GetNbins();

	for (int i = 0; i < NBins; i++) {

		double CurrentEntry = h->GetBinContent(i+1);
		double NewEntry = CurrentEntry * SF / h->GetBinWidth(i+1);

		double CurrentError = h->GetBinError(i+1);
		double NewError = CurrentError * SF / h->GetBinWidth(i+1);

		h->SetBinContent(i+1,NewEntry); 
//		h->SetBinError(i+1,NewError); 
		h->SetBinError(i+1,0.000001); 

	}

}


// -------------------------------------------------------------------------------------------------------------------------------------



