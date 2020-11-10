#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TString.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TMath.h>
#include <TLine.h>
#include <TPad.h>
#include <TGaxis.h>
#include <TGraph.h>

#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

TString ToString(double num) {

	std::ostringstream start;
	start << num;
	string start1 = start.str();
	return start1;

}

// ----------------------------------------------------------------------------------------------------------------

// To run the code

// root -l
// .L VertexRange.cpp
// VertexRange("12C","4461","2250")

// ----------------------------------------------------------------------------------------------------------------

void VertexRange(TString Nucleus, TString Energy, TString TorusCurrent) {

	// ------------------------------------------------------------------------

	// Available options for input parameters

	// Nucleus = {"C12","4He","56Fe","CH2"}
	// Energy = {1.161,2.261,4.461}
	// TorusCurrent = {"750","1500","2250"}

	// ------------------------------------------------------------------------

	gStyle->SetOptStat(0);	
	TString CLASPathToFiles = "/w/hallb-scifs17exp/clas/claseg2/apapadop/";

	// ------------------------------------------------------------------------

	TString LabelE = " @ E = 4.461 GeV";

	if (Energy == "2261") { LabelE = " @ E = 2.261 GeV"; }
	if (Energy == "1161") { LabelE = " @ E = 1.161 GeV"; }

	// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	TString Extension = "";
	if (Nucleus == "C12" && TorusCurrent == "1500") { Extension = "HighTorusCurrent_"; }
	TString FileName = CLASPathToFiles + Extension + "GetCharge_genie_filtered_data_e2a_ep_"+Nucleus+"_"+Energy+"_neutrino6_united4_radphot_test_100M.root";
	TFile* FilteredFile = TFile::Open(FileName);

	TH2D* h2 = (TH2D*)(FilteredFile->Get("h2_Electron_CorrectedVertex_Phi"));
	TH1D* h1 = h2->ProjectionX(Nucleus+"_"+Energy+"_"+TorusCurrent);

	TF1* FitFunction = nullptr; 

	double Min = -10, Max = 10;
	double MinDraw = -10, MaxDraw = 10;
	double MinXRange = -10, MaxXRange = 10;

	if (Nucleus == "4He" || Nucleus == "3He") {

		Min = -4.;
		Max = 4.;

		h1->GetXaxis()->SetRangeUser(Min,Max);
		FitFunction = new TF1("fpol0","pol0",Min,Max);

	} else {

		MinXRange = 3.;
		MaxXRange = 8.;

		Min = 3.;
		Max = 8.;

		MinDraw = 4.5;
		MaxDraw = 6.3;

		if (Nucleus == "CH2" && Energy == "1161") { Min = 5.;	Max = 5.4; }
		if (Nucleus == "C12" && Energy == "1161" && TorusCurrent == "750") { Min = 5.15; Max = 5.55; }
		if (Nucleus == "C12" && Energy == "1161" && TorusCurrent == "1500") { Min = 5.1; Max = 5.5; }
		if (Nucleus == "C12" && Energy == "2261") { Min = 4.9; Max = 5.3; }
		if (Nucleus == "C12" && Energy == "4461") { Min = 4.8; Max = 5.2; }
		if (Nucleus == "56Fe" && Energy == "2261") { Min = 4.75; Max = 5.15; }
		if (Nucleus == "56Fe" && Energy == "4461") { Min = 4.7; Max = 5.1; }

		h1->GetXaxis()->SetRangeUser(MinXRange,MaxXRange);
		FitFunction = new TF1("fgaus","gaus",MinDraw,MaxDraw);	

	}

	// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	TString CanvasName =  Nucleus+"_"+Energy+"_"+TorusCurrent;
	TCanvas* PlotCanvas = new TCanvas(CanvasName,CanvasName,205,34,1024,768);

	PlotCanvas->SetBottomMargin(0.12);
	PlotCanvas->SetLeftMargin(0.12);

	h1->SetTitle(Nucleus + ", " + Energy + ", " + TorusCurrent);
	h1->Draw();
	h1->Fit(FitFunction,"","",Min,Max);

	FitFunction->Draw("same");

	// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	double mean = FitFunction->GetParameter(1);
	double sigma = FitFunction->GetParameter(2);
	double MinRange = mean - 4*sigma;
	double MaxRange = mean + 4*sigma;

	TLatex* Mean = new TLatex();
	Mean->SetTextFont(132);
	Mean->SetTextColor(kBlack);
	Mean->SetTextSize(0.06);
	Mean->DrawLatexNDC(0.62,0.85,"Mean = " + ToString(mean));
	Mean->DrawLatexNDC(0.62,0.75,"#sigma = " + ToString(sigma));
	Mean->DrawLatexNDC(0.62,0.65,"Min = " + ToString(MinRange));
	Mean->DrawLatexNDC(0.62,0.55,"Max = " + ToString(MaxRange));

	// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

} // End of the program
