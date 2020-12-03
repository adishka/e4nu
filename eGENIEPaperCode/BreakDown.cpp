#include <TFile.h>
#include <TH1D.h>
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

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

//#include "/home/afroditi/Dropbox/PhD/Secondary_Code/myFunctions.cpp"

//#include "../../myClasses/Constants.h"

using namespace std;
//using namespace Constants;

void PrettyPlot(TH1D* h, int color) {

	int FontStyle = 132;

	h->GetXaxis()->CenterTitle();
	h->GetXaxis()->SetNdivisions(10);
	h->GetXaxis()->SetTitleFont(FontStyle);
	h->GetXaxis()->SetLabelFont(FontStyle);

	h->GetYaxis()->CenterTitle();
	h->GetYaxis()->SetNdivisions(10);
	h->GetYaxis()->SetTitleFont(FontStyle);
	h->GetYaxis()->SetLabelFont(FontStyle);
	h->GetYaxis()->SetTitle("Arbitrary Units");

	h->SetLineColor(color);
	h->SetLineWidth(3);
	h->Draw("c hist same");	

}

// ----------------------------------------------------------------------------------------------------------------

TString ToString(int num) {

	std::ostringstream start;
	start << num;
	string start1 = start.str();
	return start1;

}

// ----------------------------------------------------------------------------------------------------------------

void BreakDown(TString Nucleus, TString Energy, TString Tune, TString Interaction,TString PlotName) {

	// -----------------------------------------------------------------------------------------------------------------------------------------------

	gStyle->SetOptStat(0);
	TH1D::SetDefaultSumw2();
	int FontStyle = 132;
	const std::vector<int> Colors{610,410,kRed+1,kBlue,kGreen+3};
	const std::vector<TString> Labels{"QE","MEC","RES","DIS","COH"};

	// ------------------------------------------------------------------------

	TString TuneLabel = "SuSav2";
	if (Tune == "G18_10a_02_11a") { TuneLabel = "G2018"; }
	

	// ------------------------------------------------------------------------

	TString FileName = "myFiles/"+Nucleus+"_"+Energy+"_"+Tune+"_"+Interaction+".root";
	TFile* FileSample = TFile::Open(FileName);

	// ------------------------------------------------------------------------

	int NInteractions = 5; // QE, MEC, RES, DIS, COH
	TH1D* Plots[NInteractions];

	// ------------------------------------------------------------------------

	TString canName = Nucleus+"_"+Energy+"_"+Tune+"_"+Interaction+PlotName;
	TCanvas* can = new TCanvas(canName,canName,205,34,1024,768);
	can->cd();

	// ------------------------------------------------------------------------

	TLegend* leg = new TLegend(0.5,0.6,0.8,0.85);

	// ------------------------------------------------------------------------

	TH1D* FullPlot = (TH1D*)(FileSample->Get(PlotName));
	PrettyPlot(FullPlot,kBlack);
	leg->AddEntry(FullPlot,"Total " + TuneLabel + " " + Interaction,"l");

	// ------------------------------------------------------------------------

	for (int WhichInteraction = 0; WhichInteraction < NInteractions; WhichInteraction++) {

		Plots[WhichInteraction] = (TH1D*)(FileSample->Get(PlotName+"_BreakDown_"+ToString(WhichInteraction)));
		PrettyPlot(Plots[WhichInteraction],Colors[WhichInteraction]);
		leg->AddEntry(Plots[WhichInteraction],Labels[WhichInteraction],"l");
		

	}

	
	// ------------------------------------------------------------------------

	leg->SetTextSize(0.04);
	leg->SetTextFont(FontStyle);
	leg->SetBorderSize(0);
	leg->Draw();

	// ------------------------------------------------------------------------

} // End of the program
